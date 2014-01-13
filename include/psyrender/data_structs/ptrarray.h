/**
 * A list of pointers that automacially grows and shrinks.
 *
 * Data can be put into a PtrArray using PtrArray_append(), PtrArray_extend,
 * and PtrArray_insert().
 *
 * Existing items can be get or set using PtrArray_get() and PtrArray_set().
 * These functions check index bounds. The fast inline functions PtrArray_GET()
 * and PtrArray_SET() do not check bounds.
 *
 * A PtrArray can be used as a stack by using PtrArray_append() to push to the
 * stack and PtrArray_pop() to pop.
 *
 * Feel free to use the "len" and "items" struct members directly. Just keep in
 * mind that "items" may be reallocated and moved whenever an item is added or
 * removed. Be careful when storing pointers into "items".
 */

#ifndef _PSY_PTRARRAY_H
#define _PSY_PTRARRAY_H

#include <stdbool.h>

typedef struct {
    unsigned int n_allocated;  // Number of items allocated
    unsigned int len;  // Number of items in the array
    void** items;  // Block of void* items in the array
} PtrArray;

/**
 * Return new empty pointer array.
 *
 * Free the returned PtrArray with PtrArray_free() when done.
 */
PtrArray* PtrArray_new();

/**
 * Adds a single item to the end of the array.
 */
void PtrArray_append(PtrArray* a, void* item);

/**
 * Add a list of items to the end of the array.
 *
 * "n_items" are taken from the "items" list and inserted into the array.
 */
void PtrArray_extend(PtrArray* a, void** items, unsigned int n_items);

/**
 * Insert "item" into the array at index "pos".
 *
 * Items to the right of "pos" must be shifted, so this can be an expensive
 * operation.
 *
 * Returns true if the item was inserted. Return false if the given position
 * was out of range.
 */
bool PtrArray_insert(PtrArray* a, unsigned int pos, void* item);

/**
 * Remove the item at position "pos".
 *
 * Items to the right of "pos" must be shifted, so this can be an expensive
 * operation.
 *
 * Returns NULL if pos is out of bounds.
 */
void* PtrArray_delete(PtrArray* a, unsigned int pos);

/**
 * Returns the array item at index "pos".
 */
void* PtrArray_get(const PtrArray* a, unsigned int pos);

/**
 * Returns the array item at index "pos".
 *
 * Warning: No bounds checking is done.
 */
static inline void* PtrArray_GET(const PtrArray* a, unsigned int pos) {
    return a->items[pos];
}

/**
 * Sets the array item at index "pos" to value.
 *
 * Return true if the item was set, or false if "pos" was out of bounds.
 */
bool PtrArray_set(PtrArray* a, unsigned int pos, void* item);

/**
 * Sets the array item at index "pos" to value.
 *
 * Warning: No bounds checking is done.
 */
static inline void PtrArray_SET(PtrArray* a, unsigned int pos, void* item) {
    a->items[pos] = item;
}

/**
 * Remove the last item from the array and return it.
 *
 * Returns NULL if there are no items in the array.
 */
void* PtrArray_pop(PtrArray* a);

/**
 * Free PtrArray created from PtrArray_new().
 *
 * Data pointers inserted in the array are not free'd.
 */
void PtrArray_free(PtrArray* a);

/**
 * Create a PtrArray like type called ``_listtype`` that stores pointers to
 * ``_type`` instead of void pointers. All functions defined are prefixed with
 * ``_listtype`` instead of ``PtrArray``. Only static inline functions are
 * defined, so there is no need to create a ".c" file.
 */
#define PTRARRAY_MAKE_HEADER(_listtype, _type) \
\
    typedef PtrArray _listtype; \
\
    static inline _listtype* _listtype##_new() { \
        return (_listtype*) PtrArray_new(); \
    } \
\
    static inline void _listtype##_append(_listtype* a, _type* item) { \
        PtrArray_append((PtrArray*) a, (void*) item); \
    } \
\
    static inline void _listtype##_extend(_listtype* a, _type** items, unsigned int n_items) { \
        PtrArray_extend((PtrArray*) a, (void**) items, n_items); \
    } \
\
    static inline bool _listtype##_insert(_listtype* a, unsigned int pos, _type* item) { \
        return PtrArray_insert((PtrArray*) a, pos, (void*) item); \
    } \
\
    static inline _type* _listtype##_delete(_listtype* a, unsigned int pos) { \
        return (void*) PtrArray_delete((PtrArray*) a, pos); \
    } \
\
    static inline _type* _listtype##_get(const _listtype* a, unsigned int pos) { \
        return (void*) PtrArray_get((PtrArray*) a, pos); \
    } \
\
    static inline _type* _listtype##_GET(const _listtype* a, unsigned int pos) { \
        return ((PtrArray*) (a))->items[pos]; \
    } \
\
    static inline bool _listtype##_set(_listtype* a, unsigned int pos, _type* item) { \
        return PtrArray_set((PtrArray*) a, pos, (void*) item); \
    } \
\
    static inline void _listtype##_SET(_listtype* a, unsigned int pos, _type* item) { \
        ((PtrArray*) a)->items[pos] = (void*) item; \
    } \
\
    static inline _type* _listtype##_pop(_listtype* a) { \
        return (void*) PtrArray_pop((PtrArray*) a); \
    } \
\
    static inline void _listtype##_free(_listtype* a) { \
        PtrArray_free((PtrArray*) a); \
    }

#endif
