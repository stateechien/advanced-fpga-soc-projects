// cordic.h - Header file for CORDIC algorithm
#ifndef CORDIC_H
#define CORDIC_H

#include <iostream>
#include <cmath>
#include <ap_fixed.h>

// 在此定義迭代次數
#define NUM_ITERATIONS 6

// Baseline 版本使用 double
typedef ap_fixed<16,2> COS_SIN_TYPE;
typedef ap_fixed<16,2> THETA_TYPE;


void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c);

#endif // CORDIC_H

