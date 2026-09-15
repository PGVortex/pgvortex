#ifndef PGVORTEX_PG_AM_H
#define PGVORTEX_PG_AM_H

#include "postgres.h"

#include "access/amapi.h"

/* Target SQL access method: USING vortex. Not registered by the skeleton. */
extern IndexAmRoutine *pgv_am_routine(void);

#endif /* PGVORTEX_PG_AM_H */
