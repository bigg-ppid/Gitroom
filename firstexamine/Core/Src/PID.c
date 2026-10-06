//
// Created by king on 2026/10/5.
//
#include "PID.h"
void PID_Update(PID_t *p) {
    p->error1 = p->error0;
    p->error0 = p->target - p->actual;
    if (p->Ki != 0) {
        p->errorint += p->error0;
    }
    else {
        p->errorint =0;
    }
    p->out = p->Kp * p->error0 + p->Ki * p->errorint + p->Kd * (p->error0 - p->error1);
    if (p->out > p->outmax) {p->out = p->outmax;}
    else if (p->out < p->outmin) {p->out = p->outmin;}
}
