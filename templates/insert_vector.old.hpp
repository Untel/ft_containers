#define __VECTOR_INSERT(__RESOLVER, __RESOLVER2) \
    size_type required_cap = _size + n_to_insert; \
    size_type at = std::distance(begin(), position); \
    iterator it_end = end(); \
    bool is_collapsing = (position + n_to_insert) > it_end; \
    size_type collapse_at = is_collapsing ? (it_end - position) : 0; \
    size_type remaining_to_insert = is_collapsing ? n_to_insert - collapse_at : 0; \
    VDBG("INSERTING at: " << at << " length: " << n_to_insert << " actual_size: " << _size); \
    if (required_cap > _capacity) { \
        size_type s = _size; \
        size_type next_capacity = (required_cap > (_capacity * 2) \
            ? required_cap \
            : _capacity * 2 \
        ); \
        VDBG("NOT ENOUGH CAP cap" << _capacity << " required" << required_cap  << " next" << next_capacity); \
        pointer tmp = _allocator.allocate(next_capacity + 1); \
        VDBG("Copying length " << at); \
        VDBG("Next capacity " << next_capacity); \
        for (size_type i = 0; i < at; i++) {\
            VDBG("Copying " << _c[i]); \
            _allocator.construct(tmp + i, _c[i]); \
        } \
        VDBG("Constructing length" << n_to_insert); \
        for (size_type i = 0; i < n_to_insert; i++) { \
            VDBG("Constructing " << __RESOLVER); \
            _allocator.construct(tmp + at + i, __RESOLVER); \
        } \
        VDBG("Collapsing length" << remaining_to_insert); \
        for (size_type i = 0; i < remaining_to_insert; i++) { \
            VDBG("Collapsing " << *(_c + s - remaining_to_insert + i)); \
            _allocator.construct(tmp + at + n_to_insert + i, *(_c + s - remaining_to_insert + i)); \
        } \
        _clean(); \
        _c = tmp; \
        _size = required_cap; \
        _capacity = next_capacity; \
        return ; \
    } \
    size_type construct_from_end = n_to_insert; \
    VDBG("ENOUGH CAP: " << _capacity); \
    VDBG("Construct from end: " << construct_from_end); \
    for (size_type i = 0; i < n_to_insert; i++) { \
        _allocator.construct(_c + _size + i, __RESOLVER2); \
    } \
    if (!is_collapsing && it_end != position) { \
        size_type to_move = it_end - position - construct_from_end; \
        VDBG("Collapse is(" << is_collapsing << ") N=" << to_move); \
        for (size_type i = 0; i < to_move; i++) { \
            *(_c + _size - (i + 1)) = *(_c + _size - (i + n_to_insert + 1)); \
        } \
    } \
    if (it_end != position) { \
        VDBG("Remaining is(" << remaining_to_insert); \
        for (size_type i = 0; i < n_to_insert - remaining_to_insert; i++) \
            *(_c + at + i) = __RESOLVER; \
    } \
    _size += n_to_insert;
