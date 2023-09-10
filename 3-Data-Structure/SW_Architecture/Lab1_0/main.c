#include <stdio.h>
#include <stdlib.h>

// Global variables
unsigned int g_distance, g_speed;
// Global Constant
unsigned int THR = 50;

// states enumuration
enum
{
    e_waiting,
    e_driving
} state_id;

// states prototype
#define STATE_def(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_) ST_##_stateFunc_

STATE_def(waiting);
STATE_def(driving);
int get_distance();
void set_speed(int speed);

// ptr to func.
void (*ptr_f_state)();

STATE_def(waiting)
{
    // state actions
    state_id = e_driving;
    g_speed = 30;
    g_distance = get_distance();
    // check event
    (g_distance <= THR) ? (ptr_f_state = STATE(waiting)) : (ptr_f_state = STATE(driving));
    printf("waiting state: distance = %d | speed = %d", g_distance, g_speed);
}

int get_distance()
{
    return (rand() % (45 - 55 + 1) + 1);
}

void set_speed(int speed)
{
    g_speed = speed;
}


void init_setup()
{
    // init_DC_motor
    // init_US
    ptr_f_state = STATE(waiting);
}

void main() {
    volatile int cnt = 0;
    init_setup();
    for(int i = 0; i < 1000; i++) {
        ptr_f_state();
        for ( cnt = 0; cnt < 1000; cnt++);
    }
}