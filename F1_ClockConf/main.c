#include <stm32f10x.h>
#include <Display_Driver.h>

#include <Delay.h>

void Render_DisplayDigit(int digit, uint8_t pattern) {
	Display_Driver_ShowPattern(0x00);
	Display_driver_Sel_Digit(digit); 
	Display_Driver_ShowPattern(pattern); 
}

// Clock related

int hour = 11; // 1 ~ 12
int minute = 50; // 0 ~ 59
int second =  56; // 0 ~ 59

void increment_clock(void) { // This is called every second
	second++; 
	if(second < 60) return; 
	second = 0; 
	
	minute++; 
	if(minute < 60) return; 
	minute = 0 ;
	
	hour++; 
	if(hour <= 12) return; 
	hour = 1; 
}


// Render related

uint8_t patterns[8]; 

const uint8_t font[10] = {
	0xFC, 0x60, 0xDA, 0xF2, 0x66, 
	0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 
}; 

void generate_number(int number, int startDigit, int removeLeadingZs) {
	if(number > 100 | number < 0) return; 
	if(startDigit >= 7) return; 
	uint8_t digit0 = number / 10; 
	uint8_t digit1 = number % 10; 
	if(removeLeadingZs && digit0 == 0) {
		patterns[startDigit] = 0x00; 
	}
	else {
		patterns[startDigit] = font[digit0];
	}
	patterns[startDigit + 1] = font[digit1];
}

void generate_patterns(void) {
	patterns[2] = 0x02; 
	patterns[5] = 0x02; 
	generate_number(hour, 0, 1); 
	generate_number(minute, 3, 0); 
	generate_number(second, 6, 0); 
}

int main(void) {
	DisplayDrv_Init(); 
	
	while(1) {
		
		generate_patterns(); 
		
		// Scan for 1 second
		for(int j = 0; j < 125; j++) { // 128 scans make 1 second
			for(int i = 0; i < 8; i++) { // One scan 8 ms
				Render_DisplayDigit(i, patterns[i]); 
				Sys_DelayMs(1); 
			}
		}
		
		// Increment clock
		increment_clock(); 
		
	}
}

