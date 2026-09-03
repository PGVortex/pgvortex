#ifndef PGVORTEX_COMMON_TOPK_H
#define PGVORTEX_COMMON_TOPK_H

#include "postgres.h"

#include "storage/itemptr.h"

typedef struct PgvTopK PgvTopK;

typedef struct PgvScoredTid
{
	ItemPointerData tid;
	double		distance;
} PgvScoredTid;

extern PgvTopK *pgv_topk_create(uint32 limit, MemoryContext memory_context);
extern void pgv_topk_offer(PgvTopK *topk, const PgvScoredTid *candidate);

#endif /* PGVORTEX_COMMON_TOPK_H */
