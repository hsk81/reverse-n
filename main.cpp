#include <stdlib.h>
#include <iostream>

#include "reverse.h"
#include "reverse_print.h"

#define LIST_SIZE (500000)
#define PARTITION (3)

int main (int argc, char** argv)
{
    node *initial_list, *labeled_list, *reversed_list;

    ///////////////////////////////////////////////////////////////////////////////////////////
    
    std::cout << "ITERATIVE APPROACH [SIZE=" << LIST_SIZE << "]: .. ";

    initial_list = init (LIST_SIZE);
    labeled_list = label (initial_list);
    reversed_list = iterate (PARTITION, labeled_list);
    //print ("* ITERATED LIST: ", reversed_list);

    free (initial_list);
    std::cout << "done! ;P" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "RECURSIVE APPROACH [SIZE=" << LIST_SIZE << "]: .. ";

    initial_list = init (LIST_SIZE);
    labeled_list = label (initial_list);
    reversed_list = recurse (PARTITION, labeled_list);
    //print ("* RECURSED LIST: ", reversed_list);
    
    free (initial_list);
    std::cout << "done! ;P" << std::endl;
}
