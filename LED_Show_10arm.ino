#include "FastLED.h"

#define NUM_LEDS 250
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

void setup() { 
	// set up
	FastLED.addLeds<WS2811,DATA_PIN, BRG>(leds, NUM_LEDS);
}

/**
 * 
 */
void loop() {	
	// 2 for chill 1 for upbeat
	int tempo = 1;

	clearAll();
	raveSnail(tempo * 20);
	oneArmWipe(tempo * 30); // wipe

	for (int i = 0; i < 4; i++) {
		randRainbowPulse(tempo * 30);
	}

	for (int i = 0; i < 4; i++) {
		oneArmSpin(tempo * 100);
	}
	
	for (int i = 0; i < 4; i++) {
		fireworks2(15 * tempo);
	}
	
	for (int i = 0; i < 4; i++) {
		fireworks1(15 * tempo);
	}

	for (int i = 0; i < 4; i++) {
		rotatingSpiral(tempo * 60);
	}

	explode(20, 30); // one big one to clear previous lights
	for (int i = 20; i > 0; i=i-4) {
		explode(i, 20);
	}
	oneArmWipe(tempo * 30); // wipe

	
	for (int i = 0; i < 4; i++) {
		randArmColors(tempo * 120);
	}

}

/**
 * run a colour all around the arms leaving a faint trail
 */
void raveSnail(int wait) {
	int sat = 200;
	// choose arm at random
	int arms[10] = { 4, 2, 6, 9, 0, 7, 3, 1, 5, 8 };
	for (int a=0; a<10; a++) {
		int arm = arms[a];
		int hue = random8();
		// start and center and run to end
		for (int i=0; i<25; i++) {
			pixelOnHSV(arm, i, hue, sat, 255);
			pixelOnHSV(arm, i-1, hue, sat, 150);
			pixelOnHSV(arm, i-2, hue, sat, 100);
			FastLED.show();
			delay(wait);
		}
		// run to back to center
		for (int i=25; i>=0; i--) {
			pixelOnHSV(arm, i, hue, sat, 200);
			pixelOnHSV(arm, i+1, hue, sat, 100);
			pixelOnHSV(arm, i+2, hue, sat, 50);
			FastLED.show();
			delay(wait);
		}
	}
}

/**
 * Loop around all 10 arms lighting up the whole thing in a random colour
 */
void randArmColors(int wait) {
	for (int i = 0; i < 10; i++) {
		int hue = randbetween(0, 255);
		int arm = randbetween(0, 9);
		armOnHSV(arm, hue, 200, 100);
		FastLED.show();
		delay(wait);
	}
}

/**
 * draw a red and white spiral and rotate it
 */
void rotatingSpiral(int wait) {
	for (int start_arm = 0; start_arm < 10; start_arm++) {
		int arm = start_arm;
		setAllHSV(0, 0, 50);
		int i = 0;
		while (i < 30) {
			// pixelOnHSV(arm, i-3, 0, 200, 50);
			pixelOnHSV(arm, i-2, 0, 200, 100);
			pixelOnHSV(arm, i-1, 0, 200, 150);
			pixelOnHSV(arm, i, 0, 200, 200);
			pixelOnHSV(arm, i+1, 0, 200, 150);
			pixelOnHSV(arm, i+2, 0, 200, 100);
			// pixelOnHSV(arm, i+3, 0, 200, 50);
			i++;
			arm++;
			if (arm > 9) { arm = 0; }
		}
		FastLED.show();
		delay(wait);
	}
}

/**
 * pulse center to edge and back with random colors
 */
void randRainbowPulse(int wait) {
	int hue = randbetween(0, 255);
	for (int pix = 0; pix < 30; pix++) {
		for (int arm = 0; arm < 10; arm++) {
			pixelOnHSV(arm, pix, hue, 250, 200);
			pixelOnHSV(arm, pix-1, hue, 210, 150);
			pixelOnHSV(arm, pix-2, hue, 170, 100);
			pixelOnHSV(arm, pix-3, hue, 130, 80);
		}
		FastLED.show();
		delay(wait);
	}
	hue = randbetween(0, 255);
	for (int pix = 30; pix > 0; pix--) {
		for (int arm = 0; arm < 10; arm++) {
			pixelOnHSV(arm, pix, hue, 250, 200);
			pixelOnHSV(arm, pix+1, hue, 210, 150);
			pixelOnHSV(arm, pix+2, hue, 170, 100);
			pixelOnHSV(arm, pix+3, hue, 130, 80);
		}
		FastLED.show();
		delay(wait);
	}
}

/**
 * Running two pulses at once, one going in a bouncing out
 */
