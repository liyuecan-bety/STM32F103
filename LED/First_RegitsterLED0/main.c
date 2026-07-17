#if 0
//51单片机例子
#include<reg52.h>
sbit LED = P0^0;

int main()
{
	P0 = 0xFE;//点亮第0个灯
	LED = 0;
	
}

#endif

//寄存器点亮LED灯
#include "stm32f10x.h"
//点亮红灯
void Blink_RLED()
{
	//配置 GPIO5_CLR IO口为输出
	*(unsigned int *)0x40010C00 |= ( (1) << (4*5));
	//配置ODR寄存器
	*(unsigned int *)0x40010C0C &= ~( 1 << 5 );
	
}
//点亮绿灯
void Blink_GLED()
{
	//配置 GPIO0_CLR IO口为输出
	*(unsigned int *)0x40010C00 |= ( (1) << (4*0) );
	
	//配置ODR寄存器
	*(unsigned int *)0x40010C0C &= ~( 1 << 0 );
}
//点亮蓝灯
void Blink_BLED()
{
	//配置 GPIO5_CLR IO口为输出
	*(unsigned int *)0x40010C00 |= ( (1) << (4*1));
	//配置ODR寄存器
	*(unsigned int *)0x40010C0C &= ~( 1 << 1 );
}

int main(void)
{
	//打开 GPIOB 端口时钟
	*(unsigned int *)0x40021018 |= ( (1) << 3 );
	while(1)
	{
		Blink_BLED();
	}
}

//置位  |=      
//清零  &=~  



//点亮其他两个LED灯
//写一个简单的延时函数，让LED灯闪烁

void SystemInit(void)
{
	//函数体为空，目的是为了骗过编译器不报错
}
