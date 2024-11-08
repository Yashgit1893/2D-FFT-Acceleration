#include "fft.h"
#include <math.h>


void fft2D(Complex data[SIZE][SIZE]) {
#pragma HLS array_partition complete
//#pragma HLS PIPELINE

    // Perform FFT on rows
    for (int row = 0; row < SIZE; row++) {
//#pragma HLS LOOP_FLATTEN
//#pragma HLS PIPELINE II=1

        Complex row_data[SIZE];
#pragma HLS array_partition complete

        for (int row_data_index = 0; row_data_index < SIZE; row_data_index++) {
#pragma HLS PIPELINE

            row_data[row_data_index] = data[row][row_data_index];
        }

        for (int stage_row = 1; stage_row < SIZE; stage_row *= 2) {
//#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

            for (int k_row = 0; k_row < stage_row; k_row++) {
//#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

                double angle = -2 * PI * k_row / (2 * stage_row);
                Complex w = { cos(angle), sin(angle) };

                for (int row_data_index_k = k_row; row_data_index_k < SIZE; row_data_index_k += 2 * stage_row) {
//#pragma HLS EXPRESSION_BALANCE
//#pragma HLS PIPELINE
//#pragma HLS UNROLL
//#pragma HLS LOOP_FLATTEN

                    Complex t = {
                        w.real * row_data[row_data_index_k + stage_row].real - w.imag * row_data[row_data_index_k + stage_row].imag,
                        w.real * row_data[row_data_index_k + stage_row].imag + w.imag * row_data[row_data_index_k + stage_row].real
                    };
                    Complex u = row_data[row_data_index_k];
                    row_data[row_data_index_k] = (Complex){ u.real + t.real, u.imag + t.imag };
                    row_data[row_data_index_k + stage_row] = (Complex){ u.real - t.real, u.imag - t.imag };
                }
            }
        }

        for (int final_row_index = 0; final_row_index < SIZE; final_row_index++) {
//#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

            data[row][final_row_index] = row_data[final_row_index];
        }
    }

    // Perform FFT on columns
    for (int col = 0; col < SIZE; col++) {
//#pragma HLS LOOP_FLATTEN
//#pragma HLS PIPELINE II=1

        Complex col_data[SIZE];
//#pragma HLS array_partition complete

#pragma HLS ARRAY_PARTITION variable=col_data complete dim=1
        for (int col_data_index = 0; col_data_index < SIZE; col_data_index++) {
#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

            col_data[col_data_index] = data[col_data_index][col];
        }

        for (int stage_col = 1; stage_col < SIZE; stage_col *= 2) {
//#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

            for (int k_col = 0; k_col < stage_col; k_col++) {
//#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

                double angle = -2 * PI * k_col / (2 * stage_col);
                Complex w = { cos(angle), sin(angle) };

                for (int col_data_index_k = k_col; col_data_index_k < SIZE; col_data_index_k += 2 * stage_col) {
//#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN
//#pragma HLS UNROLL
//#pragma HLS EXPRESSION_BALANCE

                	Complex t = {
                        w.real * col_data[col_data_index_k + stage_col].real - w.imag * col_data[col_data_index_k + stage_col].imag,
                        w.real * col_data[col_data_index_k + stage_col].imag + w.imag * col_data[col_data_index_k + stage_col].real
                    };
                    Complex u = col_data[col_data_index_k];
                    col_data[col_data_index_k] = (Complex){ u.real + t.real, u.imag + t.imag };
                    col_data[col_data_index_k + stage_col] = (Complex){ u.real - t.real, u.imag - t.imag };
                }
            }
        }

        for (int final_col_index = 0; final_col_index < SIZE; final_col_index++) {
//#pragma HLS DEPENDENCE dependent=false type=inter
#pragma HLS PIPELINE
//#pragma HLS LOOP_FLATTEN

            data[final_col_index][col] = col_data[final_col_index];
        }
    }

    return ;
}
