// MAIN.C file
// version 1.1
// takes 8-digit user codes and lights the LEDs if the codes are correct
// TODO:
// replace button poll with interupts
// init timers for delay
// init button press wipe timer?

#include "stm8s.h"

#define DEBOUNCE_WAIT_MS 250

// delay using TIM4
// each delay loop is 1ms
// can specify up to "unsigned long int" ms delays
void delay_ms(unsigned long int val)
{
	unsigned long int i = 0;
	TIM4_Cmd(ENABLE);
	for (i; i < val; i++)
	{
		TIM4_SetCounter(0);
		while(!TIM4_GetFlagStatus(TIM4_FLAG_UPDATE));
		TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	}
	TIM4_Cmd(DISABLE);
}

unsigned char poll_buttons(void)
{
	// poll for button press (active low)
	// return poll value (0-7 for button, 255 for nothing)
	// simple debounce by waiting N ms
	// poll B0 (PD2)
	if(!GPIO_ReadInputPin(GPIOD, GPIO_PIN_2))
	{
		// B0 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 0;
	}
	// poll B1 (PB5)
	else if(!GPIO_ReadInputPin(GPIOB, GPIO_PIN_5))
	{
		// B1 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 1;
	}
	// poll B2 (PB4)
	else if(!GPIO_ReadInputPin(GPIOB, GPIO_PIN_4))
	{
		// B2 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 2;
	}
	// poll B3 (PC3)
	else if(!GPIO_ReadInputPin(GPIOC, GPIO_PIN_3))
	{
		// B3 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 3;
	}
	// poll B4 (PC4)
	else if(!GPIO_ReadInputPin(GPIOC, GPIO_PIN_4))
	{
		// B4 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 4;
	}
	// poll B5 (PC5)
	else if(!GPIO_ReadInputPin(GPIOC, GPIO_PIN_5))
	{
		// B5 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 5;
	}
	// poll B6 (PC6)
	else if(!GPIO_ReadInputPin(GPIOC, GPIO_PIN_6))
	{
		// B6 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 6;
	}
	// poll B7 (PC7)
	else if(!GPIO_ReadInputPin(GPIOC, GPIO_PIN_7))
	{
		// B7 pressed
		// Debounce
		delay_ms(DEBOUNCE_WAIT_MS);
		// return
		return 7;
	}
	else
	{
		// no button pressed
		// return 255
		return 255;
	}
}

// handle button events by shifting the current code array down
// add to end of array
// return 1 or 0 to show if array changed
unsigned char button_handler(unsigned char event, unsigned char* arr)
{
	if (event != 255)
		{
			arr[0] = arr[1];
			arr[1] = arr[2];
			arr[2] = arr[3];
			arr[3] = arr[4];
			arr[4] = arr[5];
			arr[5] = arr[6];
			arr[6] = arr[7];
			arr[7] = event;
			return 1;
		}
		return 0;
}

