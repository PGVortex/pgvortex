# PGVortex Roadmap

Target: publish the first open-source release by the end of December 2026.

The labels below are release-confidence targets, not claims about the current
implementation. The repository currently contains the phase-one extension
skeleton only.

## Phase 1: foundation

- PGXS build and extension packaging for PostgreSQL 17 and 18
- pgvector dependency and centralized compatibility boundary
- SharedBuffer, MMAP, planner, executor, statistics, and test layout
- architecture decisions and provisional index-format documentation
- CI compile/install smoke test

## v0.1 stable target

- SharedBuffer IVF-Flat and IVF-PQ
- PCA training and application
- Generic WAL, crash recovery, REINDEX, and VACUUM behavior
- pre-filter and iterative post-filter execution
- basic hybrid cost model and planner integration
- correctness, recall, and performance baselines

## v0.1 beta target

- IVF-RaBitQ
- bitmap inline filtering with TID filter sets
- HNSW-Flat and one quantized HNSW variant
- executor-time strategy switching

## v0.1 experimental target

- Vamana with stable base and mutable delta
- relation-backed immutable MMAP generations
- MMAP IVF, HNSW, and Vamana prototypes

## Explicitly deferred

- production readiness for every algorithm/storage combination
- writable MMAP persistence
- PostgreSQL core patches
- a per-node `StorageProvider` abstraction shared by buffer and MMAP engines
- on-disk compatibility guarantees before the format is versioned and frozen

More detailed sequencing is tracked in [docs/roadmap.md](docs/roadmap.md).
