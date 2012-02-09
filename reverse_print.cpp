#include "reverse_print.h"

void print (std::string label, node *list)
{
    std::cout << label;

    node *curr = list;
    while (curr != 0)
    {
        std::cout << curr->data << "; ";
        curr = curr->next;
    }

    std::cout << "\n";
}
