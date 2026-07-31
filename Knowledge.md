一.如何使用软件控制硬件
第一步：定义外设的“基地址”
在标准库的头文件（如 stm32f10x.h）中，第一步就是定义所有外设的基地址，这是所有操作的起点。
// 1. 整个芯片外设的基地址（总线地址）
#define PERIPH_BASE           ((uint32_t)0x40000000)
// 2. APB1 总线的基地址（低速外设，如定时器、I2C）
#define APB1PERIPH_BASE       PERIPH_BASE
// 3. APB2 总线的基地址（高速外设，如GPIO、USART1）
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
// 4. 每个具体外设的基地址 = 总线地址 + 偏移量
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
// ... 其他外设
这些地址，和你上一问中看到的 0x40010800（GPIOA）是完全一致的。
第二步：用“结构体”定义寄存器布局
接下来，标准库会为每个外设定义一个结构体类型。结构体成员按寄存器地址由低到高的顺序排列，成员的字节大小要和硬件寄存器完全一致（通常是32位，即 uint32_t）。
以 GPIO_TypeDef 为例：
typedef struct
{
  __IO uint32_t CRL;    // 0x00 偏移: 端口配置低寄存器
  __IO uint32_t CRH;    // 0x04 偏移: 端口配置高寄存器
  __IO uint32_t IDR;    // 0x08 偏移: 输入数据寄存器
  __IO uint32_t ODR;    // 0x0C 偏移: 输出数据寄存器
  __IO uint32_t BSRR;   // 0x10 偏移: 位设置/清除寄存器
  __IO uint32_t BRR;    // 0x14 偏移: 位清除寄存器
  __IO uint32_t LCKR;   // 0x18 偏移: 端口配置锁定寄存器
} GPIO_TypeDef;
__IO 是一个宏，实际上就是 volatile，告诉编译器每次访问都必须从真实地址读取，不要优化。
结构体内存布局完全按照寄存器地址排列，所以当你拿到一个基地址并把它强转为 GPIO_TypeDef* 指针时，CRL 成员的地址就是基地址 + 0，CRH 就是基地址 + 0x04，以此类推。
第三步：将“基地址”转换为“结构体指针”
最关键的步骤来了。标准库会将之前定义的基地址，强制转换为指向对应结构体的指针。
// GPIOA_BASE 是一个数值（如 0x40010800）
// 通过 (GPIO_TypeDef *) 强制类型转换，告诉编译器：
// “这个地址里存放的数据，要按照 GPIO_TypeDef 的结构来解读”
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
现在，GPIOA 本身就是一个指向结构体的指针常量，它的值就是 0x40010800。
📝 第四步：软件中通过“->”操作符修改寄存器
当你在标准库的示例代码中看到这样的写法：
GPIOA->CRL = 0x44444444;   // 将GPIOA的0-7号引脚都设为浮空输入
实际发生的操作是：
编译器解析：GPIOA 被展开为 ((GPIO_TypeDef *)0x40010800)。
成员访问：->CRL 表示访问这个结构体的第一个成员。根据结构体定义，它的偏移量是 0x00。
生成最终地址：编译器计算最终地址 = 0x40010800 + 0x00 = 0x40010800。
生成机器码：编译器生成一条向地址 0x40010800 写入数据 0x44444444 的汇编指令（通常是 STR 指令）。
这条指令被执行时，芯片的硬件逻辑会将这个写操作路由到GPIOA的配置寄存器上，从而物理上改变了引脚的电气特性。