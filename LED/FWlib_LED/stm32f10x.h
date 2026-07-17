//用来存放STM32寄存器的映射
#ifndef _STM32F10X_H
#define _STM32F10X_H


/* 外设perirhral */

#define PERIPH_BASE							((unsigned int)0x40000000)
#define APB1PERIPH_BASE				  PERIPH_BASE
#define APB2PERIPH_BASE					(PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE					(PERIPH_BASE + 0x20000)

#define RCC_BASE								(AHBPERIPH_BASE + 0x1000)
#define GPIOB_BASE							(APB2PERIPH_BASE + 0x0C00) 

/*
//不使用结构体，直接用宏定义定义寄存器
#define RCC_APB2ENR							*(unsigned int*)(RCC_BASE + 0x18)
#define GPIOB_CRL								*(unsigned int*)(GPIOB_BASE + 0x00)
#define GPIOB_CRH								*(unsigned int*)(GPIOB_BASE + 0x04)
#define GPIOB_ODR								*(unsigned int*)(GPIOB_BASE +	0x0C)
#define GPIOB_IDR								*(unsigned int*)(GPIOB_BASE +	0x08)
#define GPIOB_BSRR							*(unsigned int*)(GPIOB_BASE +	0x10)
#define GPIOB_BRR								*(unsigned int*)(GPIOB_BASE +	0x14)
#define GPIOB_LCKR							*(unsigned int*)(GPIOB_BASE +	0x18)
*/


/*寄存器结构体声明*/

//定义32位的数据类型unit_32
typedef unsigned int unit_32;
typedef unsigned short unit_16;


//GPIO外设寄存器结构体
typedef struct
{
	//按照寄存器映射的顺序定义
	unit_32 CRL;
	unit_32 CRH;
	unit_32 IDR;
	unit_32 ODR;
	unit_32 BSRR;
	unit_32 BRR;
	unit_32 LCKR;
}GPIO_TypeDef;

//RCC外设寄存器结构体声明
typedef struct
{
	unit_32 CR;
	unit_32 CFGR;
	unit_32 CIR;
	unit_32 APB2RSTR;
	unit_32 APB1RSTR;
	unit_32 AHBENR;
	unit_32 APB2ENR;
	unit_32 APB1ENR;
	unit_32 BDCR;
	unit_32 CSR;
}RCC_TypeDef;

/*外设寄存器定义*/

//GPIOB寄存器定义
#define GPIOB ((GPIO_TypeDef*)GPIOB_BASE)

//RCC寄存器定义
#define RCC 	((RCC_TypeDef*)RCC_BASE)
#endif /*STM32F10X_h*/

