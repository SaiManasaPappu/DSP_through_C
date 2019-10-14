/**
  *  Sai Manasa Pappu
  *  EE17BTECH11036
  *  2ND OCT 2K19
**/

#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef long double lgdb;
typedef long long ll;

void printarray(lgdb *arr,ll n);
lgdb *multiply(ll N, lgdb *a, lgdb *b);
lgdb *rectangular_window(ll N);
lgdb *hamming_window(ll N);
void lpf(ll fc, ll fs, ll N);
void hpf(ll fc, ll fs, ll N);
void bpf(ll fc1, ll fc2, ll fs, ll N);
lgdb *moving_average(ll N, lgdb *x, ll L);
