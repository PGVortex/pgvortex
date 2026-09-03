EXTENSION = pgvortex
MODULE_big = pgvortex
OBJS = src/pgvortex.o
DATA = sql/pgvortex--0.1.0.sql
PGFILEDESC = "pgvortex - vector indexing and adaptive hybrid search"

PG_CPPFLAGS = -Isrc

PG_CONFIG ?= pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs 2>/dev/null)
ifeq ($(strip $(PGXS)),)
$(error PostgreSQL PGXS not found; set PG_CONFIG=/path/to/pg_config)
endif
include $(PGXS)
