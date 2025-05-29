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
	uint8_t frame_info[] = {0xff, 0x10}; // PDU, len

	blink(5);
	printf(".~ RX ~.\n");

	while(1) {
		Frame_RX(frame_info, 37);
		while(!rx_ready);

		blink(1);
		uint8_t len = ((uint8_t*)LLE_BUF)[1];
		printf("RSSI:%d len:%d MAC:", ((uint8_t*)LLE_BUF)[0], len);
		for(int i = 7; i > 2; i--) {
			printf("%02x:", ((uint8_t*)LLE_BUF)[i]);
		}
		printf("%02x data:", ((uint8_t*)LLE_BUF)[2]);
		for(int i = 8; i < len +2; i++) {
			printf("%02x ", ((uint8_t*)LLE_BUF)[i]);
		}
		printf("\n");
	}
}
