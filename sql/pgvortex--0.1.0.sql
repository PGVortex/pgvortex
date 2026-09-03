\echo Use "CREATE EXTENSION pgvortex" to load this file. \quit

CREATE FUNCTION pgvortex_version()
RETURNS text
AS 'MODULE_PATHNAME', 'pgvortex_version'
LANGUAGE C
IMMUTABLE
STRICT
PARALLEL SAFE;

COMMENT ON FUNCTION pgvortex_version() IS
'Return the installed PGVortex extension version';
