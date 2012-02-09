#include "reverse.h"
#include <assert.h>

/**
 * Initializes a list of nodes and ensures that the terminal node points to nil. If the terminal
 * node is not considered explicitly, it can lead to undefinded behaviour!
 */
node* init (long size)
{
    node *list = (size > 0) ? new node[size] : 0;

    for (int index=0; index<size-1; index++)
    {
        node* curr = &list[index];
        node* next = &list[index+1];
        curr->next = next;
    }

    if (size > 0)
    {
        list[size-1].next = 0; //!!
    }
    
    return list;
}

/**
 * De-allocates reserved memory; C/C++ requires explicit de-allocation!
 */
void free (node *list)
{
    delete[] list; //!!
}

/**
 * Enumerates the data part for each node in the list, whereas the enumaration start with one
 * (and not with zero).
 */
node *label (node *list)
{
    long index = 1;
    node* head = list;

    while (list != 0)
    {
        list->data = index++;
        list = list->next;
    }

    return head;
}

/**
 * Reverses a given list of nodes; empty or single noded lists are also reversed properly.
 */
node *reverse (node *list)
{
    node *prev = list;
    if (prev == 0) return list; //!!
    node *curr = list->next;
    if (curr == 0) return list; //!!

    prev->next = 0; while (true)
    {
        if (curr->next)
        {
            node *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        else
        {
            curr->next = prev;
            break;
        }
    }

    return curr;
}

/**
 * Reverses each consecutive sub-list of size n from list and returns their concatenation. If
 * the sub-lists are of null size or the list is empty then simply the original list is 
 * returned. A *recursive* approach is used.
 */
node *recurse (int n, node *list)
{
    if (n == 0) return list; //!!
    if (list == 0) return list; //!!

    long index = 0;
    node *head = list;
    node *curr = head;

    while (curr->next != 0 && ++index % n != 0)
    {
        curr = curr->next;
    }

    if (index < n)
    {
        return reverse (head);
    }
    else
    {
        node *temp = curr->next;
        curr->next = 0;
        list = reverse (head);
        head->next = recurse (index, temp);

        return list;
    }
}

/**
 * Reverses a sub-list from head to tail and properly *re-wires* the reversed sub-list.
 */
node *reverse (node* prev, node *head, node *tail, node *next)
{
    assert (tail != 0);
    tail->next = 0;

    assert (head != 0);
    reverse (head);

    if (prev != 0) prev->next = tail;
    if (next != 0) head->next = next;

    return (prev != 0) ? prev : tail;
}

/**
 * Reverses each consecutive sub-list of size n from list and returns their concatenation. If
 * the sub-lists are of null size or the list is empty then simply the original list is
 * returned. A *iterative* approach is used.
 */
node *iterate (int n, node* list)
{
    if (n <= 1) return list; //!!
    int index = 0;

    node *prev = 0;
    node *head = list;
    node *tail = list;
    node *next = 0;

    node *curr = head; while (curr && curr->next != 0) //!!
    {
        while (curr->next != 0 && ++index % n != 0)
        {
            curr = curr->next;
            tail = curr;
            next = tail->next;
        }

        if (index <= n)
        {
            list = reverse (prev, head, tail, next);
            assert (list != 0);
        }
        else
        {
            prev = reverse (prev, head, tail, next);
            assert (prev != 0);
        }

        prev = head;
        head = next;
        curr = next;
    }

    return list;
}
