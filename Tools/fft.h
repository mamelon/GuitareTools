#ifndef FFT_H
#define FFT_H

class Fft
{
public:

    static int fastlog2(int n);
    static void FORD2(int m, double *b);
    static void FORD1(int m, double *b);
    static void FR4TR(int in, int nn, double *b0, double *b1, double *b2, double *b3);
    static void FR2TR(int in, double *b0, double *b1);
    int _FFT(double b[], int n);
    int fastpurelog2(int n);


};

#endif // FFT_H
