#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "reverse.h"
#include "reverse_print.h"

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#define STARTEED(test) (std::cout << "%TEST_STARTED% " \
    << (test) << " (reverse_test)" << std::endl)

#define FINISHED(test) (std::cout << "%TEST_FINISHED% time=0 " \
    << (test) << " (reverse_test)" << std::endl)

#define INIT(test, n) (std::cout \
    << (n) << " -- reverse_test" << "::" << (test) << std::endl)

#define FAIL(test, message) (std::cout << "%TEST_FAILED% time=0" << " " \
    << "testname=" << (test) << " " << "(reverse_test)" << " " \
    << "message=" << (message) \
    << std::endl)

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void test_compare (long run, long list_size, long partition) {
    INIT("test_compare", run);

    node *lhs_init = 0;
    node *lhs_list = 0;
    node *lhs_curr = 0;

    {
        node *initial_list = init (list_size);
        if (list_size > 0 && !initial_list) FAIL("test_compare", "!initial_list");
        node *labeled_list = label (initial_list);
        if (list_size > 0 && !labeled_list) FAIL("test_compare", "!labeled_list");
        node *iterate_list = iterate (partition, labeled_list);
        if (list_size > 0 && !iterate_list) FAIL("test_compare", "!iterate_list");

        lhs_init = initial_list;
        lhs_list = iterate_list;
        lhs_curr = iterate_list;
    }

    node *rhs_init = 0;
    node *rhs_list = 0;
    node *rhs_curr = 0;
    
    {
        node *initial_list = init (list_size);
        if (list_size > 0 && !initial_list) FAIL("test_compare", "!initial_list");
        node *labeled_list = label (initial_list);
        if (list_size > 0 && !labeled_list) FAIL("test_compare", "!labeled_list");
        node *recurse_list = recurse (partition, labeled_list);
        if (list_size > 0 && !recurse_list) FAIL("test_compare", "!recurse_list");
        
        rhs_init = initial_list;
        rhs_list = recurse_list;
        rhs_curr = recurse_list;
    }
    
    for (long index=0; index < list_size; index++)
    {
        if (!lhs_curr) { FAIL("test_compare", "!lhs_curr"); break; }
        if (!rhs_curr) { FAIL("test_compare", "!rhs_curr"); break; }

        if (lhs_curr->data != rhs_curr->data)
        {
            char message [256];
            sprintf(message, "(%d,%d) -- lhs_curr->data[%d] != rhs_curr->data[%d]",
                list_size, partition, lhs_curr->data, rhs_curr->data);
            FAIL("test_compare", message);

            print ("ITERATE LIST: ", lhs_list);
            print ("RECURSE LIST: ", rhs_list);

            break;
        }

        lhs_curr = lhs_curr->next;
        rhs_curr = rhs_curr->next;
    }

    free (lhs_init);
    free (rhs_init);
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#define MIN_LIST_SIZE (0)
#define MAX_LIST_SIZE (10)
#define MIN_PARTITION (0)
#define MAX_PARTITION (10)

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% reverse_test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    long n = 0; for (long list_size=MIN_LIST_SIZE; list_size<MAX_LIST_SIZE; list_size++)
    {
        for (long partition=MIN_PARTITION; partition<MAX_PARTITION; partition++)
        {
            STARTEED("test_compare");
            test_compare (n++, list_size, partition);
            FINISHED("test_compare");
        }
    }

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;
    return (EXIT_SUCCESS);
}
