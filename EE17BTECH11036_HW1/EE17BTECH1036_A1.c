/**
  *  Sai Manasa Pappu
  *  EE17BTECH11036
  *  5TH SEPT 2K19
**/

#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef long double lgdb ;

void printarray(lgdb *arr,int n){
    printf("[ ");
    for(int i=0;i<n;i++)
    printf("%Lf ",arr[i]);
    printf(" ]");
    printf("\n");
}

lgdb *correlation(int m,int n,lgdb *a1,lgdb *a2){
    lgdb *res = (lgdb *)malloc(sizeof(lgdb)*(m+n-1)) ;
    int a1_index,a2_index;
    for(int i=0;i<m+n-1;i++){
        res[i]=0;
        for(a1_index = 0;a1_index<m;a1_index++){
            a2_index = i+a1_index;
            if(0<=a2_index && a2_index<n){
                res[i] += ((a1[a1_index])*(a2[a2_index]));
            }
        }
    }
    return res;
}

lgdb *upsample(int n,lgdb *arr,int factor){
    lgdb *res = (lgdb *)malloc(sizeof(lgdb)*(n*factor)) ;
    int temp,i=0;
    while(i<n*factor){
        res[i] = arr[i/factor];
        i++;
        temp = factor-1 ;
        while(temp--){
            res[i] = 0;
            i++;
        }
    }
    return res;
}

lgdb *downsample(int n,lgdb *arr,int factor){
    int res_size = (n-1)/factor + 1 ;
    lgdb *res = (lgdb *)malloc(sizeof(lgdb)*(res_size)) ;
    int res_index = 0;
    for(int i=0;i<n;i+=factor){
        res[res_index++]=arr[i];
    }
    return res;
}

lgdb *conv(int m,int n,lgdb *a1,lgdb *a2){
    lgdb *res = (lgdb *)malloc(sizeof(lgdb)*(m+n-1)) ;
    int a1_index,a2_index;
    for(int i=0;i<m+n-1;i++){
        res[i]=0;
        for(a1_index = 0;a1_index<m;a1_index++){
            a2_index = i-a1_index;
            if(0<=a2_index && a2_index<n){
                res[i] += ((a1[a1_index])*(a2[a2_index]));
            }
        }
    }
    return res;
}

/*
Sample I/O

Enter size of input1: 3                                                                           
Array values: 1 2 3                                                                               
Enter size of input2: 3                                                                           
Array values: -1 -2 -3                                                                            
                                                                                                  
                                                                                                 
Convolution:                                                                                      
-1.000000 -4.000000 -10.000000 -12.000000 -9.000000                                               
                                                                                                  
Upsampled:                                                                                        
1.000000 0.000000 0.000000 2.000000 0.000000 0.000000 3.000000                                    
                                                                                                  
Downsampled:                                                                                      
1.000000                                                                                          
                                                                                                  
Correlation: -1.000000                                                                            
                      
*/

int main()
{
    int m,n,factor=3,option;
    lgdb *a1,*a2;
    
    // COMMENTOUT FUNCTIONS IF WISH TO TEST SPECIFICALLY
    
    printf("Enter size of input1: ");
    scanf("%d",&m);
    a1 = (lgdb *)malloc(m*sizeof(lgdb));
    printf("Array values: ");
    for(int i=0;i<m;i++)
    scanf("%Lf",&a1[i]);
    
    printf(" Enter 1 for convolution (or) correlation, 2 for upsampling (or) downsampling\n");
    scanf("%d",&option);
    
    if(option == 1){
        
    printf("Enter size of input2: ");
    scanf("%d",&n);
    
    a2 = (lgdb *)malloc(n*sizeof(lgdb));
    
    printf("Array values: ");
    for(int i=0;i<n;i++)
    scanf("%Lf",&a2[i]);
    
    printf("\n\nConvolution:\n");
    printarray(conv(m,n,a1,a2),m+n-1);
    
    printf("\nCorrelation:\n");
    printarray(correlation(m,n,a1,a2),m+n-1);
    
    }
    
    else if(option == 2){
        
    printf("Enter factor\n");
    scanf("%d",&factor);
        
    printf("\nUpsampled:\n");
    printarray(upsample(m,a1,factor),m*factor);
    
    printf("\nDownsampled:\n");
    printarray(downsample(m,a1,factor),(m-1)/factor + 1);
    
    }
    
    else{
        printf("\nEnter 1 or 2\n");
    }

    return 0;
}

