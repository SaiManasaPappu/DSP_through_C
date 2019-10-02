/**
  *  Sai Manasa Pappu
  *  EE17BTECH11036
  *  2ND OCT 2K19
**/

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#define pi 3.14159265358979323846

typedef long double lgdb;
typedef long long ll;

void printarray(lgdb *arr,int n){
    printf("[ ");
    for(int i=0;i<n;i++)
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
    printf("\nrect window\n");
    printarray(res,N);
    return res;
}

lgdb *hamming_window(ll N){
    lgdb *res = (lgdb *)malloc(N*sizeof(lgdb));
    for(ll i=0;i<N;i++)
    res[i] = 0.54 - 0.46*cos(2*pi*i/(N-1));
    printf("\nHamming window\n");
    printarray(res,N);
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
    for(int i=k+1;i<N;i++,n++)
    hd[i] = sin(wc*n)/(pi*n) ;
    lgdb *rect_output = multiply(N, hd, rectangular_window(N));
    lgdb *ham_output = multiply(N, hd, hamming_window(N));
    printarray(rect_output, N);
    printarray(ham_output, N);
}

void hpf(ll fc, ll fs, ll N){

}

void bpf(ll fc1, ll fc2, ll fs, ll N){

}

// lgdb *moving_average(ll N, lgdb *x){

// }

int main()
{
    int option;
    lgdb *x ;
    ll fc,fs,fc1,fc2,N;
        
    printf(" Select filter: 1)LPF 2)HPF 3)BPF 4)Moving Average Filter\n");
    scanf("%d",&option);
    
    if(option == 1 || option == 2){
        printf("fc : ");
        scanf("%lli",&fc);
        printf("fs : ");
        scanf("%lli",&fs);
        printf("N : ");
        scanf("%lli",&N);
        lpf(fc, fs, N);
		// lgdb *res = (option==1) ? lpf(fc, fs, N) : hpf(fc, fs, N) ;
        // printf("Impulse Response of %s : \n", (option==1) ? "LPF" : "HPF");
        // printarray(res, N);
    }
    
    // else if(option == 3){
    //     printf("fc1 : ");
    //     scanf("%lli",&fc1);
    //     printf("fc2 : ");
    //     scanf("%lli",&fc2);
    //     printf("fs : ");
    //     scanf("%lli",&fs);
    //     printf("N : ");
    //     scanf("%lli",&N);
    //     lgdb *res = bpf(fc1, fc2, fs, N);
    //     printf("Impulse Response of BPF: \n");
    //     printarray(res, N);
    // }
    // else if(option == 4){
    //     printf("Enter size of input x: ");
    //     scanf("%lli",&N);
    //     x = (lgdb *)malloc(N*sizeof(lgdb));
    //     printf("Array Values: \n");
    //     for(ll i=0;i<N;i++)
    //     scanf("%Lf",&x[i]);
    //     lgdb *res = moving_average(N,x);
	// 	printarray(x,n);

	// 	}
    
    else{
        printf("\nEnter correct option\n");
    }
    
    printf("\n=========================================================================\n\n");


    return 0;
}
