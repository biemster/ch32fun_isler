#include "ch32fun.h"
#include "isler.h"
#include <stdio.h>

#define LED               PA9
#define LL_TX_POWER_0_DBM 0x12

void blink(int n) {
	for(int i = n-1; i >= 0; i--) {
		funDigitalWrite( LED, FUN_LOW ); // Turn on LED
		Delay_Ms(33);
		funDigitalWrite( LED, FUN_HIGH ); // Turn off LED
		if(i) Delay_Ms(33);
	}
}

int main()
{
	SystemInit();

	funGpioInitAll();
	funPinMode( LED, GPIO_CFGLR_OUT_2Mhz_PP );

	RFCoreInit(LL_TX_POWER_0_DBM);

	// Apple Find My Stuff Packet
	uint8_t adv[] = {0x66, 0x55, 0x44, 0x33, 0x22, 0xd1, // MAC (reversed)
					 0x1e, 0xff, 0x4c, 0x00, 0x12, 0x19, 0x00, // Apple FindMy stuff
					 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xef, 0xfe, 0xdd,0xcc, // key
					 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, // more key
					 0x00, 0x00}; // status byte and one more
	uint8_t adv_channels[] = {37,38,39};

	blink(5);
	printf(".~ TX ~.\n");

#ifdef FUNCONF_SYSTICK_USE_HCLK
	const uint32_t advance = (FUNCONF_SYSTEM_CORE_CLOCK/(3.0));
#else
	const uint32_t advance = (FUNCONF_SYSTEM_CORE_CLOCK/(3.0*8));
#endif

	uint32_t time_of_next_bcast = SysTick->CNT + advance;

	while(1) {
		// printf( "BCAST\n" );
		for(int c = 0; c < sizeof(adv_channels); c++) {
			Frame_TX(adv, sizeof(adv), adv_channels[c]);
		}
		blink(1);

		// Wait for 1/3 of a second to pass from the start/last time.
		while( (int32_t)(SysTick->CNT - time_of_next_bcast) < 0 );
		time_of_next_bcast += advance;
	}
}
