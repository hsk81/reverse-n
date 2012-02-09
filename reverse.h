#ifndef REVERSE_H
#define	REVERSE_H

typedef struct node
{
    long data;
    struct node *next;
} node;

node* init (long size);
node *label (node *list);
node *reverse (node *list);
node *recurse (int n, node *list);
node *reverse (node* prev, node *head, node *tail, node *next);
node *iterate (int n, node* list);

#endif	/* REVERSE_H */
