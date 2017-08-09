#include "rbtrees.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM_NODES 32

int main()
{
    rbtrees rb;
    /* *insert */
    int i = 0;
    printf("insert node from 1 to NUM_NODES(32): \n");
    for (; i < NUM_NODES; i++) {
        rb.insert(&i,sizeof(i));
    }
    rb.traverse();
    /* *delete */
    printf("delete node 20: \n");
    int d = 20;
    rb.erase(&d);
    printf("delete node 10: \n");
    d = 10;
    rb.erase(&d);
    printf("delete node 15: \n");
    d = 15;
    rb.erase(&d);
    rb.traverse();
    return 0;
}


