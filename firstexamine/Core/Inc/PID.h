//
// Created by king on 2026/10/5.
//

#ifndef DIANJI_PID_H
#define DIANJI_PID_H
typedef struct {
    float actual;
    float target;
    float out;
    float error1;
    float error0;
    float errorint;
    float Ki;
    float Kp;
    float Kd;
    float outmax;
    float outmin;
}PID_t;
void PID_Update(PID_t *p);
#endif //DIANJI_PID_H
