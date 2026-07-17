
//寄存器点亮LED灯
#include "stm32f10x.h"
 
int main(void)
{
	#if 0
	//打开GPIO端口的时钟
	*(unsigned int *)0x40021018 |= (1 << 3);
	//配置IO口为输出
	*(unsigned int *)0x40010C00 |= (1 << (4*0));
	//控制ODR寄存器
	*(unsigned int *)0x40010C0C &= ~(1 << 0);
	#else
	
	//打开GPIO端口的时钟
	RCC_APB2ENR	 |= (1 << 3);
	//配置IO口为输出
	GPIOB_CRL		 &= ~(0x0F << (4*0));
	GPIOB_CRL		 |= (1 << (4*0));
	//控制ODR寄存器
	GPIOB_ODR &= ~(1 << 0);
	
	#endif
}

void SystemInit(void)
{
	//函数体为空为了骗过编译器不报错
}
