# Third-party notices and research provenance

SURREAL 0.5.6 does not vendor third-party source code in this repository.

The build uses Boost.Multiprecision headers supplied by the host Boost installation. Boost is distributed under the Boost Software License 1.0. See the Boost distribution for its license text.

The internal Philox4x32-10 implementation follows the published Random123/Philox algorithm family described by John K. Salmon, Mark A. Moraes, Ron O. Dror, and David E. Shaw, *Parallel Random Numbers: As Easy as 1, 2, 3* (SC11). The implementation is maintained in this repository; Random123 source code is not bundled.

Research references are design inputs and do not imply endorsement, code provenance, or performance equivalence. See `RESEARCH.md`.
