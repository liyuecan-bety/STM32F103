#include "main.h"
#define KEY_ON 1
#define KEY_OFF 0
void KEY_Init(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
