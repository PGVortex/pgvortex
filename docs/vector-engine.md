# Native Vector Engine

The vector engine is PostgreSQL-independent C++ behind a narrow C and versioned
IPC boundary. Its responsibilities are segment build/load/search, concurrent
multi-segment execution, quantization, transforms, memory residency, and
candidate production.

## Worker model

v0.1 uses one supervised PGVortex background worker with a dispatcher and a
native thread pool. Backend processes submit serialized requests and may scan
the current memtable concurrently. Results contain stable tuple references and
distances, not PostgreSQL object pointers.

Worker threads may perform ANN traversal, distance kernels, SIMD, PQ, RaBitQ,
prefetch, and native I/O. They may not invoke PostgreSQL backend APIs. The main
PostgreSQL process boundary handles errors, cancellation, memory ownership, and
heap visibility.

## Future evolution

The protocol must admit multiple workers and an external service without
changing query semantics:

```text
backend -> worker group -> local SegmentStore
backend -> vector server -> object store and local cache
```

GPU/cuVS and remote execution are adapter targets, not v0.1 dependencies.
