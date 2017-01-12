#include "stdio.h"
#include "math.h"

#define PI 3.141592653589
#define N 128
#define M 7

typedef double ElemType;

typedef struct {
    ElemType real;
    ElemType imag;
} complex_a;


complex_a complex_xx(complex_a a, complex_a b)
{
    complex_a temp;
    temp.real = a.real * b.real-a.imag*b.imag;  
    temp.imag = b.imag*a.real + a.imag*b.real;
    return temp;
}


void rader_changer(complex_a buff[])
{
    int i,j,k;
    complex_a temp;
    complex_a *x = buff;
    
    for(j=0,i=0;i<N-1;i++) {  
        if(i<j) {  
            temp = x[j];  
            x[j]  = x[i];  
            x[i]  = temp;  
        }  
        k = N/2;               
        while(j >= k) {  
            j = j-k;               
            k = k/2;             
        }  
        j = j+k; 
    }
}


void FFT(complex_a buff[])
{  
    int L=0,B=0,J=0,K=0;  
    int step=0;  
    ElemType P=0,T=0;  
    complex_a W,Temp_XX,*data;  
    //ElemType TempResult[N];  
    data = buff;  
    rader_changer(data);
    for(L=1; L<=M; L++) {  
        B = 1<<(L-1);//B=2^(L-1)  
        for(J=0; J<=B-1; J++) {  
            P = (1<<(M-L))*J;//P=2^(M-L) *J   
            step = 1<<L;//2^L  
            for(K=J; K<=N-1; K=K+step) {  
                W.real =  cos(2*PI*P/N);  
                W.imag = -sin(2*PI*P/N);  
                  
                Temp_XX = complex_xx(data[K+B],W);  
                data[K+B].real = data[K].real - Temp_XX.real;  
                data[K+B].imag = data[K].imag - Temp_XX.imag;  
                  
                data[K].real = data[K].real + Temp_XX.real;  
                data[K].imag = data[K].imag + Temp_XX.imag;  
            }  
        }  
    }  
}  


void complex_modulo(complex_a data[], ElemType out[])
{
    int i;
    for (i = 0; i < N ; i++) {
        out[i] = sqrt(data[i].real*data[i].real+data[i].imag*data[i].imag);
    }
}


int main(int argc ,char * argv[]) 
{
    complex_a buff[N];
    ElemType out[N];
    int i;
    ElemType temp;
    printf("start\n");

    printf("sin:");
    for (i = 0 ;i < N ;i++) {
	temp = sin(16*PI*i/N);
	if (temp > 0)
            buff[i].real = temp;
	else
	    buff[i].real = 0;
        buff[i].imag = 0;
        printf("%04lf ",buff[i].real);
    }
    printf("\nFFT:");
    FFT(buff);
    complex_modulo(buff, out);
    for (i = 0 ;i < N ;i++) {
        printf("%04lf ",out[i]);
    }
    printf("\n");

    return 0;
}


