#include "surreal/admission.hpp"
#include "surreal/exact.hpp"
#include "surreal/physics.hpp"
#include "surreal/units.hpp"
#include "surreal/universe.hpp"
#include "surreal/version.hpp"
#include <charconv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>
#include <stdexcept>

namespace {
std::uint64_t parse_u64(std::string s){int base=10;if(s.starts_with("0x")){base=16;s=s.substr(2);}std::uint64_t v=0;auto[p,ec]=std::from_chars(s.data(),s.data()+s.size(),v,base);if(ec!=std::errc{}||p!=s.data()+s.size())throw std::invalid_argument("invalid uint64");return v;}
std::size_t parse_size(std::string_view s){std::size_t v=0;auto[p,ec]=std::from_chars(s.data(),s.data()+s.size(),v);if(ec!=std::errc{}||p!=s.data()+s.size())throw std::invalid_argument("invalid size");return v;}
}
int main(int argc,char**argv){try{
  if(argc<2){std::cerr<<"SURREAL "<<surreal::kVersion<<"\nusage: surreal demo|run|verify|laws|formulas|math|describe|admit|verify-receipt ...\n";return 2;}
  std::string cmd=argv[1];
  if(cmd=="demo"){if(argc<4||argc>6){std::cerr<<"usage: surreal demo STEPS OUTDIR [SEED] [WORLD]\n";return 2;}auto steps=parse_size(argv[2]);std::optional<std::uint64_t>seed;if(argc>=5)seed=parse_u64(argv[4]);std::string world=argc>=6?argv[5]:"lcdm";auto r=surreal::run_reference_universe(steps,argv[3],seed,world);std::cout<<r.canonical();return 0;}
  if(cmd=="run"){if(argc<4||argc>5){std::cerr<<"usage: surreal run CONFIG OUTDIR [SEED]\n";return 2;}auto cfg=surreal::load_reference_config(argv[2]);std::optional<std::uint64_t>seed;if(argc==5)seed=parse_u64(argv[4]);auto r=surreal::run_universe(cfg,argv[3],seed);std::cout<<r.canonical();return 0;}
  if(cmd=="verify"){if(argc<3||argc>4){std::cerr<<"usage: surreal verify OUTDIR [EXPECTED_MANIFEST_ROOT]\n";return 2;}std::string err;const bool ok=argc==4?surreal::verify_reference_run_anchored(argv[2],argv[3],&err):surreal::verify_reference_run(argv[2],&err);if(!ok){std::cerr<<err<<"\n";return 1;}std::cout<<"verified\n";return 0;}
  if(cmd=="laws"){std::cout<<"[\n";auto v=surreal::law_catalogue_json_lines();for(std::size_t i=0;i<v.size();++i)std::cout<<"  "<<v[i]<<(i+1==v.size()?"\n":",\n");std::cout<<"]\n";return 0;}
  if(cmd=="formulas"){std::cout<<"[\n";auto v=surreal::formula_catalogue_json_lines();for(std::size_t i=0;i<v.size();++i)std::cout<<"  "<<v[i]<<(i+1==v.size()?"\n":",\n");std::cout<<"]\n";return 0;}
  if(cmd=="describe"){std::cout<<surreal::admission_description_json();return 0;}
  if(cmd=="admit"){if(argc>3){std::cerr<<"usage: surreal admit [REQUEST_FILE|-]\n";return 2;}std::string text;if(argc==2||std::string(argv[2])=="-"){std::ostringstream b;b<<std::cin.rdbuf();text=b.str();}else{std::ifstream f(argv[2],std::ios::binary);if(!f)throw std::runtime_error("cannot open admission request");std::ostringstream b;b<<f.rdbuf();text=b.str();}auto req=surreal::parse_admission_request(text);auto receipt=surreal::admit(req);std::cout<<receipt.canonical();return receipt.status=="ADMIT"?0:3;}
  if(cmd=="verify-receipt"){if(argc!=3){std::cerr<<"usage: surreal verify-receipt RECEIPT_FILE\n";return 2;}std::ifstream f(argv[2],std::ios::binary);if(!f)throw std::runtime_error("cannot open admission receipt");std::ostringstream b;b<<f.rdbuf();auto receipt=surreal::parse_admission_receipt(b.str());std::string err;if(!surreal::verify_admission_receipt(receipt,&err)){std::cerr<<err<<"\n";return 1;}std::cout<<"verified\n";return 0;}
  if(cmd=="math"){using namespace surreal;Quadratic phi(Rational(1,BigInt(2)),Rational(1,BigInt(2)),BigInt(5));auto relation=phi*phi-phi-Quadratic(Rational(1),Rational(0),BigInt(5));auto h=HahnSeries::omega()*HahnSeries::infinitesimal();std::cout<<"phi="<<phi.str()<<"\nphi^2-phi-1="<<relation.str()<<"\nomega*(1/omega)="<<h.str()<<"\n";return 0;}
  std::cerr<<"unknown command\n";return 2;
}catch(const std::exception&e){std::cerr<<"error: "<<e.what()<<"\n";return 1;}}
