/**
 * linked_list.c
 * A singly linked list data structure.
 *
 * The list stores void pointers, so you can store anything you want.  Remember
 * to free the memory pointed to by the stored pointer before deleting the node
 * with List_remove_current().  Alternatively you canuse
 * List_remove_current_and_data().
 *
 * To iterate through the list, use List_start_iteration() and List_next() as
 * shown in this example:
 *
 *   List_start_iteration(bullets);
 *   Bullet* bullet;
 *   while ((bullet = (Bullet*) List_next(bullets)))
 *   {
 *       Bullet_draw(bullet);
 *   }
 *
 * This implementation is slow for large lists.  It could be expanded to
 * allocate memory in chunks if extra speed is needed.
 */

#include <stdlib.h>
#include <stdio.h>

#include "psyrender.h"

/**
 * List_new
 * Create a new, empty List.
 */
List* List_new() {
    List* l = (List*) malloc(sizeof(List));
    if (!l) {
        printf("Could not allocate memory!\n");
        printf("    In List_new()\n");
        exit(1);
    }

    l->head = NULL;
    l->tail = NULL;
    l->length = 0;

    return l;
}

/**
 * List_append
 * Adds the given item to the end of the list.
 */
void List_append(List* l, void* data)
{
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;

    if (l->length == 0) {
        l->head = node;
    } else {
        l->tail->next = node;
    }
    l->tail = node;
    l->length++;
}

/**
 * List_free
 * Free the memory used by the list.
 *
 * Notice that the items that are stored in the list are not freed, that must
 * be done by the user.
 */
void List_free(List* l) {
    ListNode* node = l->head;
    ListNode* next;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(l);
}
