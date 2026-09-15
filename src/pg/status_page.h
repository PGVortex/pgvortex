#ifndef PGVORTEX_PG_STATUS_PAGE_H
#define PGVORTEX_PG_STATUS_PAGE_H

#include "postgres.h"

#include "pgvortex/engine_c.h"

typedef enum PgvMemtableState
{
	PGV_MEMTABLE_MUTABLE,
	PGV_MEMTABLE_SEALED,
	PGV_MEMTABLE_BUILDING,
	PGV_MEMTABLE_DURABLE
} PgvMemtableState;

/* Tracks logical vectors that have not crossed the segment durability boundary. */
typedef struct PgvStatusPageContext PgvStatusPageContext;

#endif /* PGVORTEX_PG_STATUS_PAGE_H */
