#include <stdlib.h>
#include <string.h>

#include "psyrender.h"

// Private prototypes
static void PtrArray_consider_resize(PtrArray* a, unsigned int new_size);


PtrArray* PtrArray_new() {
    PtrArray* a = (PtrArray*) malloc(sizeof(PtrArray));
    a->n_allocated = 0;
    a->len = 0;
    a->items = NULL;
    return a;
}

/**
 * Internal use only!
 *
 * Consider resizing the array. Afterwards there will be space for at least
 * "new_size" items.
 *
 * Called before insertion to make sure there is enough allocated room. Called
 * after deletion to reclaim space if needed.
 */
static void PtrArray_consider_resize(PtrArray* a, unsigned int new_size) {
    // Always resize to exactly new_size for now. Improvements to this later.
    //TODO: Don't always resize
    a->items = (void**) realloc((void*) a->items, new_size*sizeof(void*));
    a->n_allocated = new_size;
}

void PtrArray_append(PtrArray* a, void* item) {
    PtrArray_consider_resize(a, a->len+1);
    a->items[a->len] = item;
    a->len++;
}

void PtrArray_extend(PtrArray* a, void** items, unsigned int n_items) {
    PtrArray_consider_resize(a, a->len + n_items);
    memcpy((void*) &a->items[a->len], (void*) items, n_items*sizeof(void*));
    a->len += n_items;
}

bool PtrArray_insert(PtrArray* a, unsigned int pos, void* item) {
    if(pos > a->len) {
        return false;
    }
    PtrArray_consider_resize(a, a->len+1);
    memmove((void*) &a->items[pos+1], (void*) &a->items[pos], (a->len - pos)*sizeof(void*));
    a->items[pos] = item;
    a->len++;
    return true;
}

void* PtrArray_delete(PtrArray* a, unsigned int pos) {
    if(pos >= a->len) {
        return NULL;
    }
    void* item = PtrArray_GET(a, pos);
    memmove((void*) &a->items[pos], (void*) &a->items[pos+1], (a->len - pos - 1)*sizeof(void*));
    a->len--;
    PtrArray_consider_resize(a, a->len);
    return item;
}

void* PtrArray_get(const PtrArray* a, unsigned int pos) {
    if(pos < a->len) {
        return a->items[pos];
    } else {
        return NULL;
    }
}

bool PtrArray_set(PtrArray* a, unsigned int pos, void* item) {
    if(pos < a->len) {
        a->items[pos] = item;
        return true;
    } else {
        return false;
    }
}

void* PtrArray_pop(PtrArray* a) {
    if(a->len == 0) {
        return NULL;
    }
    void* item = a->items[a->len-1];
    a->len--;
    PtrArray_consider_resize(a, a->len);
    return item;
}

void PtrArray_free(PtrArray* a) {
    free(a->items);
    free(a);
}
