# Research notes

SURREAL uses research as design input, not as borrowed performance claims.

- Counter-based random-number generation follows the Random123/Philox design family from Salmon et al., *Parallel Random Numbers: As Easy as 1, 2, 3* (SC11). 0.5.6 includes an internal Philox4x32-10 implementation pinned to the published zero-key/zero-counter known-answer vector. It is used for deterministic replay/substream generation, not cryptography.
- Common-random-number and independent-stream counterfactuals are exposed separately because paired stochastic simulations and independent ensembles have different experimental semantics.
- Dimensional analysis is a first-class scientific correctness layer. Established C++ unit systems such as Boost.Units demonstrate that quantity/unit algebra can be enforced without making units an informal comment. SURREAL implements a smaller exact-rational SI layer so conversion and arithmetic remain inside its certified number plane.
- Conway/Gonshor surreal-number theory and later work on surreal exponentials, derivations, and transseries motivate symbolic omega-scale arithmetic. 0.5.6 implements only finite computable fragments.
- Causal-set ideas motivate a locally ordered event substrate without claiming causal-set quantum gravity is established physics.
- Adaptive-mesh and hierarchical-timestep astrophysics motivate local refinement and local clocks; the current release implements the refinement criterion, not a production AMR hierarchy.
- Equality saturation/e-graphs motivate separating semantic equivalence proof from optimization choice. SURREAL uses a smaller verified local rewrite VM rather than claiming a full e-graph engine.

## Primary references used for 0.5.6 hardening

- Random123 counter-based RNG documentation: https://random123.com/releases/1.06/docs/index.html
- Boost.Units dimensional-analysis documentation: https://www.boost.org/latest/doc/html/boost_units.html
- Linux `getrandom(2)` behavior and interruption semantics: https://man7.org/linux/man-pages/man2/getrandom.2.html

These references informed interface choices only. SURREAL's tests and claim ledger remain the authority for what this release itself implements.