unsigned char code_check(unsigned char* arr, unsigned char* CFA, unsigned char* ledr)
{
	unsigned char codeA_val[] = {0,1,2,3,4,5,6,7};
	unsigned char codeB_val[] = {7,1,2,6,2,4,3,1};
	unsigned char codeC_val[] = {0,5,2,1,3,5,2,1};
	unsigned char codeD_val[] = {7,3,6,1,4,3,0,4};
	unsigned char codeE_val[] = {6,3,7,3,4,7,5,2};
	unsigned char codeF_val[] = {3,4,2,0,2,6,7,5};
	unsigned char codeG_val[] = {5,0,3,1,7,2,0,5};
	unsigned char codeH_val[] = {1,5,2,1,4,0,7,0};
	unsigned char blank_val[] = {7,7,7,7,7,7,7,7};
	
	// flag A
	if (CFA[0] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeA_val[0] && arr[1] == codeA_val[1] && arr[2] == codeA_val[2] &&
				arr[3] == codeA_val[3] && arr[4] == codeA_val[4] && arr[5] == codeA_val[5] &&
				arr[6] == codeA_val[6] && arr[7] == codeA_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[0] = 1;
			*ledr = *ledr | 128;
			return 1;
		}
	}
	// flag B
	if (CFA[1] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeB_val[0] && arr[1] == codeB_val[1] && arr[2] == codeB_val[2] &&
				arr[3] == codeB_val[3] && arr[4] == codeB_val[4] && arr[5] == codeB_val[5] &&
				arr[6] == codeB_val[6] && arr[7] == codeB_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[1] = 1;
			*ledr = *ledr | 64;
			return 1;
		}
	}
	// flag C
	if (CFA[2] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeC_val[0] && arr[1] == codeC_val[1] && arr[2] == codeC_val[2] &&
				arr[3] == codeC_val[3] && arr[4] == codeC_val[4] && arr[5] == codeC_val[5] &&
				arr[6] == codeC_val[6] && arr[7] == codeC_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[2] = 1;
			*ledr = *ledr | 32;
			return 1;
		}
	}
	// flag D
	if (CFA[3] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeD_val[0] && arr[1] == codeD_val[1] && arr[2] == codeD_val[2] &&
				arr[3] == codeD_val[3] && arr[4] == codeD_val[4] && arr[5] == codeD_val[5] &&
				arr[6] == codeD_val[6] && arr[7] == codeD_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[3] = 1;
			*ledr = *ledr | 16;
			return 1;
		}
	}
	// flag E
	if (CFA[4] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeE_val[0] && arr[1] == codeE_val[1] && arr[2] == codeE_val[2] &&
				arr[3] == codeE_val[3] && arr[4] == codeE_val[4] && arr[5] == codeE_val[5] &&
				arr[6] == codeE_val[6] && arr[7] == codeE_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[4] = 1;
			*ledr = *ledr | 8;
			return 1;
		}
	}
	// flag F
	if (CFA[5] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeF_val[0] && arr[1] == codeF_val[1] && arr[2] == codeF_val[2] &&
				arr[3] == codeF_val[3] && arr[4] == codeF_val[4] && arr[5] == codeF_val[5] &&
				arr[6] == codeF_val[6] && arr[7] == codeF_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[5] = 1;
			*ledr = *ledr | 4;
			return 1;
		}
	}
	// flag G
	if (CFA[6] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeG_val[0] && arr[1] == codeG_val[1] && arr[2] == codeG_val[2] &&
				arr[3] == codeG_val[3] && arr[4] == codeG_val[4] && arr[5] == codeG_val[5] &&
				arr[6] == codeG_val[6] && arr[7] == codeG_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[6] = 1;
			*ledr = *ledr | 2;
			return 1;
		}
	}
	// flag H
	if (CFA[7] == 0)
	{
		// if 0, we need to check the code
		// else we can just ignore
		if(arr[0] == codeH_val[0] && arr[1] == codeH_val[1] && arr[2] == codeH_val[2] &&
				arr[3] == codeH_val[3] && arr[4] == codeH_val[4] && arr[5] == codeH_val[5] &&
				arr[6] == codeH_val[6] && arr[7] == codeH_val[7])
		{
			// code matches
			// set flag so we skip next check
			// set bit in LED register
			// return 1
			CFA[7] = 1;
			*ledr = *ledr | 1;
			return 1;
		}
	}
	// blank
	if (CFA[8] == 0)
	{
		// we need to check the code
		if(arr[0] == blank_val[0] && arr[1] == blank_val[1] && arr[2] == blank_val[2] &&
				arr[3] == blank_val[3] && arr[4] == blank_val[4] && arr[5] == blank_val[5] &&
				arr[6] == blank_val[6] && arr[7] == blank_val[7])
		{
			// code matches
			// set flag
			// return 1
			CFA[8] = 1;
			return 1;
		}
	}

	// no matches, return 0
	return 0;
}

void GPIO_setup(void)
{
	// first, we DeInit the B,C,D bus
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	// init the 8 GPIO buttons:
	// B0 = PD2
	GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT);
	// B1 = PB5
	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
	// B2 = PB4
	GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
	// B3 = PC3
	GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
	// B4 = PC4
	GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);
	// B5 = PC5
	GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_FL_NO_IT);
	// B6 = PC6
	GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);
	// B7 = PC7
	GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT);
	// init the 3 LED control outputs
	// SRCLK = PD4
	GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
	// RCLK = PD5
	GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
	// SER = PD6
	GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);

}

