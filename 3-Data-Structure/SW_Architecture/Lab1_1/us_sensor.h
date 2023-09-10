

#ifndef US_H_
#define US_H

enum {
    US_waiting
}US_state_id;

#define STATE_def(_statename_) ST_##_statename_()
#define STATE(_statename_) ST_##_statename



STATE_def(waiting);













#endif