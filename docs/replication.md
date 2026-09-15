# Replication Direction

Replication separates consistency-critical metadata from large performance
artifacts:

```text
PostgreSQL WAL channel: logical insert/delete, status, manifest publication
Segment channel: immutable ANN bytes
```

The WAL channel is authoritative. A delayed segment cannot resurrect a TID
already deleted by replayed WAL. Segment ID, version, generation, memtable range,
checksum, and publication boundary allow a standby to discard stale or
out-of-order artifacts.

The segment channel must be a SegmentStore capability rather than a permanently
embedded primary file server. Peer and object-store transports are possible,
but neither physical replication nor remote storage is a v0.1 release gate.

Embedding payload in WAL remains an explicit future policy decision. Full
payload simplifies standby delta replay but can cause substantial WAL
amplification; TID-only replay reduces WAL but requires heap materialization.

Base backup, PITR retention, standby promotion, missing-segment behavior, and
garbage-collection horizons must be designed together before replication is
declared supported.
