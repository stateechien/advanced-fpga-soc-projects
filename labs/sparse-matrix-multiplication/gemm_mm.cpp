#include <ap_int.h>
#include <ap_fixed.h>

#define N 4

void gemm_mm(
    const float A[N][N],
    const float x[N],
    float y[N]
) {

#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS INTERFACE s_axilite port=A      bundle=CTRL
#pragma HLS INTERFACE s_axilite port=x      bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y      bundle=CTRL


#pragma HLS ARRAY_PARTITION variable=A complete dim=1
#pragma HLS ARRAY_PARTITION variable=A complete dim=2
#pragma HLS ARRAY_PARTITION variable=x complete dim=1
#pragma HLS ARRAY_PARTITION variable=y complete dim=1


#pragma HLS PIPELINE II=1


    float a00 = A[0][0], a01 = A[0][1], a02 = A[0][2], a03 = A[0][3];
    float a10 = A[1][0], a11 = A[1][1], a12 = A[1][2], a13 = A[1][3];
    float a20 = A[2][0], a21 = A[2][1], a22 = A[2][2], a23 = A[2][3];
    float a30 = A[3][0], a31 = A[3][1], a32 = A[3][2], a33 = A[3][3];
    float x0 = x[0], x1 = x[1], x2 = x[2], x3 = x[3];


    y[0] = a00*x0 + a01*x1 + a02*x2 + a03*x3;
    y[1] = a10*x0 + a11*x1 + a12*x2 + a13*x3;
    y[2] = a20*x0 + a21*x1 + a22*x2 + a23*x3;
    y[3] = a30*x0 + a31*x1 + a32*x2 + a33*x3;
}
