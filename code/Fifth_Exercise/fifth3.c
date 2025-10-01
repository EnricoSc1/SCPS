#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Kahan summation works under the assumption that, at every step of the summation, the current sum will be larger than the term added

double KahanSum(long double x[]){
	long double sum = 0.0;
	long double c = 0.0;
	long double ord_x[4];

	for (int i = 0; i < 4; i++){
		long double y = x[i] - c;
		long double t = sum + y;
		c = (t - sum) - y;
		sum = t;
		//printf("%10.f, %10.f, %10.f\n",sum,c,y);
	}

	return sum;
}

int main(){

	long double vec[4] = {1.0, 1.0e+16, - (1.0e+16), -0.5};
	long double sum = 0;

	sum = KahanSum(vec);

	printf("%.10Lf\n",sum);

}
