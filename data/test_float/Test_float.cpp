// constructing priority queues
#include <iostream>       // std::cout
#include <math.h>

union b64{
	double e;
	uint64_t u64;
};

union b32{
	float f;
	uint32_t i32;
};

void bprint(int p){
        int i=0;
        int bit1 = 1;
        for (i=sizeof (p) * 8-1;i>=0; i--){
                unsigned int x = (((bit1<<i)&p) !=0);
                printf("%d", x);
        }

        
}

void b64print(uint64_t p){
        int i=0;
        int bit1 = 1;
        for (i=sizeof (p) * 8-1;i>=0; i--){
                unsigned int x = (((bit1<<i)&p) !=0);
                printf("%d", x);
        }

}

//double 不要直接和整形做运算，会有问题
uint32_t printExp(uint32_t p){
        uint32_t bit1 = 1;
        uint32_t k = (p>>23) & 0xFF;
		uint32_t Bias = (1<<7) - 1;//pow(2, 7) - 1;
		uint32_t exp = k - Bias;
        printf(" k = %d exp = %d Bias = %d", k, exp, Bias);
		//printf(" %d", (int)(pow(2,7) - 1));
		return exp;
}

double printFrac(uint32_t p){
        int i=0;
        uint32_t bit1 = 1;
        uint32_t k = p & 0x007FFFFF;
		b64 v;
		for (i=22;i>=0; i--){
                double x = (((bit1<<i)&p) * pow(2, -i));
                //printf(" %e ", x);
				v.e += x;
        }
        printf(" frac = %e b64=", v.e);
		b64print(v.u64);
		//printf(" %d", (int)(pow(2,7) - 1));
		
		return v.e;
}

int main ()
{
	b32 i;
	//float format
	for (i.i32 = 0x40000000 ; i.i32 < 0x400000FF ; i.i32++){
		printf("i = %d f = %f b= ", i.i32 , i.f);
		bprint(i.i32);
		printExp(i.i32);
		printFrac(i.i32);
		printf("\n");
	}
	
	//验证float的加法
	{
		b32 j,z,w,w1;
		j.f = 1.000001f;
		z.f = 1.000001f;
		w.f = j.f+z.f;
		w1.i32 = j.i32+z.i32;
		printf("sum f= %f, w1 = %f\n" , w.f, w1.f);
	}
	
	//From double to float
	{
		b64 e;
		b32 f;
		e.u64 = 0x000000000111ffffU;
		f.f = e.e;
		printf("f= %f f= %08X, w1 = %e, w1 = %llX\n" , f.f, f.i32, e.e, e.u64);
		//f= -0.000000 f= 80000000, w1 = -3.237859e-319, w1 = 800000000000FFFF
	}
	
	//From double to float
	{
		b64 e;
		b32 f;
		f.i32 = 0x7F7FFFFF;
		e.e = f.f;
		printf("f= %f f= %08X, b=" , f.f, f.i32);
		bprint(f.i32);
		printf(" w1 = %e, w1 = %llX\n", e.e, e.u64 );
		
		e.e = 3.402824e+38d;
		f.f = e.e;
		printf("f= %f f= %08X, b=" , f.f, f.i32);
		bprint(f.i32);
		printf(" w1 = %e, w1 = %llX\n", e.e, e.u64 );
		
		f.i32 = 0xFF7FFFFF;
		e.e = f.f;
		printf("f= %f f= %08X, b=" , f.f, f.i32);
		bprint(f.i32);
		printf(" w1 = %e, w1 = %llX\n", e.e, e.u64 );
		//f= -0.000000 f= 80000000, w1 = -3.237859e-319, w1 = 800000000000FFFF
		
		e.e = -3.402824e+38d;
		f.f = e.e;
		printf("f= %f f= %08X, b=" , f.f, f.i32);
		bprint(f.i32);
		printf(" w1 = %e, w1 = %llX\n", e.e, e.u64 );
		
		f.i32 = 0x80000001;
		e.e = f.f;
		printf("f= %f f= %08X, b=" , f.f, f.i32);
		bprint(f.i32);
		printf(" w1 = %e, w1 = %llX\n", e.e, e.u64 );
		
		f.i32 = 0x00000001;
		e.e = f.f;
		printf("f= %f f= %08X, b=" , f.f, f.i32);
		bprint(f.i32);
		printf(" w1 = %e, w1 = %llX\n", e.e, e.u64 );
	}
	return 0;
}