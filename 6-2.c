#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

float getdiffernce(struct timeval after, struct timeval before){
	float diff = (after.tv_sec - before.tv_sec) * 1000000.0 + (after.tv_usec - before.tv_usec);
				
	return diff;
}

void inner(float *u, float *v, int length, float *dest){
	int i;
	float sum = 0.0f;
	for(i = 0; i < length; ++i){
		sum += u[i] * v[i];
	}
	*dest = sum;
}

/*Make a 4x4 unrolling function*/

void inner2(float *u, float *v, int length, float *dest){
	int i;
	float x0 = 0.0f;
	float x1 = 0.0f;
	float x2 = 0.0f;
	float x3 = 0.0f;
	for(i = 0; i < length; i+= 4){
		x0 += u[i] * v[i];
		x1 += u[i + 1] * v[i + 1];
		x2 += u[i + 2] * v[i + 2];
		x3 += u[i + 3] * v[i + 3];
	}
	for (; i < length; ++i)
	{
		x0 += u[i] * v[i];
	}
	*dest = x0 + x1 + x2 + x3;
}

int main(int argc, char const *argv[])
{
	size_t length = 10000;
	float u[length];
	for (int i = 0; i < length; ++i)
	{
		u[i] = rand() % 473;
	}
	float v[length];
	for (int i = 0; i < length; ++i)
	{
		v[i] = rand() % 473;
	}
	float dest;
	int count = 10000;

	struct timeval before;
	struct timeval after;

	gettimeofday(&before, NULL);
	for (int i = 0; i < count; ++i)
	{
		inner(u, v, length, &dest);
	}
	gettimeofday(&after, NULL);
	printf("%f\n", getdiffernce(after, before));

	gettimeofday(&before, NULL);
	for (int i = 0; i < count; ++i)
	{
		inner2(u, v, length, &dest);
	}
	gettimeofday(&after, NULL);
	printf("%f\n", getdiffernce(after, before));
	return 0;
}