#ifndef PGVORTEX_MMAP_IVF_H
#define PGVORTEX_MMAP_IVF_H

#include "executor/search_cursor.h"

extern PgvSearchCursor *pgv_mmap_ivf_begin_search(Relation index_relation,
												  const PgvSearchRequest *request);

#endif /* PGVORTEX_MMAP_IVF_H */
