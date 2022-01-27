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

template<typename T>
void Tbprint(T p){
        int i=0;
        int bit1 = 1;
        for (i=sizeof (p) * 8-1;i>=0; i--){
                unsigned int x = (((bit1<<i)&p) !=0);
                printf("%d", x);
        }

        
}

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

void overflow(){
	unsigned char i= 0xFF;
	unsigned char j= 0x01;
	i = i + j;
	printf("i = %d b=", i);
	Tbprint(i);
	printf("\n");
	
	i = 0xFF;
	j= 0xFF;
	i = 0xFF*0xFF;
	unsigned short k = 0xFF*0xFF;
	printf("i = %d b=", i);
	Tbprint(i);
	printf("\ni16=%04X b=",k);
	Tbprint(k);
	printf("\n");
}

void multiconst(){
	int i = 0x80000001;
	int j = i << 1;
	int z = i * 2;
	printf("i=%d b=",i);
	Tbprint(i);
	printf("\nj=%d b=",j);
	Tbprint(j);
	printf("\nz=%d b=",z);
	Tbprint(z);
	printf("\n");
}
int main ()
{
	int x = 55;
	int j = ~x + 1;
	
	printf("x=%d b=",x);
	bprint(x);
	printf("\n");
	
	printf("j=%d b=",j);
	bprint(j);
	printf("\n");
	
	overflow();
	multiconst();
	return 0;
}