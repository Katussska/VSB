#include "mbed.h"

DigitalOut led_PTA1(PTA1);
DigitalOut led_PTA2(PTA2);

DigitalOut led_0(PTC0);
DigitalOut led_1(PTC1);
DigitalOut led_2(PTC2);
DigitalOut led_3(PTC3);
DigitalOut led_4(PTC4);
DigitalOut led_5(PTC5);
DigitalOut led_6(PTC7);
DigitalOut led_7(PTC8);

DigitalIn btn_PTC9(PTC9);
DigitalIn btn_PTC10(PTC10);
DigitalIn btn_PTC11(PTC11);
DigitalIn btn_PTC12(PTC12);

struct
{
    DigitalOut r;
    DigitalOut g;
    DigitalOut b;
} typedef RGBLed;

struct
{
    int r;
    int g;
    int b;
} typedef Color;

RGBLed rgbleds[3] = {
    RGBLed{
        rgb0_r,
        rgb0_g,
        rgb0_b,
    },
    RGBLed{
        rgb1_r,
        rgb1_g,
        rgb1_b,
    },
    RGBLed{
        rgb2_r,
        rgb2_g,
        rgb2_b,
    },
};

Color colors[6] = {
    // red
    Color{
        .r = 100,
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

double jas_0 = 0;
double jas_1 = 0;
double jas_2 = 0;
double jas_3 = 0;
double jas_4 = 0;
double jas_5 = 0;
double jas_6 = 0;
double jas_7 = 0;

double rgbJas_0 = 0;
double rgbJas_1 = 0;
double rgbJas_2 = 0;

DigitalOut leds[8] = {led_0, led_1, led_2, led_3, led_4, led_5, led_6, led_7};
double ledJas[8] = {jas_0, jas_1, jas_2, jas_3, jas_4, jas_5, jas_6, jas_7};
double rgbJas[3] = {rgbJas_0, rgbJas_1, rgbJas_2};

bool isPTC9pressed = false;
bool isPTC10pressed = false;
bool isPTC11pressed = false;
bool isPTC12pressed = false;

int ticks = 0;
int m = 0; // program

// led
double ledPeriod = 20;
int i = 0;
int j = 0;
int c = 0;

// rgb
double rgbPeriod = 20;
int chosenColor = 0;
int a = 0;
int b = 0;

// LED SEKCE

// vyber led
void task1_1()
{
    if (btn_PTC9 == 0)
    {
        if (!isPTC9pressed)
        {
            j++;
            if (j == 8)
            {
                j = 0;
            }
        }
    }
    isPTC9pressed = true;
    if (btn_PTC9 == 1)
    {
        isPTC9pressed = false;
    }
}

// manipulace s jasem led
void task1_2()
{
    if (btn_PTC10 == 0)
    {
        ledJas[j] += 0.05;
        if (ledJas[j] > 100)
        {
            ledJas[j] = -10;
        }
    }
}

// sviceni led
void task1_3()
{
    for (int i = 0; i < 8; i++)
    {
        double brightness = ledPeriod * ledJas[i] / 100;
        if (ticks < brightness)
        {
            leds[i] = 1;
        }
        else
        {
            leds[i] = 0;
        }
        ticks++;
        if (ticks > ledPeriod)
        {
            ticks = 0;
        }
    }
}

// nastaveni jasu vsech ledek pomoci 2 tlacitek (50% neslo tak poznat, proto tam je 10%)
void task2()
{
    if (btn_PTC9 == 0 && btn_PTC10 == 0)
    {
        for (int k = 0; k < 8; k++)
        {
            ledJas[k] = 10;
        }
    }
}

// prechod mezi blikanim a stalym svicenim
void task3()
{
    if (btn_PTC11 == 0)
    {
        if (!isPTC11pressed && c == 0)
        {
            ledPeriod = 2000;
            c++;
        }
        else if (!isPTC11pressed && c == 1)
        {
            ledPeriod = 20;
            c--;
        }
    }
    isPTC11pressed = true;
    if (btn_PTC11 == 1)
    {
        isPTC11pressed = false;
    }
}

// RGB SEKCE

// vyber rgb
void task4_1()
{
    if (btn_PTC9 == 0)
    {
        if (!isPTC9pressed)
        {
            a++;
            if (a == 3)
            {
                a = 0;
            }
        }
    }
    isPTC9pressed = true;
    if (btn_PTC9 == 1)
    {
        isPTC9pressed = false;
    }
}

// manipulace s jasem rgb
void task4_2()
{
    if (btn_PTC10 == 0)
    {
        rgbJas[a] += 0.05;
        if (rgbJas[a] > 100)
        {
            rgbJas[a] = -10;
        }
    }
}

// sviceni rgb
void task4_3()
{
    for (int i = 0; i < 3; i++)
    {
        double rgbBrightness = rgbPeriod * rgbJas[i] / 100;
        if (ticks < rgbBrightness)
        {
            rgbleds[i].r = colors[chosenColor].r;
            rgbleds[i].g = colors[chosenColor].g;
            rgbleds[i].b = colors[chosenColor].b;
        }
        else
        {
            rgbleds[i].r = 0;
            rgbleds[i].g = 0;
            rgbleds[i].b = 0;
        }
        ticks++;
        if (ticks > rgbPeriod)
        {
            ticks = 0;
        }
    }
}

// nastaveni jasu vsech rgb pomoci 2 tlacitek (50% neslo tak poznat, proto tam je 10%)
void task4_4()
{
    if (btn_PTC9 == 0 && btn_PTC10 == 0)
    {
        for (int k = 0; k < 8; k++)
        {
            rgbJas[k] = 10;
        }
    }
}

// prechod mezi blikanim a stalym svicenim
void task4_5()
{
    if (btn_PTC11 == 0)
    {
        if (!isPTC11pressed && c == 0)
        {
            rgbPeriod = 1000;
            c++;
        }
        else if (!isPTC11pressed && c == 1)
        {
            rgbPeriod = 20;
            c--;
        }
    }
    isPTC11pressed = true;
    if (btn_PTC11 == 1)
    {
        isPTC11pressed = false;
    }
}

void bonus()
{
    // vyber barvy ledky pomocí tlacitka 3 a 4
    if (btn_PTC11 == 0 && btn_PTC12 == 0)
    {
        if (!isPTC11pressed && !isPTC12pressed)
        {
            chosenColor++;
            if (chosenColor > 5)
            {
                chosenColor = 0;
            }
        }
        isPTC11pressed = true;
        isPTC11pressed = true;
    }
    if (btn_PTC11 == 1 && btn_PTC12 == 1)
    {
        isPTC11pressed = false;
        isPTC12pressed = false;
    }
}

// main function
void stuff()
{
    // task5
    if (btn_PTC12 == 0)
    {
        if (!isPTC12pressed && m == 0)
        {
            task1_1();
            task1_2();
            task1_3();
            task2();
            task3();

            led_PTA1 = 1;
            led_PTA2 = 0;

            m++;
        }
        else if (!isPTC12pressed && m == 1)
        {
            task4_1();
            task4_2();
            task4_3();
            task4_4();
            task4_5();
            bonus();

            led_PTA1 = 0;
            led_PTA2 = 1;

            m--;
        }
    }
    isPTC12pressed = true;

    if (btn_PTC12 == 1)
    {
        isPTC11pressed = false;
    }
}

int main()
{
    Ticker ticky;
    ticky.attach(stuff, 1ms);
    while (true)
    {
    }
}