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
    int i = 0,num = 0;
    char number[3] = {0};
    int flag = 0;
    srand((unsigned) time(NULL));
    printf("insert node 32 number:\n");
    for (; i < NUM_NODES; i++) {
        num = rand() % (NUM_NODES + i);
        if(i == num){
            flag = i;
        }
        sprintf(number,"%d",num);
        rb.insert(number,strlen(number));
    }
    rb.traverse();
    printf("traverse node %d: \n",flag);
    sprintf(number,"%d",flag);
    rb.traverse(number);
    printf("delete node %d: \n",flag);
    sprintf(number,"%d",flag);
    rb.erase(number);
    rb.traverse();
    return 0;
}


