#ifndef PGVORTEX_PG_COMPAT_H
#define PGVORTEX_PG_COMPAT_H

#include "postgres.h"

#if PG_VERSION_NUM < 170000 || PG_VERSION_NUM >= 190000
#error "pgvortex currently supports PostgreSQL 17 and 18"
#endif

#define PGVORTEX_PG_MAJOR_VERSION (PG_VERSION_NUM / 10000)

#endif /* PGVORTEX_PG_COMPAT_H */
