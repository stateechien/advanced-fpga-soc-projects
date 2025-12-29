// src/helloworld.c
#include "xparameters.h"
#include "xcsr_mm_hw.h"
#include "xgemm_mm_hw.h"
#include "xil_io.h"
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include <stdint.h>

#define N 4

int main() {
    // 1) 取两路 IP 的基址
    const uint32_t baseCSR = XPAR_CSR_MM_0_S_AXI_CTRL_BASEADDR;
    const uint32_t baseGEM = XPAR_GEMM_MM_0_S_AXI_CTRL_BASEADDR;

    // 2) 测试数据
    float x[N] = {1,2,3,4};
    float A[N][N] = {
        {1,0,2,0},
        {0,0,0,0},
        {0,3,0,4},
        {5,0,0,0}
    };
    float y_csr[N], y_gem[N];
    XTime t0, t1;
    uint32_t tmp;

    // ======== CSR SpMV IP ========
    // 写 x[0..3]
    Xil_Out32(baseCSR + XCSR_MM_CTRL_ADDR_X_0_DATA, *(uint32_t*)&x[0]);
    Xil_Out32(baseCSR + XCSR_MM_CTRL_ADDR_X_1_DATA, *(uint32_t*)&x[1]);
    Xil_Out32(baseCSR + XCSR_MM_CTRL_ADDR_X_2_DATA, *(uint32_t*)&x[2]);
    Xil_Out32(baseCSR + XCSR_MM_CTRL_ADDR_X_3_DATA, *(uint32_t*)&x[3]);
    // 启动
    Xil_Out32(baseCSR + XCSR_MM_CTRL_ADDR_AP_CTRL, 1);
    // 计时并等 ap_done
    XTime_GetTime(&t0);
    while ((Xil_In32(baseCSR + XCSR_MM_CTRL_ADDR_AP_CTRL) & 0x2) == 0) { }
    XTime_GetTime(&t1);
    xil_printf("CSR SpMV cycles: %u\r\n", (uint32_t)(t1 - t0));
    // 读 y[0..3]
    tmp = Xil_In32(baseCSR + XCSR_MM_CTRL_ADDR_Y_0_DATA); y_csr[0] = *(float*)&tmp;
    tmp = Xil_In32(baseCSR + XCSR_MM_CTRL_ADDR_Y_1_DATA); y_csr[1] = *(float*)&tmp;
    tmp = Xil_In32(baseCSR + XCSR_MM_CTRL_ADDR_Y_2_DATA); y_csr[2] = *(float*)&tmp;
    tmp = Xil_In32(baseCSR + XCSR_MM_CTRL_ADDR_Y_3_DATA); y_csr[3] = *(float*)&tmp;

    // ======== Dense GEMM IP ========
    // 写矩阵 A 的 16 个元素（按 A[row][col] 展平）
    uint32_t *pA = (uint32_t*)A;
    // 先写第 0 行
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_0_0_DATA, pA[0]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_0_1_DATA, pA[1]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_0_2_DATA, pA[2]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_0_3_DATA, pA[3]);
    // 写第 1 行
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_1_0_DATA, pA[4]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_1_1_DATA, pA[5]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_1_2_DATA, pA[6]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_1_3_DATA, pA[7]);
    // 写第 2 行
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_2_0_DATA, pA[8]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_2_1_DATA, pA[9]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_2_2_DATA, pA[10]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_2_3_DATA, pA[11]);
    // 写第 3 行
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_3_0_DATA, pA[12]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_3_1_DATA, pA[13]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_3_2_DATA, pA[14]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_A_3_3_DATA, pA[15]);

    // 写 x[0..3]
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_X_0_DATA, *(uint32_t*)&x[0]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_X_1_DATA, *(uint32_t*)&x[1]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_X_2_DATA, *(uint32_t*)&x[2]);
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_X_3_DATA, *(uint32_t*)&x[3]);

    // 启动
    Xil_Out32(baseGEM + XGEMM_MM_CTRL_ADDR_AP_CTRL, 1);
    // 计时并等 ap_done
    XTime_GetTime(&t0);
    while ((Xil_In32(baseGEM + XGEMM_MM_CTRL_ADDR_AP_CTRL) & 0x2) == 0) { }
    XTime_GetTime(&t1);
    xil_printf("Dense GEMM cycles: %u\r\n", (uint32_t)(t1 - t0));

    // 读 y[0..3]
    tmp = Xil_In32(baseGEM + XGEMM_MM_CTRL_ADDR_Y_0_DATA); y_gem[0] = *(float*)&tmp;
    tmp = Xil_In32(baseGEM + XGEMM_MM_CTRL_ADDR_Y_1_DATA); y_gem[1] = *(float*)&tmp;
    tmp = Xil_In32(baseGEM + XGEMM_MM_CTRL_ADDR_Y_2_DATA); y_gem[2] = *(float*)&tmp;
    tmp = Xil_In32(baseGEM + XGEMM_MM_CTRL_ADDR_Y_3_DATA); y_gem[3] = *(float*)&tmp;

    // ======== 打印结果 ========
    xil_printf("CSR y: %3d %3d %3d %3d\r\n", (int)y_csr[0], (int)y_csr[1], (int)y_csr[2], (int)y_csr[3]);

    xil_printf("GEM y: %3d %3d %3d %3d\r\n", (int)y_gem[0], (int)y_gem[1], (int)y_gem[2], (int)y_gem[3]);

    return 0;
}
