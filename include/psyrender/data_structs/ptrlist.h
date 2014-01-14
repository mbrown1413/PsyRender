/**
 * A list of pointers that automacially grows and shrinks.
 *
 * Data can be put into a PtrList using PtrList_append(), PtrList_extend,
 * and PtrList_insert().
 *
 * Existing items can be get or set using PtrList_get() and PtrList_set().
 * These functions check index bounds. The fast inline functions PtrList_GET()
 * and PtrList_SET() do not check bounds.
 *
 * A PtrList can be used as a stack by using PtrList_append() to push to the
 * stack and PtrList_pop() to pop.
 *
 * Feel free to use the "len" and "items" struct members directly. Just keep in
 * mind that "items" may be reallocated and moved whenever an item is added or
 * removed. Be careful when storing pointers into "items".
 */

#ifndef _PSY_PTRLIST_H
#define _PSY_PTRLIST_H

#include <stdbool.h>

typedef struct {
    unsigned int n_allocated;  // Number of items allocated
    unsigned int len;  // Number of items in the list
    void** items;  // Block of void* items in the list
} PtrList;

/**
 * Return new empty pointer list.
 *
 * Free the returned PtrList with PtrList_free() when done.
 */
PtrList* PtrList_new();

/**
 * Adds a single item to the end of the list.
 */
void PtrList_append(PtrList* a, void* item);

/**
 * Add a list of items to the end of the list.
 *
 * "n_items" are taken from the "items" list and inserted into the list.
 */
void PtrList_extend(PtrList* a, void** items, unsigned int n_items);

/**
 * Insert "item" into the list at index "pos".
 *
 * Items to the right of "pos" must be shifted, so this can be an expensive
 * operation.
 *
 * Returns true if the item was inserted. Return false if the given position
 * was out of range.
 */
bool PtrList_insert(PtrList* a, unsigned int pos, void* item);

/**
 * Remove the item at position "pos".
 *
 * Items to the right of "pos" must be shifted, so this can be an expensive
 * operation.
 *
 * Returns NULL if pos is out of bounds.
 */
void* PtrList_delete(PtrList* a, unsigned int pos);

/**
 * Returns the list item at index "pos".
 */
void* PtrList_get(const PtrList* a, unsigned int pos);

/**
 * Returns the list item at index "pos".
 *
 * Warning: No bounds checking is done.
 */
static inline void* PtrList_GET(const PtrList* a, unsigned int pos) {
    return a->items[pos];
}

/**
 * Sets the list item at index "pos" to value.
 *
 * Return true if the item was set, or false if "pos" was out of bounds.
 */
bool PtrList_set(PtrList* a, unsigned int pos, void* item);

/**
 * Sets the list item at index "pos" to value.
 *
 * Warning: No bounds checking is done.
 */
static inline void PtrList_SET(PtrList* a, unsigned int pos, void* item) {
    a->items[pos] = item;
}

/**
 * Remove the last item from the list and return it.
 *
 * Returns NULL if there are no items in the list.
 */
void* PtrList_pop(PtrList* a);

/**
 * Free PtrList created from PtrList_new().
 *
 * Data pointers inserted in the list are not free'd.
 */
void PtrList_free(PtrList* a);

/**
 * Create a PtrList like type called ``_listtype`` that stores pointers to
 * ``_type`` instead of void pointers. All functions defined are prefixed with
 * ``_listtype`` instead of ``PtrList``. Only static inline functions are
 * defined, so there is no need to create a ".c" file.
 */
#define PTRLIST_MAKE_HEADER(_listtype, _type) \
\
    typedef PtrList _listtype; \
\
    static inline _listtype* _listtype##_new() { \
        return (_listtype*) PtrList_new(); \
    } \
\
    static inline void _listtype##_append(_listtype* a, _type* item) { \
        PtrList_append((PtrList*) a, (void*) item); \
    } \
\
    static inline void _listtype##_extend(_listtype* a, _type** items, unsigned int n_items) { \
        PtrList_extend((PtrList*) a, (void**) items, n_items); \
    } \
\
    static inline bool _listtype##_insert(_listtype* a, unsigned int pos, _type* item) { \
        return PtrList_insert((PtrList*) a, pos, (void*) item); \
    } \
\
    static inline _type* _listtype##_delete(_listtype* a, unsigned int pos) { \
        return (void*) PtrList_delete((PtrList*) a, pos); \
    } \
\
    static inline _type* _listtype##_get(const _listtype* a, unsigned int pos) { \
        return (void*) PtrList_get((PtrList*) a, pos); \
    } \
\
    static inline _type* _listtype##_GET(const _listtype* a, unsigned int pos) { \
        return ((PtrList*) (a))->items[pos]; \
    } \
\
    static inline bool _listtype##_set(_listtype* a, unsigned int pos, _type* item) { \
        return PtrList_set((PtrList*) a, pos, (void*) item); \
    } \
\
    static inline void _listtype##_SET(_listtype* a, unsigned int pos, _type* item) { \
        ((PtrList*) a)->items[pos] = (void*) item; \
    } \
\
    static inline _type* _listtype##_pop(_listtype* a) { \
        return (void*) PtrList_pop((PtrList*) a); \
    } \
\
    static inline void _listtype##_free(_listtype* a) { \
        PtrList_free((PtrList*) a); \
    }

#endif