void fireworks1(int wait) {
	for (int i = 8; i < 50; i++) {
		for (int arm = 0; arm < 10; arm++) {
			// reversed bit
			pixelOnRGB(arm, 16-i, 10, 10, 0); //yellow
			pixelOnRGB(arm, 15-i, 20, 20, 0); //yellow
			pixelOnRGB(arm, i-21, 40, 40, 0); //yellow
			pixelOnRGB(arm, i-20, 80, 80, 0); //yellow
			pixelOnRGB(arm, i-19, 120, 120, 0); //yellow
			pixelOnRGB(arm, i-18, 200, 200, 0); //yellow
			//normal bit
			pixelOnRGB(arm, i-3, 80, 0, 0); //red
			pixelOnRGB(arm, i-2, 160, 0, 0); //red
			pixelOnRGB(arm, i-1, 20, 0, 0); //red
			pixelOnRGB(arm, i, 40, 0, 0); //red
			pixelOnRGB(arm, i+1, 80, 0, 0); //red
			pixelOnRGB(arm, i+2, 200, 0, 0); //red
		}
		FastLED.show();
		delay(wait);
		clearAll();
	}
}

/**
 * Pulse a couple lights out
 */
void fireworks2(int wait) {
	for (int i = 0; i < 30; i++) {
		for (int arm = 0; arm < 10; arm++) {
			pixelOnHSV(arm, i, 160, 200, 200);
			pixelOnHSV(arm, i-1, 160, 200, 120);
			pixelOnHSV(arm, 30-i, 85, 200, 200);
			pixelOnHSV(arm, 30-i+1, 85, 200, 120);
		}
		FastLED.show();
		delay(wait);
		clearAll();
	}
}

/**
 * pulse all lights in rainbow
 */
void rainbow() {
	for (int hue = 0; hue < 256; hue=hue+1) {
		for (int arm = 0; arm < 10; arm++) {
			armOnHSV(arm, hue, 200, 100);
		}
		FastLED.show();
	}
}

/**
 * A single pulse going form the center to the 'size' and back
 */
void explode(int wait, int size) {
	for (int i = 0; i < size; i++) {
		for (int arm = 0; arm < 10; arm++) {
			pixelOnHSV(arm, i, 120, 150, 100);
			pixelOnHSV(arm, i+1, 120, 150, 200);
			pixelOnHSV(arm, i+2, 120, 150, 100);
		}
		FastLED.show();
		delay(wait);
		for (int arm = 0; arm < 10; arm++) {	
			pixelOnHSV(arm, i, 0, 0, 0);
			pixelOnHSV(arm, i+1, 0, 0, 0);
			pixelOnHSV(arm, i+2, 0, 0, 0);
		}
		FastLED.show();
	}
	for (int i = size; i > 0; i--) {
		for (int arm = 0; arm < 10; arm++) {
			pixelOnHSV(arm, i, 120, 150, 100);
			pixelOnHSV(arm, i+1, 120, 150, 200);
			pixelOnHSV(arm, i+2, 120, 150, 100);
		}
		FastLED.show();
		delay(wait);
		for (int arm = 0; arm < 10; arm++) {	
			pixelOnHSV(arm, i, 0, 0, 0);
			pixelOnHSV(arm, i+1, 0, 0, 0);
			pixelOnHSV(arm, i+2, 0, 0, 0);
		}
		FastLED.show();
	}
}

/**
 * Spin around all arms to 'wipe' an old pattern clean
 */
void oneArmWipe(int wait) {
	for (int i = 0; i < 10; i++) {
		armOnHSV(i,0,96,120); 
		FastLED.show();
		delay(wait);
		armOnRGB(i,0,0,0); 
		FastLED.show();
	}
}

/**
 * Make a spinning pattern with crude anti aliasing
 */
void oneArmSpin(int wait) {
	for (int i = 0; i < 10; i++) {
		
		int values[10] = { 60,90,120,150,120,90,60,0,0,0 };
		for (int j=0; j<10; j++) {
			armOnHSV(i+j, 0, 150, values[j]);
		}

		FastLED.show();
		delay(wait);
	}
}

/**
 * Make a spinning pattern with two colors
 */
void twoColorSpin(int wait) {
	for (int i = 0; i < 10; i++) {
		
		int values[10] = { 100,120,150,120,100,100,120,150,120,100 };
		int hues[10] = { 85,85,85,85,85,0,0,0,0,0 };
		for (int j=0; j<10; j++) {
			armOnHSV(i+j, hues[j], 150, values[j]);
		}

		FastLED.show();
		delay(wait);
	}
}

/**
 * Make a spinning pattern with crude anti aliasing
 */
