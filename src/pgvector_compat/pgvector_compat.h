#ifndef PGVORTEX_PGVECTOR_COMPAT_H
#define PGVORTEX_PGVECTOR_COMPAT_H

#include "postgres.h"

#include "common/vector.h"

/*
 * This is the sole boundary allowed to understand pgvector Datums and ABI.
 * Core engines consume PgvVectorView and never pgvector's internal structs.
 */
extern bool pgv_pgvector_supports_type(Oid type_oid);
extern bool pgv_pgvector_datum_view(Datum value, Oid type_oid,
									PgvVectorView *view);

#endif /* PGVORTEX_PGVECTOR_COMPAT_H */
