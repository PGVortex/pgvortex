#ifndef PGVORTEX_ENGINE_QUANTIZER_HPP
#define PGVORTEX_ENGINE_QUANTIZER_HPP

#include <cstdint>

namespace pgvortex {

enum class Codec
{
	kNone,
	kPq,
	kRaBitQ
};

using CodecId = std::uint64_t;

class Quantizer
{
public:
	virtual ~Quantizer() = default;
};

} // namespace pgvortex

#endif /* PGVORTEX_ENGINE_QUANTIZER_HPP */
