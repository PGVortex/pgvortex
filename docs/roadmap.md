# Engineering Roadmap

## 1. Extension foundation

Freeze naming and SQL ownership, validate PG17/PG18 builds, add extension
install/uninstall tests, establish pgvector compatibility tests, and define
error-handling and memory-context conventions.

## 2. SharedBuffer IVF-Flat

Specify page structs and metapage versioning, implement build/insert/scan,
define Generic WAL records, add MVCC and VACUUM behavior, and test recovery.
Establish exact-result and recall harnesses before quantization.

## 3. Training and quantization

Add deterministic sampling and KMeans, PCA model persistence, PQ encoding and
ADC distance, training-memory limits, and quantization-error statistics. Add
RaBitQ behind a beta feature boundary after PQ is stable.

## 4. Hybrid planning and execution

Implement pre-filter exact and iterative post-filter first. Add cost estimates,
blocking TopK, cursor continuation, runtime feedback, then bitmap inline-filter
and bounded strategy switching.

## 5. SharedBuffer graph beta

Implement logical NodeIDs, directory pages, append/COW edges, recovery-safe
node states, iterative HNSW search, deletes, VACUUM, and one quantized variant.

## 6. Experimental engines

Prototype Vamana stable-base/delta consolidation. Specify immutable generation
publication and reader lifetimes before MMAP IVF, HNSW, or Vamana traversal.

Every phase includes correctness, isolation, crash-recovery, recall, and
benchmark gates appropriate to the functionality introduced.