void twoArmSpin(int wait) {
	for (int i = 0; i < 10; i++) {
		
		int values[10] = { 150,80,0,0,80,150,80,0,0,80 };
		for (int j=0; j<10; j++) {
			armOnHSV(i+j, 0, 150, values[j]);
		}

		FastLED.show();
		delay(wait);
	}
}

/**
 * Switch all lights on to a warm white
 */
void warmWhite() {
	for (int i = 0; i < 10; i++) {
		// armOnRGB(i, 255, 147, 41);
		armOnHSV(i, 30, 150, 200);
	}
	FastLED.show();
	delay(1000);
}

/***************************************
 * Utility functions from here down
 * only called by other funtions
 **************************************/

// clear all
void clearAll() {
	for (int i = 0; i < 10; i++) {
		armOnRGB(i, 0, 0, 0);
	}
}

// Set all lights to a color
void setAllHSV(int h, int s, int v) {
	for (int i = 0; i < 10; i++) {
		armOnHSV(i, h, s, v);
	}
}

// turn on an arm
void armOnRGB(int arm_num, int r, int g, int b) {
	while (arm_num >= 10) { arm_num = arm_num - 10; }
	for(int i = 0; i < 30; i++) {
		pixelOnRGB(arm_num, i, r, g, b);
	}
}
void armOnHSV(int arm_num, int h, int s, int v) {
	while (arm_num >= 10) { arm_num = arm_num - 10; }
	for(int i = 0; i < 30; i++) {
		pixelOnHSV(arm_num, i, h, s, v);
	}
}

// turn on a pixel
void pixelOnRGB(int arm_num, int rel_LED_num, int r, int g, int b) {
	int p = getPixel(arm_num, rel_LED_num);
	if (p != -1) {
		leds[p].setRGB(r,g,b);
	}
}
void pixelOnHSV(int arm_num, int rel_LED_num, int h, int s, int v) {
	int p = getPixel(arm_num, rel_LED_num);
	if (p != -1) {
		leds[p].setHSV(h,s,v);
	}
}

// generate random interger
int randbetween(int min, int max) {
	return rand()%(max-min + 1) + min;
}

// get a pixel based off it's arm and relative position number
int getPixel(int arm_num, int rel_LED_num) {
	int abs_LED_num = 0;
	int arm_0_pos = 0;
	bool reverse = false;

	// figure out if arm is postive or reverse
	if ( arm_num == 0 || arm_num == 2 || arm_num == 4 || arm_num == 6 || arm_num == 8 ) { reverse = true; }
	// if arm number is out of bounds return -1 (to ignore request)
	if ( arm_num > 9 ) { return -1; }
	
	// find absolute position of LED #0 based on arm number
	switch (arm_num) {
		case 0: arm_0_pos = 23; break;
		case 1: arm_0_pos = 75; break;
		case 2: arm_0_pos = 125; break;
		case 3: arm_0_pos = 171; break;
		case 4: arm_0_pos = 230; break;
		case 5: arm_0_pos = 24; break;
		case 6: arm_0_pos = 74; break;
		case 7: arm_0_pos = 126; break;
		case 8: arm_0_pos = 170; break;
		case 9: arm_0_pos = 231; break;
	}

	// if arm is postive add relative number, else minus relative nuber 
	if (reverse) {
		abs_LED_num = arm_0_pos - rel_LED_num;
	} else {
		abs_LED_num = arm_0_pos + rel_LED_num;
	}

	// if absolute number is outside range, return -1
	switch (arm_num) {
		case 0: if (abs_LED_num < 0 || abs_LED_num > 23 ) { abs_LED_num = -1; } break;
		case 1: if (abs_LED_num < 75 || abs_LED_num > 99 ) { abs_LED_num = -1; } break;
		case 2: if (abs_LED_num < 100 || abs_LED_num > 125 ) { abs_LED_num = -1; } break;
		case 3: if (abs_LED_num < 171 || abs_LED_num > 199 ) { abs_LED_num = -1; } break;
		case 4: if (abs_LED_num < 200 || abs_LED_num > 230 ) { abs_LED_num = -1; } break;
		case 5: if (abs_LED_num < 24 || abs_LED_num > 49 ) { abs_LED_num = -1; } break;
		case 6: if (abs_LED_num < 50 || abs_LED_num > 74 ) { abs_LED_num = -1; } break;
		case 7: if (abs_LED_num < 126 || abs_LED_num > 149 ) { abs_LED_num = -1; } break;
		case 8: if (abs_LED_num < 150 || abs_LED_num > 170 ) { abs_LED_num = -1; } break;
		case 9: if (abs_LED_num < 231 || abs_LED_num > 249 ) { abs_LED_num = -1; } break;
	}

	return abs_LED_num;
}
