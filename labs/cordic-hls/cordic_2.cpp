#include "cordic_2.h"

// arctan(2^-i) for i = 0..11 (單位：弧度)
static const THETA_TYPE cordic_phase[NUM_ITERATIONS] = {
    0.785, // arctan(1)         = 45°
    0.463, // arctan(0.5)       ≈ 26.565°
    0.244,// arctan(0.25)      ≈ 14.036°
    0.124,// arctan(0.125)     ≈ 7.125°
    0.0624,// arctan(0.0625)    ≈ 3.576°
    0.0312,// arctan(0.03125)  ≈ 1.7899°
};

void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
{
    // K 值 (6 次迭代後的累積縮放因子)，約 0.607252935
    COS_SIN_TYPE x = 0.607252935;
    COS_SIN_TYPE y = 0.0;
    THETA_TYPE z = theta;

    // 在迴圈外插入 pipeline 指示，盡量降低每個迭代的組合邏輯延遲
    #pragma HLS PIPELINE II=1
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int d = (z >= 0.0) ? 1 : -1;

        // 使用 >> 取代除法 (y >> i 表示 y 除以 2^i)
        //COS_SIN_TYPE x_new = x - d * (y >> i);
        //COS_SIN_TYPE y_new = y + d * (x >> i);

        COS_SIN_TYPE x_new = x - d * (y / (1 << i));
        COS_SIN_TYPE y_new = y + d * (x / (1 << i));
		
        x = x_new;
        y = y_new;
        z = z - d * cordic_phase[i];
    }

    c = x;
    s = y;
}