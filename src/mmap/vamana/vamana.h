#ifndef PGVORTEX_MMAP_VAMANA_H
#define PGVORTEX_MMAP_VAMANA_H

#include "executor/search_cursor.h"

extern PgvSearchCursor *pgv_mmap_vamana_begin_search(Relation index_relation,
													 const PgvSearchRequest *request);

#endif /* PGVORTEX_MMAP_VAMANA_H */
