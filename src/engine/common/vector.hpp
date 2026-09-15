#ifndef PGVORTEX_ENGINE_COMMON_VECTOR_HPP
#define PGVORTEX_ENGINE_COMMON_VECTOR_HPP

#include <cstddef>
#include <cstdint>

namespace pgvortex {

enum class VectorKind
{
	kFloat32,
	kFloat16,
	kSparseFloat32,
	kBit
};

/* Borrowed view. Ownership never crosses the request boundary implicitly. */
struct VectorView
{
	VectorKind kind;
	std::uint32_t dimensions;
	const void *data;
	std::size_t bytes;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_COMMON_VECTOR_HPP */
