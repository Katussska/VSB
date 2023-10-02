#include "mbed.h"

// LEDs on K64F-KIT - instances of class DigitalOut
DigitalOut led1(PTA1);
DigitalOut led2(PTA2);

DigitalOut led3(PTC0);
DigitalOut led4(PTC1);
DigitalOut led5(PTC2);
DigitalOut led6(PTC3);
DigitalOut led7(PTC4);
DigitalOut led8(PTC5);
DigitalOut led10(PTC7);
DigitalOut led11(PTC8);

DigitalOut led12(PTB2);
DigitalOut led13(PTB3);
DigitalOut led14(PTB9);

DigitalOut led15(PTB10);
DigitalOut led16(PTB11);
DigitalOut led17(PTB18);

DigitalOut led18(PTB19);
DigitalOut led19(PTB20);
DigitalOut led20(PTB23);

// Button on K64F-KIT - instance of class DigitalIn
DigitalIn button9( PTC9 );
DigitalIn button10( PTC10 );
DigitalIn button11(PTC11);
DigitalIn button12(PTC12);
int mode = 0;
int indexled = 0;
int ticks = 0;
int limit = 6;
bool changed = false;
bool block9 = false;
bool block10 = false;
bool block11 = false;
bool block12 = false;
int rgbindex = 0;
int rgbCollorIndex = 0;
int numToBin = 0;
DigitalOut ledky[] = {led3,led4,led5,led6,led7,led8,led10,led11};
DigitalOut RGBLED[3][3] = {{led12,led13,led14},{led15,led16,led17},{led18,led19,led20}};


bool binarryled[8];

void changeMode()
{
	if(button9 == 1)
	{
		block9 = false;
	}
	if(button9 == 0 && block9 == false)
	{
		changed = true;
			if(mode +1 > 2)
			{
				mode = 0;
			}
			else
			{
				mode ++;
			}
			block9 = true;
	}
}


int speedtick = 0;
int speed = 99;
int ledIndex = 0;
int endLed = 3;
bool Right = true;



void lightbar()
{

	ledky[ledIndex] = 0;
	ticks++;
	speedtick++;

	if (button10 == 1)
	{
		block10 = false;
	}

	if (button10 == 0 && block10 == false)			// nastaveni rychlostii
	{
		if (speed + 1 > 100)
		{
			speed = 0;
		}
		else
		{
			speed++;
		}
		block10 = true;
	}

	if (button12 == 1)
	{
		block12 = false;
	}
	if (button12 == 0 && block12 == false)			// nastaveni koncove led
	{
		if (endLed + 1 > 8)
		{
			endLed = 3;
		}
		else
		{
			endLed++;
		}
		block12 = true;
	}

	if (speedtick >= speed)								// switch zarovek
	{
		if(Right)
		{
			ledIndex++;
			if(ledIndex >= endLed)
			{
				Right = false;
			}

		}
		else
		{
			ledIndex--;
			if(ledIndex -1 == 0)
			{
				Right = true;
			}
		}
		speedtick = 0;
	}

	if (ticks >= limit)	// time to switch on?
	{
		ledky[ledIndex] = 1;
	}


	if (ticks >= 13)	//reset loopu
	{
		ticks = 0;
	}


}


int rgbLedindex = 0;
int collorindex = 0;
void rgbLeds()
{
	RGBLED[rgbLedindex][collorindex] = 1;
	ticks++;
	if(button12 == 1)
	{
		block12 = false;
	}
	if (button12 == 0 && block12 == false)			// check button
	{
		if (limit + 1 > 13)
		{
			limit = 0;
		}
		else
		{
			limit++;
		}
		block12 = true;
	}

	if(button10 == 0 && block10 == false)
	{

		/*for(int z = 0; z < 3 ;z++)
		{
			RGBLED[rgbLedindex][z] = 0;
		}*/

		if(rgbLedindex + 1 > 2)
		{
			rgbLedindex = 0;
		}
		else
		{
			rgbLedindex++;
		}

		block10 = true;
	}


	if(button11 == 1)   			//nastaveni rgb ledky
	{
		block11 = false;
	}
	if ( button11 == 0 && block11 == false)			// check button
	{
		if(rgbCollorIndex + 1 > 2)
		{
			rgbCollorIndex = 0;
		}
		else
		{
			rgbCollorIndex++;
		}

		block11 = true;
	}

	RGBLED[rgbLedindex][collorindex] = 0;                            //RGB JE VYPNUTA


	if(button12 == 1)
	{
		block12 = false;
	}
	if ( button12 == 0 && block12 == false)			// check button
	{
		if(limit + 1 > 13)
			{
				limit = 0;
			}
			else
			{
				limit++;
			}
			block12 = true;
	}

	if ( ticks >= limit)	// time to switch on?
	{
		RGBLED[rgbLedindex][collorindex] =1;
	}


	if ( ticks >= 13 )
	{
		ticks = 0;
	}
}

void binary()
{
	int num = numToBin;
	ticks++;

	for(int i = 0;i < 8;i++)
			{
				if(binarryled[i])
				{
					ledky[i] = 0;
				}

			}


	for(int i = 0; i < 8;i++)
	{
		ledky[i] = 0;
	}

	if(button10 == 1)							//zmena rgb ledky
	{
		block10 = false;
	}

	if(button10 == 0 && block10 == false)
	{

		numToBin--;
		block10 = true;
	}


	if(button11 == 1)   			//nastaveni rgb ledky
	{
		block11 = false;
	}
	if ( button11 == 0 && block11 == false)			// check button
	{
		numToBin++;
		block11 = true;
	}

	if(button12 == 1)
	{
		block12 = false;
	}
	if ( button12 == 0 && block12 == false)			// změna frequence
	{
		if(limit + 1 > 13)
			{
				limit = 0;
			}
			else
			{
				limit++;
			}
			block12 = true;
	}

	for (int i = 8 - 1;i >= 0;i--)					// prevod na binar
	{
		if (num % 2 == 1)
		{
			binarryled[i] = true;

		}
		else
		{
			binarryled[i] = false;

		}
		num = num / 2;
	}



	if ( ticks >= limit)	// time to switch on?
	{
		for(int i = 0;i < 8;i++)
		{
			if(binarryled[i])
			{
				ledky[i] = 1;
			}

		}

	}

	if ( ticks >= 13 )	//reset loopu
	{
		ticks = 0;
	}


}



int main()
{
	Ticker modeticker;
	Ticker ticker;
	std::chrono::milliseconds l_tout( 1 );

	modeticker.attach(changeMode, l_tout );
	//ticker.attach(binary,l_tout);
	ticker.attach(lightbar,l_tout);
	//ticker.attach(rgbLeds,l_tout);


	while ( 1 )
	{}

/*	{ if(mode == 0&&changed)
	{
		  ticker.detach();
		  ticker.attach(rgbLeds,l_tout);
		  changed = false;
	  }
	  if(mode == 1&&changed)
	  {
		  ticker.detach();
		  ticker.attach(binary,l_tout);
		  changed = false;
	  }
	  if(mode == 2&&changed)
	  {
		  ticker.detach();
		  ticker.attach(lightbar, l_tout);
		  changed = false;
	  }
	}*/
}

