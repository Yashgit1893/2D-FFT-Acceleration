#include "fft.h"
#include <stdio.h>
#include <sys/time.h>
int main() {
    // struct timeval start, end;
    // long seconds, useconds;
    // double mtime;

    // gettimeofday(&start, NULL);

    Complex data[SIZE][SIZE];
    // Initialize your data here
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            data[row][col].real = row + col;  // Example initialization
            data[row][col].imag = 0.0;
        }
    }

    // Print input data
    printf("Input data:\n");
    for (int print_row = 0; print_row < SIZE; print_row++) {
        for (int print_col = 0; print_col < SIZE; print_col++) {
            printf("(%f, %f) ", data[print_row][print_col].real, data[print_row][print_col].imag);
        }
        printf("\n");
    }
    
    fft2D(data);

    // Print transformed data
    printf("Transformed data:\n");
    for (int result_row = 0; result_row < SIZE; result_row++) {
        for (int result_col = 0; result_col < SIZE; result_col++) {
            printf("(%f, %f) ", data[result_row][result_col].real, data[result_row][result_col].imag);
        }
        printf("\n");
    }
    // gettimeofday(&end, NULL);

    // seconds = end.tv_sec - start.tv_sec;
    // useconds = end.tv_usec - start.tv_usec;
    // mtime = ((seconds) * 1000 + useconds/1000.0);

    // printf("2DFFT took %f milliseconds to execute \n", mtime);
    return 0;
}
