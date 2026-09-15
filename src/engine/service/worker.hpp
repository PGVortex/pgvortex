#ifndef PGVORTEX_ENGINE_SERVICE_WORKER_HPP
#define PGVORTEX_ENGINE_SERVICE_WORKER_HPP

#include "engine/common/status.hpp"

namespace pgvortex {

class VectorWorker
{
public:
	Status Run();
	void RequestStop();
};

/* Worker threads must not call PostgreSQL backend APIs. */

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_SERVICE_WORKER_HPP */
