#ifndef PGVORTEX_SHARED_WAL_H
#define PGVORTEX_SHARED_WAL_H

#include "postgres.h"

#include "access/generic_xlog.h"

typedef struct PgvWalContext
{
	GenericXLogState *generic_state;
} PgvWalContext;

/* The first implementation will wrap PostgreSQL Generic WAL. */

#endif /* PGVORTEX_SHARED_WAL_H */
