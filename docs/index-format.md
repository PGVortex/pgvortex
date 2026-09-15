# Format Inventory

This document lists logical records only. No C/C++ struct in the skeleton is a
frozen disk or wire format.

## PostgreSQL-managed metadata

- Meta: magic, format version, index generation, next IDs, manifest epoch
- Status directory: memtable ID to outstanding TID/status pages
- Status entries: logical vectors not covered by a durable published segment
- Manifest: active/obsolete segment identities, versions, ranges, locations,
  models, codecs, checksums, and publication LSNs

These records use PostgreSQL-managed pages and WAL.

## Immutable segment artifact

- versioned header and bounded section directory
- native ANN body
- TID mapping
- raw vector or quantized code payload
- transform/codec identifiers
- statistics and checksums
- separately durable deletion sidecar

Every count, offset, dimension, and length requires overflow-safe validation.
Readers reject unknown versions, algorithms, features, or incompatible models.
Persisted data contains offsets and IDs, never process pointers.

## IPC

IPC has an independent protocol version and length-delimited messages. Requests
own their serialized query/filter data. Responses contain stable tuple
references and status codes. Backend addresses, PostgreSQL Datums, exceptions,
and native object pointers cannot cross the boundary.

Until formats are frozen, upgrades require `REINDEX` and stale segment caches
are discarded.
