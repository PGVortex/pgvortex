#ifndef PGVORTEX_ENGINE_COMMON_TRAINING_HPP
#define PGVORTEX_ENGINE_COMMON_TRAINING_HPP

#include <cstdint>

namespace pgvortex {

struct TrainingOptions
{
	std::uint64_t random_seed;
	std::uint32_t max_samples;
	std::uint32_t max_iterations;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_COMMON_TRAINING_HPP */
