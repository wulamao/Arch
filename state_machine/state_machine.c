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

（为了优化开销，分离了状态与状态回调的绑定，需要人为保持顺序方便数组下标访问）

*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_STATE 3 //状态节点数
#define NUM_EVNET 4 //事件数

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

//状态转移图 数据表示
enum state state_matrix[NUM_EVNET][NUM_STATE] =
{
    //state1 state2 state3
    {state2, state3, state1}, //event_A
    {state1, state2, state2}, //event_B
    {state1, state2, state3}, //event_C
    {state3, state1, state3}  //event_D
};

typedef void (*func_cb)(void);

// 状态节点下的行为函数
void state1_cb();
void state2_cb();
void state3_cb();

//状态节点的转移函数
func_cb cb[NUM_STATE] =
{
    state1_cb,//state1
    state2_cb,//state2
    state3_cb //state3
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
    if (cb[last_state] != 0)
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

// 实现函数默认参数
#define DEFAULT(name, deval) ((#name[0])?name+0:deval) //
#define state_machine_(event, update) state_machine(event, DEFAULT(update, 1))

#define state_machine_default(event) state_machine(event, true)

void test(void)
{
    // emitted event_A
    unsigned char event = event_A;
    state_machine(event, true);
    state_machine_default(event_B);
    state_machine_(event_D,);
}

int main()
{
    test();


    return 0;
}
