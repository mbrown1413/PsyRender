/**
 * .. todo:: Document Linked List
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ListNode_struct ListNode;

struct ListNode_struct {
    void* data; // The data stored by this node
    ListNode* next; // The next node in the linked list
};

typedef struct {
    ListNode* head; // The first item in the list
    ListNode* tail; // The last item in the list
    unsigned int length; // Number of items in the list
} List;

List* List_new();
void List_append(List* l, void* data);
void List_free(List* l);

#endif
