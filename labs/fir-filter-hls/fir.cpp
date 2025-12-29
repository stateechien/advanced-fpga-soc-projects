/*******************************************************************************
Vendor: Xilinx 
Associated Filename: fir.c
Purpose: Vivado HLS Tutorial Example 
Device: All 
Revision History: May 30, 2008 - initial release
                                                
*******************************************************************************
Copyright 2008 - 2012 Xilinx, Inc. All rights reserved. 

This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer assumes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/
#include "fir.h"

void fir (data_t *y, data_t x) {

  const coef_t c[N] = {
  1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,
  8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,
  16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,
  24,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,
  32,33,33,34,34,35,35,36,36,37,37,38,38,39,39,40,
  40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,
  48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,
  56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,
  64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,
  72,73,73,74,74,75,75,76,76,77,77,78,78,79,79,80,
  80,81,81,82,82,83,83,84,84,85,85,86,86,87,87,88,
  88,89,89,90,90,91,91,92,92,93,93,94,94,95,95,96,
  96,97,97,98,98,99,99,100,100,101,101,102,102,103,103,104,
  104,105,105,106,106,107,107,108,108,109,109,110,110,111,111,112,
  112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,120,
  120,121,121,122,122,123,123,124,124,125,125,126,126,127,127,127,
  127,127,127,126,126,125,125,124,124,123,123,122,122,121,121,120,
  120,119,119,118,118,117,117,116,116,115,115,114,114,113,113,112,
  112,111,111,110,110,109,109,108,108,107,107,106,106,105,105,104,
  104,103,103,102,102,101,101,100,100,99,99,98,98,97,97,96,
  96,95,95,94,94,93,93,92,92,91,91,90,90,89,89,88,
  88,87,87,86,86,85,85,84,84,83,83,82,82,81,81,80,
  80,79,79,78,78,77,77,76,76,75,75,74,74,73,73,72,
  72,71,71,70,70,69,69,68,68,67,67,66,66,65,65,64,
  64,63,63,62,62,61,61,60,60,59,59,58,58,57,57,56,
  56,55,55,54,54,53,53,52,52,51,51,50,50,49,49,48,
  48,47,47,46,46,45,45,44,44,43,43,42,42,41,41,40,
  40,39,39,38,38,37,37,36,36,35,35,34,34,33,33,32,
  32,31,31,30,30,29,29,28,28,27,27,26,26,25,25,24,
  24,23,23,22,22,21,21,20,20,19,19,18,18,17,17,16,
  16,15,15,14,14,13,13,12,12,11,11,10,10,9,9,8,
  8,7,7,6,6,5,5,4,4,3,3,2,2,1,1,0
  };
  
  #pragma HLS ARRAY_PARTITION variable=c cyclic factor=8 dim=1
  
  #pragma HLS INTERFACE s_axilite port=return bundle=control
  #pragma HLS INTERFACE s_axilite port=x bundle=control
  #pragma HLS INTERFACE s_axilite port=y bundle=control
  static data_t shift_reg[N];
    #pragma HLS ARRAY_PARTITION variable=shift_reg cyclic factor=8 dim=1

  static bool initialized = false;

  if (!initialized) {
    for (int i = 0; i < N; ++i)
      shift_reg[i] = 0;
    initialized = true;
  }
  
  acc_t acc = 0;
  //data_t data;
  int i;
 

  #pragma HLS PIPELINE II=1
  TDL:for(i = N-1; i >0; i--){
  #pragma HLS UNROLL factor=8
	  shift_reg[i] = shift_reg[i-1];
  }
  shift_reg[0] = x;

  
  MAC:for(i = 0; i < N; i++){
  #pragma HLS UNROLL factor=8
  //#pragma HLS PIPELINE
  //#pragma HLS UNROLL factor=4 skip_exit_check
  	  acc += c[i] * (shift_reg[i]);
  }

/*
  #pragma HLS PIPELINE II=1
  MAC:for(i = 0; i < N/2; i++){
  //#pragma HLS UNROLL factor=8
	  acc += c[i] * (shift_reg[i]+shift_reg[N-1-i]);
  }
*/
  
  //acc += c[N/2] * shift_reg[N/2];
  *y=acc;
}


