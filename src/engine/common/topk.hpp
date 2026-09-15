#ifndef PGVORTEX_ENGINE_COMMON_TOPK_HPP
#define PGVORTEX_ENGINE_COMMON_TOPK_HPP

#include <cstdint>

namespace pgvortex {

struct TupleRef
{
	std::uint32_t block_number;
	std::uint16_t offset_number;
};

struct Candidate
{
	TupleRef tuple;
	double distance;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_COMMON_TOPK_HPP */
