#include "rbtrees.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define NUM_NODES 32

int main()
{
    rbtrees rb;
    /* *insert */
    int i = 0,number = 0;
    int flag = 0;
    srand((unsigned) time(NULL));
    printf("insert node 32 number:\n");
    for (; i < NUM_NODES; i++) {
        number = rand() % (NUM_NODES + i);
        if(i == number){
            flag = i;
        }
        rb.insert(&number,sizeof(number));
    }
    rb.traverse();
    printf("traverse node %d: \n",flag);
    rb.traverse(&flag);
    printf("delete node %d: \n",flag);
    rb.erase(&flag);
    rb.traverse();
    return 0;
}


