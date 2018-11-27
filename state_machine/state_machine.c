#include "state_machine.h"

/*

初始节点
终止节点
状态节点
事件
状态行为

每个状态节点对应一个状态行为
根据事件的发生进行状态转移

状态转移图:
         s1      s2       s3
事件A    s2      s3       s1
事件B    s1      s2       s1
事件C    s1      s2       s3
事件D    ...

*/
 
 
#include <stdio.h>
#include <stdlib.h>

enum state  {
    state0,
    state1,
    state2
};


enum event  {
    event_A,
    event_B,
    event_C,
    event_D
};

#define state_num 4
typedef void (*func )(void);
typedef struct __state_node {
    unsigned char next_state[state_num];
    func cb;
}state_node;

void state0_cb()
{
    printf("state 000\n");
}

void state1_cb()
{
    printf("state 111\n");
}

void state2_cb()
{
    printf("state 222\n");
}



state_node s_node[3] = {
    {
        .next_state = {state0,state2,state0,state0},
        .cb = state0_cb
    },//state0
    {
        .next_state = {state1,state1,state0,state2},
        .cb = state1_cb
    },//state1
    {
        .next_state = {state0,state2,state2,state2},
        .cb = state2_cb
    }//state2
};


#define true 1
unsigned char last_state = state0;
void state_machine(unsigned char event, unsigned char update){
    if(update == true)
        last_state = s_node[last_state].next_state[event];
    printf("last_state = %d\n", last_state);
    s_node[last_state].cb();
}


void test(void)
{



    // emitted event_A
    unsigned char event = event_A;
    state_machine(event, true);


}

int main()
{
    //test();
    state_machine(event_B, 1);

    return 0;
}
