# SegmentStore

SegmentStore owns complete immutable artifacts. Its coarse operations create a
writer, publish/open a version, check existence, and remove an obsolete version.
It is not called during ANN neighbor traversal.

## NativeFileStore

The local-performance path stores versioned segment files on local durable
storage. A segment can be opened read-only with mmap for immediate availability,
promoted to RAM in the background, or consumed through algorithm-native I/O for
DiskANN-style search.

PostgreSQL object lifecycle, fsync ordering, backup, tablespaces, and orphan
cleanup must be specified before this store is production-supported.

## PageSegmentStore

The portability path writes opaque immutable segment bytes through
PostgreSQL-managed relation pages. Loading reads those pages sequentially and
materializes a contiguous native SegmentView before search; the ANN inner loop
never calls `ReadBuffer()`.

This mode favors PostgreSQL/remote-page durability integration over cold-start
latency and WAL volume. It is a candidate for page-based cloud PostgreSQL.

## ObjectSegmentStore

The cloud path is deferred until after v0.1. Immutable segments may live in S3,
OSS, or a compatible service with a compute-local cache. PostgreSQL retains the
WAL-backed manifest, while remote bytes remain a versioned artifact that must
be available for recovery at the required LSN.
