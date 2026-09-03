#ifndef PGVORTEX_MMAP_COMPACTION_H
#define PGVORTEX_MMAP_COMPACTION_H

#include "postgres.h"

typedef enum PgvCompactionPhase
{
	PGV_COMPACTION_BUILD,
	PGV_COMPACTION_VALIDATE,
	PGV_COMPACTION_PUBLISH,
	PGV_COMPACTION_RETIRE
} PgvCompactionPhase;

typedef struct PgvCompactionJob PgvCompactionJob;

#endif /* PGVORTEX_MMAP_COMPACTION_H */
