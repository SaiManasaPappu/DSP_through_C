#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common_functions.h"

typedef long double lgdb;

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

lgdb *conv(int n,lgdb *a1,int m,lgdb *a2){
    lgdb *res = (lgdb *)malloc(sizeof(lgdb)*(m+n-1)) ;
    int a1_index,start,end;
    for(int i=0;i<m+n-1;i++){
        res[i]=0;
        start = 0 > (i-m+1) ? 0 : (i-m+1) ;
        end = n < (i+1) ? n : (i+1) ;
        for(a1_index = start;a1_index < end ;a1_index++)
            res[i] += ((a1[a1_index])*(a2[i-a1_index])) ;
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

lgdb* reduced(int n, int h, lgdb* v){
	lgdb *v_red = (lgdb *)malloc(n*sizeof(lgdb));
	int rem = (h-1)/2 ;
	for(int i=0;i<n;i++)
	v_red[i] = v[i+rem];
	return v_red ;
}

lgdb* scale(int n,lgdb* a,int factor){
	lgdb *a_scaled = (lgdb *)malloc(n*sizeof(lgdb));
	for(int i=0;i<n;i++)
	a_scaled[i] = factor*a[i];
	return a_scaled;
}

lgdb *decimation(int n,lgdb *x,int m,lgdb *h,int factor){
	lgdb *v,*v_reduced,*y;
	v = conv(n,x,m,h);
	v_reduced = reduced(n,m,v);
	y = downsample(n,v_reduced,factor);
	return y;
}

lgdb *interpolation(int n,lgdb *y,int m, lgdb* h,int factor){
	lgdb *upsampled,*z,*z_reduced;
	upsampled = upsample(n,y,factor);
	z = conv(factor*n,upsampled,m,h);
	z_reduced = reduced(factor*n,m,z);
	return z_reduced;
}

lgdb *modified_hbf_decimation(int n,lgdb *x,int m,lgdb *h,int factor){
	lgdb *v,*v_reduced,*y;
	
	// Convolution using modified HBF equations
	v = (lgdb *)malloc(sizeof(lgdb)*(m+n-1)) ;
    int h_index,x_index,x_other;
    for(int i=0;i<m+n-1;i++){
        v[i]=0;
        
        // Increment h_index by 2 since alternate elements are 0, in this case mid element is not added
        for(h_index = 0;h_index<m/2;h_index+=2){			
            x_index = i-h_index;
            x_other = i - (m - 1 - h_index) ;
            v[i] += (h[h_index])*(((0<=x_index && x_index<n) ? x[x_index] : 0)+((0<=x_other && x_other<n) ? x[x_other] : 0));
        }
        
        // Add mid element part i.e, h[h_length/2]. Note that hlength is always odd
        h_index = m/2;
        x_index = i-h_index;
        if(0<=x_index && x_index<n)
            v[i] += ((h[h_index])*(x[x_index]));
    }
	v_reduced = reduced(n,m,v);
	y = downsample(n,v_reduced,factor);
	return y;
}
lgdb *decim_with_all_props(int n,lgdb *x,int m,lgdb *h,int factor){
    /* In this function we 
     ** skip calculating first (h-1)/2 and last (h-1)/2 samples in convolution itself*/
	lgdb *v;
	
	// Convolution using modified HBF equations
	v = (lgdb *)malloc(sizeof(lgdb)*((n-1)/factor + 1 )) ;
    int h_index,x_index,x_other,j=0;
    for(int i=(m-1)/2;i<n+(m-1)/2;i+=2){
        v[j]=0;
        
        // Increment h_index by 2 since alternate elements are 0, in this case mid element is not added
        for(h_index = 0;h_index<m/2;h_index+=2){			
            x_index = i-h_index;
            x_other = i - (m - 1 - h_index) ;
            v[j] += (h[h_index])*(((0<=x_index && x_index<n) ? x[x_index] : 0)+((0<=x_other && x_other<n) ? x[x_other] : 0));
        }
        
        // Add mid element part i.e, h[h_length/2]. Note that hlength is always odd
        h_index = m/2;
        x_index = i-h_index;
        if(0<=x_index && x_index<n)
            v[j] += ((h[h_index])*(x[x_index]));
        j++;
    }
	return v;
}

lgdb *modified_hbf_interpolation(int n,lgdb *y,int m,lgdb *h,int factor){
	lgdb *upsampled,*z,*z_reduced;
	upsampled = upsample(n,y,factor);
	int ysize = n*factor,h_index,y_index,y_other;
	
	// Peform Convolution using modified HBF equations		
	z = (lgdb *)malloc(sizeof(lgdb)*(m+ysize-1)) ;
    for(int i=0;i<m+ysize-1;i++){
        z[i]=0;
        
        // Increment h_index by 2 since alternate elements are 0, in this case mid element is not added
        for(h_index = 0;h_index<m/2;h_index+=2){
			// Note that h[i] = h[(h_len - 1) - i]
            y_index = i-h_index;
            y_other = i - (m - 1 - h_index) ;
            z[i] += (h[h_index])*(((0<=y_index && y_index<ysize) ? upsampled[y_index] : 0) + ((0<=y_other && y_other<ysize) ? upsampled[y_other] : 0));
        }
        
        // Add mid element part i.e, h[h_length/2]. Note that hlength is always odd
        h_index = m/2;
        y_index = i-h_index;
        if(0<=y_index && y_index<ysize){
                z[i] += ((h[h_index])*(upsampled[y_index]));
        }   
    }
	z_reduced = reduced(factor*n,m,z);
	return z_reduced;
}
