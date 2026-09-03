#include "postgres.h"

#include "fmgr.h"
#include "utils/builtins.h"

#include "pg_compat/pg_compat.h"
#include "pgvortex.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(pgvortex_version);

Datum
pgvortex_version(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(cstring_to_text(PGVORTEX_VERSION));
}
