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
事件B    s1      s2       s2
事件C    s1      s2       s3
事件D    s3      s1       s3

*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_STATE 3
#define NUM_EVNET 4

enum state
{
    state1,
    state2,
    state3
};

enum event
{
    event_A,
    event_B,
    event_C,
    event_D
};

enum state state_matrix[NUM_EVNET][NUM_STATE] =
{
    //state1 state2 state3
    {state2, state3, state1}, //event_A
    {state1, state2, state2}, //event_B
    {state1, state2, state3}, //event_C
    {state3, state1, state3}  //event_D
};

typedef void (*func_cb)(void);


void state1_cb();
void state2_cb();
void state3_cb();

func_cb cb[NUM_STATE] =
{
    state1_cb,
    state2_cb,
    state3_cb
};

void state1_cb()
{
    printf("state 111\n");
}

void state2_cb()
{
    printf("state 222\n");
}

void state3_cb()
{
    printf("state 333\n");
}

void state_change(unsigned char event)
{
    last_state = state_matrix[event][last_state];
}

void state_out(void)
{
    cb[last_state]();
}

#define true 1
unsigned char last_state = state1;
void state_machine(unsigned char event, unsigned char update)
{
    if (update == true)
        state_change(event);
    printf("last_state = %d\n", last_state);
    state_out();
}


void test(void)
{
    // emitted event_A
    unsigned char event = event_A;
    state_machine(event, true);
    state_machine(event_B, true);
}

int main()
{
    test();


    return 0;
}