void clock_setup(void)
{
	// deinit the clocks
	CLK_DeInit();
	CLK_HSECmd(DISABLE);
	CLK_LSICmd(DISABLE);
	// enable high speed internal (16MHz) closk
	CLK_HSICmd(ENABLE);
	
	while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);
	
	CLK_ClockSwitchCmd(ENABLE);
	// no prescale and division
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI,
	DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);
	// diable all clocked interfaces except TIM4
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
	// setup timer 4
	// used for ms delay
	TIM4_DeInit();
	TIM4_TimeBaseInit(TIM4_PRESCALER_128, 125);
	TIM4_Cmd(DISABLE);
}

// functions to display the LED register
// how the LED shift register works:
// SER = bit to display
// RCLK = shift register clock
// SRCLK = input clock
// steps: set SER to either 1 or 0 depending on the bit
// pulse SRCLK to load
// pulse RCLK to shift
void load_one(void)
{
	// write 1 to SER
	GPIO_WriteHigh(GPIOD, GPIO_PIN_6);
	delay_ms(1);
	// pulse SRCLK
	GPIO_WriteHigh(GPIOD, GPIO_PIN_4);
	delay_ms(1);
	GPIO_WriteLow(GPIOD, GPIO_PIN_4);
}

void load_zero(void)
{
	// write 0 to SER
	GPIO_WriteLow(GPIOD, GPIO_PIN_6);
	delay_ms(1);
	// pulse SRCLK
	GPIO_WriteHigh(GPIOD, GPIO_PIN_4);
	delay_ms(1);
	GPIO_WriteLow(GPIOD, GPIO_PIN_4);
}

void display_LED_bar(unsigned char LEDreg)
{
	unsigned char i = 0;
	GPIO_WriteLow(GPIOD, GPIO_PIN_4);
	GPIO_WriteLow(GPIOD, GPIO_PIN_5);
	GPIO_WriteLow(GPIOD, GPIO_PIN_6);
	for(i; i < 8; i++)
	{
		// load either 1 or 0
		if(((LEDreg >> i) & 1) == 1)
		{
			// one
			load_one();
		}
		else
		{
			// zero
			load_zero();
		}
		// shift in result
		GPIO_WriteHigh(GPIOD, GPIO_PIN_5);
		delay_ms(1);
		GPIO_WriteLow(GPIOD, GPIO_PIN_5);
	}
}

void main(void)
{
	// flag for button push
	unsigned char button_push_event = 0;
	// flag to signal for code check
	unsigned char code_check_flag = 0;
	// array to store current code shift register
	unsigned char current_code_array[8] = {0,0,0,0,0,0,0,0};
	// code flags (so we don't check every code every time)
	unsigned char code_flag_array[9] = {0,0,0,0,0,0,0,0,0};
	// LED bar register
	unsigned char LED_reg = 0;
	// LED update flag
	unsigned char led_update = 0;
	// iterator
	unsigned char i = 0;
	// blank check
	unsigned char b = 0;
	
	// init uC
	clock_setup();
	GPIO_setup();
	
	// start sequence
	display_LED_bar(128);
	delay_ms(250);
	display_LED_bar(64);
	delay_ms(250);
	display_LED_bar(32);
	delay_ms(250);
	display_LED_bar(16);
	delay_ms(250);
	display_LED_bar(8);
	delay_ms(250);
	display_LED_bar(4);
	delay_ms(250);
	display_LED_bar(2);
	delay_ms(250);
	display_LED_bar(1);
	delay_ms(250);
	display_LED_bar(0);
	delay_ms(250);
	display_LED_bar(255);
	delay_ms(250);
	display_LED_bar(0);
	delay_ms(250);
	display_LED_bar(255);
	delay_ms(250);
	display_LED_bar(0);
	
	// main running loop
	while(1)
	{
		// poll buttons
		button_push_event = poll_buttons();
		// handle buttone event
		code_check_flag = button_handler(button_push_event, current_code_array);
		// if code check flag set, check to see if the code matches
		// call code check function
		// update LED if needed
		if (code_check_flag == 1)
		{
			led_update = code_check(current_code_array, code_flag_array, &LED_reg);
			// update LED if needed
			if (led_update == 1)
			{
				if (code_flag_array[8] == 1)
				{
					code_flag_array[8] = 0;
					if (b == 0)
					{
						b = 1;
					}
					else
					{
						b = 0;
					}
				}
				display_LED_bar(LED_reg);
				if (b == 1)
				{
					display_LED_bar(0);
				}
				i = 0;
				for (i; i < sizeof(current_code_array); ++i)
				{
					current_code_array[i] = 0;
				}
			}
		}
		
	}

}
