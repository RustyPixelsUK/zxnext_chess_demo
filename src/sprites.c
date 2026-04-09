#include <arch/zxn.h>
#include <intrinsic.h>
#include <string.h>
#include <stdlib.h>
#include "sprites.h"
#include "globals.h"
#include "zxnext/src/bank.h"
#include "zxnext/src/sprite.h"
#include "chessmen.h"

void sprites_create(void)
{
	uint8_t chessman_count[12];
	uint8_t fig_offset[] = { 0, 8, 10, 12, 14, 15 };
	uint8_t fig_count[] = { 8, 2, 2, 2, 1, 1 };
	int8_t polestart[] =
	{
		-FR,-FN,-FB,-FQ,-FK,-FB,-FN,-FR,
		-FP,-FP,-FP,-FP,-FP,-FP,-FP,-FP,
		0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,
		FP, FP, FP, FP, FP, FP, FP, FP,
		FR, FN, FB, FQ, FK, FB, FN, FR
	};

	memset(chessman_count, 0, 12);
	
	uint8_t sprite_count = 0;

	for (uint8_t i = 0; i < 32; i++)
	{
		uint8_t fig_index = sprite_count % 6;
		uint8_t chessman_index = sprite_count % 12;
		uint8_t sprite_index = i * 4;
		uint16_t sprite_offset = chessman_index * 512;
	
		sprite_set_pattern(sprite_index, chessmen_spr + sprite_offset, true);
		sprite_set_attributes(sprite_index, sprite_index, 0, 0, 0, 0, 0, SPRITE_VISIBLE | SPRITE_ANCHOR | SPRITE_4BIT);
		sprite_set_pattern(sprite_index + 1, chessmen_spr + sprite_offset + 128, true);
		sprite_set_attributes(sprite_index + 1, 1, 16, 0, 0, 0, 0, SPRITE_VISIBLE | SPRITE_4BIT);
		sprite_set_pattern(sprite_index + 2, chessmen_spr + sprite_offset + 256, true);
		sprite_set_attributes(sprite_index + 2, 2, 0, 16, 0, 0, 0, SPRITE_VISIBLE | SPRITE_4BIT);
		sprite_set_pattern(sprite_index + 3, chessmen_spr + sprite_offset + 384, true);
		sprite_set_attributes(sprite_index + 3, 3, 16, 16, 0, 0, 0, SPRITE_VISIBLE | SPRITE_4BIT);
		
		if (chessman_count[sprite_count] < fig_count[fig_index] - 1)
			chessman_count[sprite_count]++;
		else
			sprite_count++;
	}

	memset(chessman_count, 0, 12);
	
	for (uint8_t y = 0; y < 8; y++)
	{
		for (uint8_t x = 0; x < 8; x++)
		{
			int8_t f = polestart[y * 8 + x];
			
			if (f == 0)
				continue;
			
			uint8_t fig_index = abs(f) - 1;
			uint8_t chessman_index = fig_index + (f < 0 ? 0 : 6);
			uint8_t sprite_index = (fig_offset[fig_index] + chessman_count[chessman_index]) + (f < 0 ? 0 : 16);
			
			sprite_update(sprite_index, 14 + (x * 28), 14 + (y * 28));
			
			if (chessman_count[chessman_index] < fig_count[fig_index] - 1)
				chessman_count[chessman_index]++;
		}
	}
}