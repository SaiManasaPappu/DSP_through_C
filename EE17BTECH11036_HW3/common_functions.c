/**
  *  Sai Manasa Pappu
  *  EE17BTECH11036
  *  2ND OCT 2K19
**/

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "common_functions.h"
#define pi 3.14159265358979323846

typedef long double lgdb;
typedef long long ll;

void printarray(lgdb *arr,ll n){
    printf("[ ");
    for(ll i=0;i<n;i++)
    printf("%Lf ",arr[i]);
    printf(" ]");
    printf("\n");
}

lgdb *multiply(ll N, lgdb *a, lgdb *b){
    // Perform elementwise multiplication of a and b of same length N
    lgdb *res = (lgdb *)malloc(N*sizeof(lgdb));
    for(ll i=0;i<N;i++)
    res[i] = a[i]*b[i] ;
    return res;
}

lgdb *rectangular_window(ll N){
    lgdb *res = (lgdb *)malloc(N*sizeof(lgdb));
    for(ll i=0;i<N;i++)
    res[i] = 1.0;
    return res;
}

lgdb *hamming_window(ll N){
    lgdb *res = (lgdb *)malloc(N*sizeof(lgdb));
    for(ll i=0;i<N;i++)
    res[i] = 0.54 - 0.46*cos(2.0*pi*i/(N-1.0));
    return res;
}

void lpf(ll fc, ll fs, ll N){
    lgdb wc = (2.0*pi*fc)/fs ;
    lgdb *hd = (lgdb *)malloc(N*sizeof(lgdb));
    ll k = (N-1)/2.0 ;
    ll n=-k;
    for(ll i=0;i<k;i++,n++)
    hd[i] = sin(wc*n)/(pi*n) ;
    hd[k] = wc/pi ;
    n = 1 ;
    for(ll i=k+1;i<N;i++,n++)
    hd[i] = sin(wc*n)/(pi*n) ;
    lgdb *rect_output = multiply(N, hd, rectangular_window(N));
    lgdb *ham_output = multiply(N, hd, hamming_window(N));
    printf("\nUsing Rectangular Window\n");
    printarray(rect_output, N);
    printf("\nUsing Hamming Window\n");
    printarray(ham_output, N);
}

void hpf(ll fc, ll fs, ll N){
    lgdb wc = (2.0*pi*fc)/fs ;
    lgdb *hd = (lgdb *)malloc(N*sizeof(lgdb));
    ll k = (N-1)/2.0 ;
    ll n=-k;
    for(ll i=0;i<k;i++,n++)
    hd[i] = (sin(pi*n)-sin(wc*n))/(pi*n) ;
    hd[k] = 1.0 - wc/pi ;
    n = 1 ;
    for(ll i=k+1;i<N;i++,n++)
    hd[i] = (sin(pi*n)-sin(wc*n))/(pi*n) ;
    lgdb *rect_output = multiply(N, hd, rectangular_window(N));
    lgdb *ham_output = multiply(N, hd, hamming_window(N));
    printf("\nUsing Rectangular Window\n");
    printarray(rect_output, N);
    printf("\nUsing Hamming Window\n");
    printarray(ham_output, N);

}

void bpf(ll fc1, ll fc2, ll fs, ll N){
    lgdb wc1 = (2.0*pi*fc1)/fs ;
    lgdb wc2 = (2.0*pi*fc2)/fs ;
    lgdb *hd = (lgdb *)malloc(N*sizeof(lgdb));
    ll k = (N-1)/2.0 ;
    ll n=-k;
    for(ll i=0;i<k;i++,n++)
    hd[i] = (sin(wc2*n)-sin(wc1*n))/(pi*n) ;
    hd[k] = wc2/pi- wc1/pi ;
    n = 1 ;
    for(ll i=k+1;i<N;i++,n++)
    hd[i] = (sin(wc2*n)-sin(wc1*n))/(pi*n) ;
    lgdb *rect_output = multiply(N, hd, rectangular_window(N));
    lgdb *ham_output = multiply(N, hd, hamming_window(N));
    printf("\nUsing Rectangular Window\n");
    printarray(rect_output, N);
    printf("\nUsing Hamming Window\n");
    printarray(ham_output, N);

}

lgdb *moving_average(ll N, lgdb *x, ll L){
    lgdb *res = (lgdb *)malloc((N+L-1)*sizeof(lgdb));

    // First L-1 terms
    for(ll i=0;i<L-1;i++){   
        res[i]=0;
        for(ll j=0;j<i+1;j++)
        res[i] += x[j] ;
        res[i] /= (1.0*L);
    }

    //Mid N-L+1 terms
    for(ll i=L-1;i<N;i++){
        res[i] = 0;
        for(ll j=0;j<L;j++)
        res[i] += x[i-j];
        res[i] /= (1.0*L);
    }

    // Last L-1 terms
    for(ll i= N;i<N+L-1;i++){
        res[i]=0;
        for(ll j=i-L+1;j<N;j++)
        res[i] += x[j] ;
        res[i] /= (1.0*L) ;
    }

    return res;
}
