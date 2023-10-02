#include "mbed.h"

DigitalOut led_PTA1( PTA1 );
DigitalOut led_PTA2( PTA2 );

DigitalOut led_0(PTC0);
DigitalOut led_1(PTC1);
DigitalOut led_2(PTC2);
DigitalOut led_3(PTC3);
DigitalOut led_4(PTC4);
DigitalOut led_5(PTC5);
DigitalOut led_6(PTC7);
DigitalOut led_7(PTC8);

DigitalOut rgb0_r(PTB2);
DigitalOut rgb0_g(PTB3);
DigitalOut rgb0_b(PTB9);

DigitalOut rgb1_r(PTB10);
DigitalOut rgb1_g(PTB11);
DigitalOut rgb1_b(PTB18);

DigitalOut rgb2_r(PTB19);
DigitalOut rgb2_g(PTB20);
DigitalOut rgb2_b(PTB23);

DigitalIn btn_PTC9( PTC9 );
DigitalIn btn_PTC10( PTC10 );
DigitalIn btn_PTC11( PTC11 );
DigitalIn btn_PTC12( PTC12 );

struct {
    int r;
    int g;
    int b;
}typedef Color ;

struct {
    DigitalOut r;
    DigitalOut g;
    DigitalOut b;
} typedef RGBLed;

DigitalOut leds[8] {led_0, led_1, led_2, led_3, led_4, led_5, led_6, led_7};

RGBLed rgbleds[3] = {
        RGBLed {
            rgb0_r,
            rgb0_g,
            rgb0_b,
        },
        RGBLed {
                rgb1_r,
                rgb1_g,
                rgb1_b,
        },
        RGBLed {
                rgb2_r,
                rgb2_g,
                rgb2_b,
        },
};

Color colors[6] = {
        // red
        Color{
            .r =  100,
            .g = 0,
            .b = 0,
        },
        // green
        Color{
                .r = 0,
                .g = 100,
                .b = 0,
        },
        // blue
        Color{
            .r = 0,
            .g = 0,
            .b = 100,
        },
        // yellow
        Color{
                .r = 0,
                .g = 100,
                .b = 100,
        },
        // purple
        Color{
                .r = 100,
                .g = 0,
                .b = 100,
        },
        // white
        Color{
            .r = 100,
            .g = 100,
            .b = 100,
        },
};

bool state = false; // false == program 1; true == program 2
bool firstTime = true;

bool isPTC9pressed = false;
bool isPTC10pressed = false;
bool isPTC11pressed = false;
bool isPTC12pressed = false;

int chosenRGBid = 0;
int chosenColor = 0;

int rgbTicks = 0;
int rgbBrightness = 50;
int rgbPeriod = 20;

void activateOneRGB(int id) {
    int pwm = rgbPeriod * rgbBrightness / 100;
    for (int i = 0; i < 3; i++) {
        if(i == id) {
            if (rgbTicks < pwm) {
                rgbleds[i].r = colors[chosenColor].r;
                rgbleds[i].g = colors[chosenColor].g;
                rgbleds[i].b = colors[chosenColor].b;

            } else {
                rgbleds[i].r = 0;
                rgbleds[i].g = 0;
                rgbleds[i].b = 0;
            }
            rgbTicks++;
            if (rgbTicks > rgbPeriod) {
                rgbTicks = 0;
            }
        } else {
            rgbleds[i].r = 0;
            rgbleds[i].g = 0;
            rgbleds[i].b = 0;
        }
    }
}

void handleLedScale() {
    int n = rgbBrightness / 100 * 7;
    for (int i = 0; i < 8; i++) {
        if (i <= n) {
            leds[i] = 1;
        } else {
            leds[i] = 0;
        }
    }
}

void program1() {
    led_PTA1 = 1;
    led_PTA2 = 0;
    ////////



    if (firstTime) {
        activateOneRGB(chosenRGBid);
        firstTime = false;
    }

    // vyber led
    if (btn_PTC10 == 0) {
        if (!isPTC10pressed) {
            chosenRGBid += 1;
            if (chosenRGBid > 2) {
                chosenRGBid = 0;
            }
        }
        isPTC10pressed = true;
    }
    if (btn_PTC10 == 1) {
        isPTC10pressed = false;
    }

    // vyber color
    if (btn_PTC11 == 0) {
        if (!isPTC11pressed) {
            chosenColor++;
            if (chosenColor > 5) {
                chosenColor = 0;
            }
        }
        isPTC11pressed = true;
    }
    if (btn_PTC11 == 1) {
        isPTC11pressed = false;
    }

    // vyber brightness
    if (btn_PTC12 == 0) {
        if (!isPTC12pressed) {
            rgbBrightness += 5;
            if (rgbBrightness > 100) {
                rgbBrightness = 0;
            }
        }
        isPTC12pressed = true;
    }
    if (btn_PTC12 == 1) {
        isPTC12pressed = false;
    }

    activateOneRGB(chosenRGBid);
    handleLedScale();
}

void program2() {
    led_PTA1 = 0;
    led_PTA2 = 1;
}

void stuff() {
    // handle program change
    if (btn_PTC9 == 0) {
        if (!isPTC9pressed) {
            state = !state; // provest pouze jednou po dobu drzeni
        }
        isPTC9pressed = true;
    }
    if (btn_PTC9 == 1) {
        isPTC9pressed = false;
    }

    if (!state) {
        program1();
    } else {
        program2();
    }
}

int main()
{
    Ticker ticky;
    ticky.attach(stuff, 1ms);

    while (true){}
}
