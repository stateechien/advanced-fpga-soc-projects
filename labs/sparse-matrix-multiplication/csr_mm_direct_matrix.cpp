#include <ap_int.h>
#include <ap_fixed.h>

#define N 4

void csr_mm(
    const float x[N],
    float y[N]
) {
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS INTERFACE s_axilite port=x      bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y      bundle=CTRL


#pragma HLS PIPELINE II=1

#pragma HLS ARRAY_PARTITION variable=x complete dim=1
#pragma HLS ARRAY_PARTITION variable=y complete dim=1


    float x0 = x[0];
    float x1 = x[1];
    float x2 = x[2];
    float x3 = x[3];


    const float a00 = 1.0f;
    const float a02 = 2.0f;
    const float a21 = 3.0f;
    const float a23 = 4.0f;
    const float a30 = 5.0f;


    float r0 = a00 * x0 + a02 * x2;
    float r1 = 0.0f;
    float r2 = a21 * x1 + a23 * x3;
    float r3 = a30 * x0;


    y[0] = r0;
    y[1] = r1;
    y[2] = r2;
    y[3] = r3;
}
