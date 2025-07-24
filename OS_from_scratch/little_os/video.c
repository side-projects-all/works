#include "video.h"

#define VIDEO_MEMORY ((volatile uint16_t*)0xB8000)
#define SCREEN_WIDTH 80u
#define SCREEN_HEIGHT 25u

void put_fb(uint32_t row, uint32_t col, char c, uint8_t fg, uint8_t bg) {
	if (col >= SCREEN_WIDTH || row >= SCREEN_HEIGHT) return;

	uint8_t color = (fg << 4) | (bg & 0x0F);
	uint16_t ch = (color << 8) | (uint8_t)c;
	VIDEO_MEMORY[row * SCREEN_WIDTH + col] = ch;
}
