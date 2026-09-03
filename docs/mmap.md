# MMAP Design

PGVortex does not use writable mappings as a persistence mechanism. Without a
PostgreSQL core checkpoint hook, writable MMAP data cannot safely inherit all
database durability guarantees.

The default design is:

```text
index relation
  meta / generation manifest
  model data
  immutable relation-backed base generation -- mmap(PROT_READ)
  SharedBuffer mutable delta
  SharedBuffer edge or list overlay
```

PostgreSQL creates and durably records every generation. Compaction writes a
new, unpublished generation through PostgreSQL-controlled I/O, validates it,
then switches the manifest. Existing readers finish on the old generation;
reclamation waits for reader accounting and normal PostgreSQL lifecycle rules.

Each backend owns its mapping address and page-fault behavior. Shared memory
may contain only stable identifiers such as index OID, `RelFileLocator`,
generation number, extent metadata, and reader counts. Process virtual
addresses must never be stored in shared memory or persisted on disk.

MMAP layouts may optimize offset-to-pointer conversion, cache lines, SIMD,
NUMA placement, software prefetch, and sequential fault behavior. They are not
required to match SharedBuffer layouts or reuse its traversal loop.

A future `mmap_mode = cache` may expose an external, reconstructable read cache.
Such a cache is never the only durable copy and may be discarded after a crash
or version mismatch.
