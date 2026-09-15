# MMAP Residency

MMAP is a read-only residency policy for durable immutable segments, not a
separate storage engine or ANN implementation.

```text
durable segment -> mmap(PROT_READ) -> immediately searchable
                                  -> optional background promotion to RAM
```

No published segment body is modified through a writable mapping. Inserts use
the shared memtable, deletes use a separately durable sidecar, and rebuilds
publish a new generation.

Each process owns its mapping address. Shared memory and manifests contain only
segment identity, version, generation, extents, and reader counts. Native HNSW
or IVF receives a contiguous SegmentView and follows pointers/offsets without a
storage callback.

Disk-oriented algorithms may use their own asynchronous/direct-I/O and cache
policies instead of mapping the whole artifact.
