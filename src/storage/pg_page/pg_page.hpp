#ifndef PGVORTEX_STORAGE_PG_PAGE_HPP
#define PGVORTEX_STORAGE_PG_PAGE_HPP

namespace pgvortex {

class SegmentStore;

/* Materializes immutable segment blobs from PostgreSQL-managed relation pages. */
SegmentStore *CreatePageSegmentStore();

} // namespace pgvortex

#endif /* PGVORTEX_STORAGE_PG_PAGE_HPP */
