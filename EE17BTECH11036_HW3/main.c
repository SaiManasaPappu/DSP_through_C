/**
  *  Sai Manasa Pappu
  *  EE17BTECH11036
  *  2ND OCT 2K19
**/

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "common_functions.h"
#include "common_functions.c"

#define pi 3.14159265358979323846

typedef long double lgdb;
typedef long long ll;

int main()
{
    int option;
    lgdb *x ;
    ll fc,fs,fc1,fc2,N,L;
        
    printf(" Select filter: 1)LPF 2)HPF 3)BPF 4)Moving Average Filter\n");
    scanf("%d",&option);
    
    if(option == 1 || option == 2){
        printf("fc : ");
        scanf("%lli",&fc);
        printf("fs : ");
        scanf("%lli",&fs);
        printf("N : ");
        scanf("%lli",&N);
        if(option==1)
        lpf(fc, fs, N);
        else
        hpf(fc, fs, N);
		// lgdb *res = (option==1) ? lpf(fc, fs, N) : hpf(fc, fs, N) ;
        // printf("Impulse Response of %s : \n", (option==1) ? "LPF" : "HPF");
        // printarray(res, N);
    }
    
    else if(option == 3){
        printf("fc1 : ");
        scanf("%lli",&fc1);
        printf("fc2 : ");
        scanf("%lli",&fc2);
        printf("fs : ");
        scanf("%lli",&fs);
        printf("N : ");
        scanf("%lli",&N);
        bpf(fc1, fc2, fs, N);
        // lgdb *res = bpf(fc1, fc2, fs, N);
        // printf("Impulse Response of BPF: \n");
        // printarray(res, N);
    }
    else if(option == 4){
        printf("Enter size of input x: ");
        scanf("%lli",&N);
        x = (lgdb *)malloc(N*sizeof(lgdb));
        printf("Array Values: \n");
        for(ll i=0;i<N;i++)
        scanf("%Lf",&x[i]);
        printf("L: ");
        scanf("%lli",&L);
        lgdb *res = moving_average(N,x,L);
        printf("Output:\n");
		printarray(res,N+L-1);

		}
    
    else{
        printf("\nEnter correct option\n");
    }
    
    printf("\n=========================================================================\n\n");


    return 0;
}