# Contributing

The acceptance bar is complete executable evidence backed by tests and audits.

- No unfinished, simulated, or scaffold-only implementation artifacts in production source.
- Every public C++ API and every Fortran/assembly hook must have a real linked caller/test path and pass `make audit`.
- New stochastic behavior must specify replay, common-random-number fork, and independent-stream semantics.
- New formula kernels must expose unit/dimension contracts through `Quantity`; anonymous raw-rational public formula APIs are not accepted.
- Integer field kernels require an overflow argument and executable refusal test.
- New run configuration fields must be canonicalized, validated, committed into artifacts, and corruption-tested.
- New physics must distinguish an executed transition from a reference formula and state exactly which invariants are certified.
- `make test`, ASan, UBSan, Clang and audit must all pass before release.
