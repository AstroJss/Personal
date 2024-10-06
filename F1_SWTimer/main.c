#include <stm32f10x.h>
#include "gpio.h"
#include "Timer.h"
#include "Button.h"
#include "DisplayDrv.h"
#include "OPM.h"


int main(void) {
	
	// A lot of initializations
	SystemInit();
	GPIO_Init();

	Timer_Config();
	
	EXTI_Config();
  Timer_Init();

	
	while(1) {
	//Display_Digits(seconds);
	}
}

