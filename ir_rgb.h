#ifndef IR_RGB
#define IR_RGB

#include <Arduino.h>


void rgb_ir_init();
int rgb_ir_new_val();
unsigned int rgb_ir_val();
void ir();
void rgb_rcv();
void rst_rgb();


#endif
