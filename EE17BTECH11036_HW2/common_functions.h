typedef long double lgdb;

void printarray(lgdb *arr,int n);
lgdb *correlation(int m,int n,lgdb *a1,lgdb *a2);
lgdb *upsample(int n,lgdb *arr,int factor);
lgdb *downsample(int n,lgdb *arr,int factor);
lgdb *conv(int m,lgdb *a1,int n,lgdb *a2);
lgdb* reduced(int n, int h, lgdb* v);
lgdb* scale(int n,lgdb* a,int factor);
lgdb *decimation(int n,lgdb *x,int m,lgdb *h,int factor);
lgdb *interpolation(int n,lgdb *y,int m, lgdb* h,int factor);
lgdb *modified_hbf_decimation(int n,lgdb *x,int m,lgdb *h,int factor);
lgdb *decim_with_all_props(int n,lgdb *x,int m,lgdb *h,int factor);
lgdb *modified_hbf_interpolation(int n,lgdb *y,int m,lgdb *h,int factor);
