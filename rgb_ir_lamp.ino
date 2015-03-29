#include "ir_rgb.h"
#include "rgb_ir_map.h"

#define R_PIN 9
#define G_PIN 10
#define B_PIN 11

int color_red = 0;
int color_green = 0;
int color_blue = 0;
int mode = 0;
unsigned int number_loop = 0;
int fondu = 0;
unsigned int delay_n_loop = 200;
int pwm_max = 255;
unsigned int cmd_ir = 0;
unsigned int old_cmd_ir = 0;
int ir_n = 0;

void setup()
{
	Serial.begin(115200);
	rgb_ir_init();
	Serial.println("Read");
}

void loop() {
	rgb_rcv();
	if(mode == 1 && number_loop >= delay_n_loop)
	{
		number_loop = 0;
		if(fondu == 0)
		{
			if(color_red < 255)
				color_red++;
			else
			{
				color_green++;
				color_blue = 0; 
				fondu++;
			}
		}
		else if(fondu == 1)
		{
			if(color_green < 255)
			{
				color_green++;
			}
			else
			{
				color_red--;
				color_blue++;
				fondu++;
			}
		}
		else if(fondu == 2)
		{
			if(color_blue < 255)
			{
				color_blue++;
				color_red--;
			}
			else
			{
				color_green--;
				color_red++;
				fondu++;
			}
		}
		else if(fondu == 3)
		{
			if(color_red < 255)
			{
				color_red++;
				color_green--;
			}
			else
			{
				color_blue--;
				color_green++;
				fondu++;
			}
		}
		else if(fondu == 4)
		{
			if(color_green < 255)
			{
				color_green++;
				color_blue--;
			}
			else
			{
				color_blue++;
				color_red--;
				fondu = 2;
			}
		}
	}
	if(rgb_ir_new_val())
	{
		cmd_ir = rgb_ir_val();
		if(cmd_ir != old_cmd_ir)
		{
			ir_n = 0;
			old_cmd_ir = cmd_ir;
		}
		if(ir_n == 0)
		{
			Serial.println(cmd_ir);
			switch(cmd_ir)
			{
				case RED_P:
					mode = 0;
					if(color_red <= 253)
						color_red += 2;
					else
						color_red = 255;
					break;
				case RED_M:
					mode = 0;
					if(color_red >= 2)
						color_red -= 2;
					else
						color_red = 0;
					break;
				case GREEN_P:
					mode = 0;
					if(color_green <= 253)
						color_green += 2;
					else
						color_green = 255;
					break;
				case GREEN_M:
					mode = 0;
					if(color_green >=  2)
						color_green -= 2;
					else
						color_green = 0;
					break;
				case BLUE_P:
					mode = 0;
					if(color_blue < 253)
						color_blue += 2;
					else
						color_blue = 255;
					break;
				case BLUE_M:
					mode = 0;
					if(color_blue >= 2)
						color_blue -= 2;
					else
						color_blue = 0;
					break;
				case WHITE:
					mode = 0;
					color_red = 255;
					color_green = 255;
					color_blue = 255;
					break;
				case SHUTDOWN:
					mode = 0;
					color_red = 0;
					color_green = 0;
					color_blue = 0;
					break;
				case LIGHT_UP:
					if(color_red <= 253)
						color_red += 2;
					else
						color_red = 255;
					if(color_green <= 253)
						color_green += 2;
					else
						color_green = 255;
					if(color_blue <= 253)
						color_blue += 2;
					else
						color_blue = 255;
					break;
				case LIGHT_DOWN:
					if(color_red >= 2)
						color_red -= 2;
					else
						color_red = 0;
					if(color_green >=2)
						color_green -= 2;
					else
						color_green = 0;
					if(color_blue >= 2)
						color_blue -= 2;
					else
						color_blue = 0;
					break;
				case RED:
					mode = 0;
					color_red = 255;
					color_green = 0;
					color_blue = 0;
					break;
				case GREEN:
					mode = 0;
					color_red = 0;
					color_green = 255;
					color_blue = 0;
					break;
				case BLUE:
					mode = 0;
					color_red = 0;
					color_green = 0;
					color_blue = 255;
					break;
				case ORANGE_DARK:
					mode = 0;
					color_red = 204;
					color_green = 85;
					color_blue = 0;
					break;
				case ORANGE:
					mode = 0;
					color_red = 255;
					color_green = 127;
					color_blue = 0;
					break;
				case CAPUCINE:
					mode = 0;
					color_red = 255;
					color_green = 94;
					color_blue = 77;
					break;
				case YELLOW:
					mode = 0;
					color_red = 231;
					color_green = 240;
					color_blue = 13;
					break;
				case EMERALD:
					mode = 0;
					color_red = 1;
					color_green = 215;
					color_blue = 88;
					break;
				case GLAUCOUS:
					mode = 0;
					color_red = 100;
					color_green = 155;
					color_blue = 136;
					break;
				case TEAL:
					mode = 0;
					color_red = 0;
					color_green = 142;
					color_blue = 142;
					break;
				case LAPIS:
					mode = 0;
					color_red = 38;
					color_green = 97;
					color_blue = 156;
					break;
				case BLUE_BRIGHT:
					mode = 0;
					color_red = 00;
					color_green = 47;
					color_blue = 167;
					break;
				case PURPLE:
					mode = 0;
					color_red = 46;
					color_green = 0;
					color_blue = 108;
					break;
				case PINK:
					color_red = 249;
					color_green = 0;
					color_blue = 158;
					break;
				case ZINZOLIN:
					mode = 0;
					color_red = 108;
					color_green = 2;
					color_blue = 119;
					break;
				case PINK_SALMON1:
					mode = 0;
					color_red = 255;
					color_green = 145;
					color_blue = 164;
					break;
				case PLAY:
					if(mode == 0)
                                        {
                                                color_red = 0;
      				          	color_green = 0;
      				        	color_blue = 0;
						mode = 1;
                                        }
					else
						mode = 0;
					break;
				case QUICK:
					if(delay_n_loop >= 10)
						delay_n_loop -= 10;
					else
						delay_n_loop = 0;
					break;
				case SLOW:
					delay_n_loop += 10;
					break;
					
					/*
					color_red = ;
					color_green = ;
					color_blue = ;
					break;*/
			}
		ir_n++;
                }
		else
			ir_n = 0;
	}
	analogWrite(R_PIN, color_red);
	analogWrite(G_PIN, color_green);
	analogWrite(B_PIN, color_blue);
	number_loop++;
	//delay(1);
}










