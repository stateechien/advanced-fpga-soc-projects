#include <ap_int.h>
#include <ap_fixed.h>
#define N 4

extern void gemm_mm(const float A[N][N], const float x[N], float y[N]);

void csr_mm(const float x[N], float y[N]) {
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL
#pragma HLS INTERFACE s_axilite port=x      bundle=CTRL
#pragma HLS INTERFACE s_axilite port=y      bundle=CTRL
#pragma HLS PIPELINE II=1

    static const float A[N][N] = {
        {1.0f, 0.0f, 2.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 3.0f, 0.0f, 4.0f},
        {5.0f, 0.0f, 0.0f, 0.0f}
    };

    gemm_mm(A, x, y);
}
