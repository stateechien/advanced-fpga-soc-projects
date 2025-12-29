#include "block_mm.h"


#include <stdlib.h>
void blockmatmul(hls::stream<blockvec> &Arows, hls::stream<blockvec> &Bcols,hls::stream<blockmat> &ABpartial, int it) {



    DTYPE AB[BLOCK_SIZE][BLOCK_SIZE] = { 0 };
    #pragma HLS ARRAY_PARTITION variable=AB complete dim=0
	
    #pragma HLS DATAFLOW
    int counter = it % (SIZE/BLOCK_SIZE);
    static DTYPE A[BLOCK_SIZE][SIZE];
	#pragma HLS ARRAY_PARTITION variable=A complete dim=1
	
    //only load the A rows
	if(counter == 0){
		loadA:
        for(int i = 0; i < BLOCK_SIZE; i++){
		blockvec tempA = Arows.read();
		    for(int j =0; j < SIZE; j++){
			#pragma HLS PIPELINE II=1
			A[i][j] = tempA.a[j];
		    }
		}			
	}

    partialsum: 
    for(int k =0; k < SIZE; k++){
		blockvec tempB = Bcols.read();
		for(int i = 0; i < BLOCK_SIZE; i++){
			for(int j = 0; j < BLOCK_SIZE; j++){
				#pragma HLS UNROLL
				AB[i][j] += A[i][k] * tempB.a[j];
			}
		}
	}
	
    writeoutput:
	blockmat temp_blockmat;
	for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
        	temp_blockmat.out[i][j] = AB[i][j];
        }
    }
	ABpartial.write(temp_blockmat);
}
