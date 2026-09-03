#ifndef PGVORTEX_SHARED_PAGE_H
#define PGVORTEX_SHARED_PAGE_H

#include "postgres.h"

typedef enum PgvPageType
{
	PGV_PAGE_META,
	PGV_PAGE_MODEL,
	PGV_PAGE_DIRECTORY,
	PGV_PAGE_GRAPH_NODE,
	PGV_PAGE_GRAPH_EDGE,
	PGV_PAGE_CODE,
	PGV_PAGE_RAW_VECTOR,
	PGV_PAGE_IVF_BASE_POSTING,
	PGV_PAGE_IVF_DELTA_POSTING,
	PGV_PAGE_TOMBSTONE,
	PGV_PAGE_RETIRED
} PgvPageType;

/* Physical page structs are intentionally deferred until format design. */

#endif /* PGVORTEX_SHARED_PAGE_H */
