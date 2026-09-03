#ifndef PGVORTEX_SHARED_IVF_H
#define PGVORTEX_SHARED_IVF_H

#include "executor/search_cursor.h"

extern PgvSearchCursor *pgv_shared_ivf_begin_search(Relation index_relation,
													 const PgvSearchRequest *request);

#endif /* PGVORTEX_SHARED_IVF_H */
