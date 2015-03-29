#include "ir_rgb.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define __time_out__ 100000

volatile unsigned long tmp[80] = {0};
volatile int nbr_interuption = 0;
volatile int new_val = false;
volatile int egal_val = false;
unsigned int dt = 0;
int val[33] = {0};
unsigned int value = 0;
int test = 0;


void rgb_ir_init()
{
	pinMode(2, INPUT);
	attachInterrupt(0, ir, LOW);
}
void rst_rgb()
{
  new_val = false;
  nbr_interuption = 0;
  value = 0;
}
int rgb_ir_new_val()
{
	return new_val;
}
void rgb_rcv()
{
        dt = 0;
	if(nbr_interuption > 0)
		dt = micros()-tmp[nbr_interuption-1];
	if(test)
	{
               // Serial.println(nbr_interuption);
		cli();
		int b = 0;
		for(int a = 2; a < nbr_interuption ; a += 2)
		{
                    //    Serial.println(666);
			if(tmp[a]-tmp[a-1] <1000)
				val[b] = 0;
			else
				val[b] = 1;
				b++;
                        
		}
 		EICRA = (EICRA&~(1<<ISC01|1<<ISC00)); //Interuption à logique bas
                nbr_interuption = 0;
                new_val = 1;
                test = 0;
                sei();	
	}
        else if(nbr_interuption >= 80 || dt >= __time_out__)
        {
                EICRA = (EICRA&~(1<<ISC01|1<<ISC00)); //Interuption à logique bas
                nbr_interuption = 0;
                new_val = 1;
                test = 0;
        }
}
unsigned int rgb_ir_val()
{
        cli();
        if(!egal_val)
        {
        value = 0;
        for(int a = 0; a<16 ; a++)
			value |= val[32-a]<<a;
        }
        egal_val = 0;
        new_val = 0;
        sei();
        return value;
}
void ir()
{
	tmp[nbr_interuption] = micros();
	if(nbr_interuption == 0)
		EICRA = (EICRA&~(1<<ISC01))|(1<<ISC00); //Interuption à chaque changement logique
	if(nbr_interuption == 1)
	{
		dt = (tmp[1]-tmp[0]);
		if(dt <= 9500 && dt >= 9200)
			nbr_interuption++;
		else
                {
                        EICRA = (EICRA&~(1<<ISC01|1<<ISC00)); //Interuption à logique bas
			nbr_interuption = 0;
                }
	}
	else if(nbr_interuption == 2)
        {
                
                dt = (tmp[2]-tmp[1]);
		//Serial.println(dt);
                if(dt <= 4500 && dt >= 4300)
			nbr_interuption++;
		else if(dt <= 2300 && dt >=  2100)
                {
                  nbr_interuption = 0;
                  test = 0;
                  egal_val = 1;
                  new_val = 1;
                }                
                else
                {
                        EICRA = (EICRA&~(1<<ISC01|1<<ISC00)); //Interuption à logique bas
			nbr_interuption = 0;
                }
        }
        else
        {
                if(!digitalRead(2) && nbr_interuption > 2)
                {
                  dt = tmp[nbr_interuption]-tmp[nbr_interuption-1];
                 // Serial.println(dt);
                  if(dt <= 39750 && dt >= 39500)
                    test = 1;
                }
		nbr_interuption++;
        }
  
}

