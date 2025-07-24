#ifndef VIDEO_H
#define VIDEO_H

#include "stdint.h"

/*
*	for frame buffer setting
*/
void put_fb(uint32_t x, uint32_t y, char c, uint8_t fg, uint8_t bg);

#endif	//VIDEO_H
