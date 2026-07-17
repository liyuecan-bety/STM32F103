/*寄存器封装成固件库*/
//寄存器点亮LED灯
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

//宏定义LED，可以切换LED颜色
#define LEDG_GPIO_PORT							GPIOB													//绿色LED端口
#define LEDG_GPIO_CLK_ENABLE				(RCC->APB2ENR	 |= (1 << 3));	//绿色LED时钟使能
#define LEDG_GPIO_Pin								GPIO_Pin_0										//绿色LED引脚，修改该PIN则可以切换LED颜色

//软件延时函数
void Delay(unit_32 count)
{
	for(;count !=0 ;count--);
}

int main(void)
{
#if 0
	/*直接操作内存*/
	//打开GPIO端口的时钟
	*(unsigned int *)0x40021018 |= (1 << 3);
	//配置IO口为输出
	*(unsigned int *)0x40010C00 |= (1 << (4*0));
	//控制ODR寄存器
	*(unsigned int *)0x40010C0C &= ~(1 << 0);
#elif 0
	/*实现寄存器映射找到绝对地址*/
	//打开GPIO端口的时钟
	RCC_APB2ENR	 |= (1 << 3);
	//配置IO口为输出
	GPIOB_CRL		 &= ~(0x0F << (4*0));
	GPIOB_CRL		 |= (1 << (4*0));
	//控制ODR寄存器
	GPIOB_ODR &= ~(1 << 0);
	GPIOB_ODR |= (1 << 0);
	
#elif 0
	/*定义寄存器结构体，寄存器结构体定义，将每个外设基地址强制类型转换，转换成相应外设的结构体指针*/
	//打开GPIO端口的时钟
	RCC->APB2ENR	 |= (1 << 3);
	//配置IO口为输出
	GPIOB->CRL		 &= ~(0x0F << (4*0));//使得初始的CRL为0
	GPIOB->CRL		 |= (1 << (4*0));
	//控制ODR寄存器
	
	GPIOB->ODR		 &= ~(1 << 0);
	//GPIOB->ODR     |=  (1 << 0);//复位
	
#elif 0
	/*编写ODR的置为复位函数增加可读性*/
	//打开GPIO端口的时钟
	RCC->APB2ENR	 |= (1 << 3);
	//配置IO口为输出
	GPIOB->CRL		 &= ~(0x0F << (4*0));//使得初始的CRL为0
	GPIOB->CRL		 |= (1 << (4*0));
	//控制ODR寄存器
	GPIO_SetBits(GPIOB,GPIO_Pin_0);//置位函数，置位ODR第0位
	//GPIO_ResetBits(GPIOB,GPIO_Pin_0);//复位函数，复位ODR第0位
	
#elif 1
	/*定义外设初始化结构体，枚举*/
	GPIO_InitTypeDef GPIO_InitStructure;
	//打开GPIO端口的时钟
	LEDG_GPIO_CLK_ENABLE;
	//配置IO口为输出
	GPIO_InitStructure.GPIO_Pin = LEDG_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//控制ODR寄存器，绿色LED闪烁
	while(1)
	{
		GPIO_SetBits(LEDG_GPIO_PORT,LEDG_GPIO_Pin);//置位函数，置位ODR第0位
		Delay(0xFFFF);
		GPIO_ResetBits(LEDG_GPIO_PORT,LEDG_GPIO_Pin);//复位函数，复位ODR第0位
		Delay(0xFFFF);
	}
	//GPIO_SetBits(LEDG_GPIO_PORT,LEDG_GPIO_Pin);//置位函数，置位ODR第0位
	//GPIO_ResetBits(LEDG_GPIO_PORT,LEDG_GPIO_Pin);//复位函数，复位ODR第0位
	#endif
}

void SystemInit(void)
{
	//函数体为空为了骗过编译器不报错
}

