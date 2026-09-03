#ifndef PGVORTEX_MMAP_HNSW_H
#define PGVORTEX_MMAP_HNSW_H

#include "executor/search_cursor.h"

extern PgvSearchCursor *pgv_mmap_hnsw_begin_search(Relation index_relation,
												   const PgvSearchRequest *request);

#endif /* PGVORTEX_MMAP_HNSW_H */
