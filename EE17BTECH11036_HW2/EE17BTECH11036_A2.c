/**
  *  Sai Manasa Pappu
  *  EE17BTECH11036
  *  15TH SEPT 2K19
**/

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "common_functions.h"
#include "common_functions.c"

typedef long double lgdb ;

int main()
{
    int m,n,factor = 2,option;
    lgdb *x,*h ;
    
    printf("Enter size of input x: ");
    scanf("%d",&n);
    
    x = (lgdb *)malloc(n*sizeof(lgdb));
    
    printf("Array values: ");
    for(int i=0;i<n;i++)
    scanf("%Lf",&x[i]);
 
    printf("Enter size of LPF: ");
    scanf("%d",&m);
    
    h  = (lgdb *)malloc(m*sizeof(lgdb));
    
    printf("Array values: ");
    for(int i=0;i<m;i++)
    scanf("%Lf",&h[i]);
    
    printf(" Select option 1) decimation, 2)Interpolation\n");
    scanf("%d",&option);
    
    if(option == 1){
		printf("\n=========================================================================\n\n");
		printf(" DECIMATION OUTPUT:\n\n");
		printarray(decimation(n,x,m,h,factor),(n-1)/factor + 1);
		printf("\n DECIMATION USING MODIFIED HBF EQUATIONS\n\n");
		printarray(modified_hbf_decimation(n,x,m,h,factor),(n-1)/factor + 1);
		printf("\n DECIMATION LEAVING ALTERNATE AND EDGE VALUES\n\n");
		printarray(decim_with_all_props(n,x,m,h,factor),(n-1)/factor + 1);
    }
    
    else if(option == 2){
		printf("\n=========================================================================\n\n");
		printf("\n INTERPOLATION OUTPUT:\n\n");
		printarray(interpolation(n,x,m,h,factor),n*factor);
		printf("\n INTERPOLATION USING MODIFIED HBF EQUATIONS\n\n");
		printarray(modified_hbf_interpolation(n,x,m,h,factor),factor*n);
    }
    
    else{
        printf("\nEnter 1 or 2\n");
    }
    
    printf("\n=========================================================================\n\n");


    return 0;
}
