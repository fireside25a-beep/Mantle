# SURREAL 0.5.6 release notes

0.5.6 adds the first model-independent local admission boundary. SURREAL remains the authority layer: an AI or ordinary local program emits a bounded canonical request; SURREAL evaluates it through an existing certified engine and emits an authenticated replay-verifiable receipt.

Implemented admission operations are exact rational relation checking, unit-safe formula evaluation, self-contained causal DAG admission, and proof-step law rewrite verification. The protocol has no model SDK, network dependency, hosted adapter, or hidden stochastic path. `surreal describe`, `surreal admit`, and `surreal verify-receipt` are real CLI surfaces and are exercised by the release test target.

All 0.5.5 causal, physics, entropy, horizon, unit, exact arithmetic, Fortran field, and rewrite semantics remain intact.
