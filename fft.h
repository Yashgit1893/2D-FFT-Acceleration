#ifndef FFT_H
#define FFT_H
#define PI 3.14159265358979323846
#define SIZE 2  // Example size, adjust as needed
typedef struct {
    double real;
    double imag;
} Complex;

void fft2D(Complex data[SIZE][SIZE]);

#endif
