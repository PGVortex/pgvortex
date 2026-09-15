#ifndef PGVORTEX_PGVECTOR_COMPAT_H
#define PGVORTEX_PGVECTOR_COMPAT_H

#include "postgres.h"

typedef struct PgvPgvectorView
{
	int32		dimensions;
	const void *data;
} PgvPgvectorView;

/* This is the only layer allowed to understand pgvector's Datum ABI. */
extern bool pgv_pgvector_supports_type(Oid type_oid);
extern bool pgv_pgvector_datum_view(Datum value, Oid type_oid,
									PgvPgvectorView *view);

#endif /* PGVORTEX_PGVECTOR_COMPAT_H */
