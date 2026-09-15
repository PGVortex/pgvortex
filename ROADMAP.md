# PGVortex Roadmap

Target: publish the first open-source release by the end of December 2026.

The current repository contains only the Architecture v1 skeleton. Items below
are targets, not implemented features.

## September: executable vertical slice

- register the `vortex` access method and pgvector opclasses
- freeze the first PG/native C ABI and versioned IPC envelope
- start and supervise one PGVortex vector worker
- build, publish, load, and search one minimal immutable segment
- use brute-force shared memtable search for recent vectors
- complete one end-to-end KNN query through heap MVCC recheck

## October: delta and durability

- byte-bounded shared memtable, ready-state publication, seal, and rotation
- WAL-backed status pages and versioned segment manifest
- segment lifecycle: building, durable, active, obsolete, reclaimable
- delete bitmap, VACUUM ordering, size-tiered merge, and rebuild
- recovery reconciliation and crash fault injection at every publication step

## November: native performance

- native HNSW as the primary ANN path
- IVF-Flat after the durability path is stable
- concurrent segment search, candidate merge, and memory budgeting
- read-only mmap cold start and optional promotion to RAM
- static, concurrent, dynamic, recovery, and cold-start benchmarks

## December: hybrid search and release

- iterative ANN and filter-aware oversampling
- basic planner cost model and blocking TopK execution
- initial scalar filter integration
- compatibility, recovery, recall, benchmark, and operational documentation
- release packaging and reproducible PG17/PG18 CI

## After the core release gate

- IVF-PQ, PCA, RaBitQ, Vamana, and DiskANN
- worker groups and external vector-service deployment
- physical replication segment channel
- PageSegmentStore for page-based cloud PostgreSQL
- object storage, local cache, Neon/serverless integration, and GPU adapters

The release gate is a complete, recoverable vertical slice, not the number of
algorithm directories populated. See [docs/roadmap.md](docs/roadmap.md).
