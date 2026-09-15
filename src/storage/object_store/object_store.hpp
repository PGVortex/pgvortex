#ifndef PGVORTEX_STORAGE_OBJECT_STORE_HPP
#define PGVORTEX_STORAGE_OBJECT_STORE_HPP

namespace pgvortex {

class SegmentStore;

/* Reserved for a reconstructable remote segment channel after v0.1. */
SegmentStore *CreateObjectSegmentStore();

} // namespace pgvortex

#endif /* PGVORTEX_STORAGE_OBJECT_STORE_HPP */
