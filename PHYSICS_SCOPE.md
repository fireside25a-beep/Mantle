# Physics scope and claim ledger

SURREAL separates **executed dynamics**, **unit-checked formula kernels**, and **research targets**. Exact arithmetic alone is not advertised as physical correctness: formula inputs must also satisfy the unit/dimension contract.

## Executed dynamics in 0.5.6

- Dimensionless Friedmann expansion with radiation, matter, curvature, and Lambda terms; selectable LCDM, Einstein-de Sitter and radiation-dominated law worlds.
- Pairwise softened Newtonian gravity using rational interval square-root enclosures and kick-drift-kick integration.
- Pairwise Coulomb kicks with equal/opposite interval forces.
- Local inertial photon packet propagation.
- Entropic two-body decay with every random draw committed.
- Exact stellar rest-mass to radiant-energy bookkeeping transition.
- Periodic integer vacuum Maxwell lattice update with discrete divergence preservation certificate and checked `int64` safety envelope.
- Exact integer scalar-field refinement criterion with checked Laplacian envelope.

## Unit-checked formula atlas

The public formula entry point accepts exact `Quantity` values, canonicalizes named units into exact SI rationals, validates dimensions, and then evaluates its rational/interval expression. 0.5.6 includes mechanics, gravitation/cosmology, thermodynamic/fluid, atomic reference and Planck-scale formulas listed by `surreal formulas`.

The formula atlas validates dimensions and exact conversion scales; it does not by itself validate empirical constants, model applicability, experimental uncertainty, or whether a formula is appropriate to a particular physical regime.

## Explicit non-claims

0.5.6 does **not** implement the Einstein field equations, GRMHD, radiation transport, a stellar reaction network, quantum field theory, Standard Model scattering amplitudes, chemistry, planet formation, or every experimentally known law. The configured runner is a reference causal-law laboratory, not a production universe simulator.

The symbolic number layer is a finite computable fragment. The class of all surreal numbers is a proper class and cannot be materialized by a finite program.

## Reference-run units

The configured causal-law runner currently uses dimensionless/normalized rational coordinates and couplings for its body and lattice dynamics. The exact SI `Quantity` system applies to the public formula atlas. A future physical-scenario schema must attach dimensions to executed-state fields before those reference dynamics can be described as SI-typed simulation state.
