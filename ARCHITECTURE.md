# Architecture

SURREAL models a universe state as `U = (C, L, S, I, H)`: causal partial order, active law domains, content-addressed state, invariant ledger, and authenticated history. A law transition changes that tuple only through an explicit certificate-bearing operation.

## Language boundary

| Layer | Language | Responsibility |
|---|---|---|
| primitive | x86-64 assembly | direct Linux `getrandom(2)` syscall ABI and a deliberately simple reversible rotate/XOR demonstration primitive |
| numerical field | Fortran 2018 | periodic integer lattice Laplacian, divergence, curl, Maxwell leap, kick-drift |
| certified kernel | C++23 | arbitrary-precision rational/interval arithmetic, exact units, symbolic omega/Hahn arithmetic, causal graph, law runtime, state, invariants, hashing, entropy streams, horizon archives, rewrite verifier |
| CLI | C++23 | configured runs, reference demo, verification, law/formula catalogues, symbolic math inspection |

The assembly is not claimed as a speed or security optimization. Seeded pseudorandom execution uses Philox4x32-10 in C++; live entropy uses the assembly syscall wrapper. The C ABI between Fortran/assembly and C++ is intentionally tiny. There is no hidden Python or C runtime.

## Causal execution and branching

Each event records `id`, sorted unique parents, derived depth, local rational time, region, law, before/after state hashes, invariant hash, entropy root, and memo-reuse bit. Missing predecessors and time regressions are rejected.

`Universe::fork()` is explicitly a **common-random-numbers** counterfactual fork: immutable region pointers, causal graph, memo state, and the seeded entropy position are copied. Two replay forks therefore receive the same future seeded draws until their entropy consumption differs. `fork_independent(domain)` shares the same physical/causal past but derives a deterministic independent Philox stream. This distinction is part of the API contract rather than an accidental consequence of copying the object.

Memoization includes the incoming causal-boundary root, so a cached deterministic result cannot cross a changed causal past accidentally.

## Numeric domains and units

`Rational` is arbitrary precision. `Interval` is a closed rational enclosure. `sqrt_interval` uses scaled arbitrary-precision integer square roots. `Quadratic` provides exact `a+b*sqrt(d)` arithmetic. `SurrealScale` is a finite Laurent polynomial in omega; `HahnSeries` is a finite-support rational-exponent Hahn fragment. No host float is used by these certified types.

`Quantity` pairs an exact SI-canonical rational with a five-base dimension vector (length, mass, time, charge, temperature). Named units carry exact conversion scales. Formula-atlas evaluation validates dimensions before arithmetic; compatible units are converted to canonical SI values first. This makes “arithmetic exact” and “physics dimensionally valid” separate enforced contracts.

## Integer field safety

Fortran kernels intentionally use `int64`. C++ wrappers validate dimensions and conservative magnitude envelopes before entering the lattice kernels. `kick_drift_checked` uses arbitrary-precision preflight arithmetic to prove that the exact velocity and position updates fit in `int64` before calling Fortran. These guards prevent silent integer wrap from being described as exact evolution.

## Physics transitions

Body dynamics return `LawResult {state, invariant certificate, detail}`. Runtime admission requires the invariant certificate to pass. Entropic laws receive an `EntropyLedger`; every draw updates the entropy root. Field transitions return their own discrete divergence certificate because body conservation and lattice constraints are different contracts.

## Configured universes

`surreal run` consumes a strict canonical configuration that defines step count, cosmology world, timesteps/couplings, bodies, lattice dimensions, scalar threshold, and sparse initial field values. Unknown or duplicate scalar keys are rejected. The canonical configuration is committed into the run manifest and report. `surreal demo` is only the built-in small reference scenario.

## Self-rewrite

`LawProgram` is a microscopic exact stack language. A rewrite is a list of named local identities with before/after hashes. `verify_rewrite_certificate` replays every step. `self_rewrite_kernel` performs exact corpus equivalence and may adopt only a verified, equivalent, non-larger program, repeating to a fixed point and recording hash lineage. Wall-clock benchmark observations are excluded from semantic roots.

This is constrained verified rewriting, not arbitrary self-modifying native code.

## Authenticated horizon

`seal_horizon` writes a committed archive of a region plus causal-root context. `reopen_horizon` validates the archive before exposing content. “Horizon” is a software information-boundary analogy, not a claim that storage implements black-hole thermodynamics.

## Integrity anchors

Run manifests and horizon commitments have two verification modes. Internal verification establishes self-consistency and corruption detection. Anchored verification additionally compares the verified manifest root or horizon commitment with a caller-supplied value retained outside the artifact being checked. SURREAL deliberately does not equate an in-band digest with source authenticity.

## Canonical persistence

Canonical state, event, invariant and rewrite objects use schema-tagged length framing so arbitrary payload bytes cannot change field boundaries. Horizon text records hex-encode variable text. Run and horizon publication uses durable temporary-file plus atomic-rename publication and bounded no-follow reopen paths.

## Model-independent admission protocol

The AI-facing boundary points inward: models are proposal sources, not runtime authorities. `SURREAL_ADMISSION_REQUEST_V1` is a strict local line protocol accepted only from stdin or a local file. The parser bounds total bytes, field count, per-value size, work count, duplicate keys, unknown fields, and operation-specific cardinality. There is no network transport or model SDK in the kernel.

`admit()` dispatches only to real certified engines. Exact comparisons use `Rational`; formula evaluation uses the unit-checked `Quantity` layer; causal admission constructs and validates an actual `CausalGraph`; rewrite verification replays the bounded `LawProgram` certificate. The receipt embeds the normalized request and result, hashes both, and derives a receipt root. `verify_admission_receipt()` decodes the embedded request and deterministically executes it again, so receipt verification does not trust the original caller.
