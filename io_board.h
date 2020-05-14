/*
 *
 * particle xenon feather
 *
 *                        .--------------------.
 *                  Reset |16 0.18             |
 *                        |15 3v3              |
 *            (Button 1)  |14 0.11             |
 *                        |13 0v               |
 *                        |12 0.03     Vbat 12 | 
 *                        |11 0.04     Pen  11 | 
 *                        |10 0.28     Vusb 10 | 
 *                        | 9 0.29     1.03  9 | 
 *                        | 8 0.30     1.12  8 |  (Blue LED)
 *                        | 7 0.31     1.11  7 | 
 *                        | 6 1.15     1.10  6 | 
 *                        | 5 1.13     1.08  5 | 
 *                        | 4 1.14     1.02  4 | 
 *             Uart Rx    | 3 0.08     1.01  3 | 
 *             Uart Tx    | 2 0.06     0.27  2 | 
 *                        | 1 nc       0.26  1 | 
 *                        `--------------------'
 *
 *
 */
#ifndef io_board_H_
#define io_board_H_
#include <io_cpu.h>

void io_board_panic (io_t*,int);

#define SPECIALISE_IO_BOARD_IMPLEMENTATION(S) \
    SPECIALISE_IO_CPU_IMPLEMENTATION(S) \
	 .panic = io_board_panic,\
    /**/


#define RESET_PIN				def_nrf_io_input_pin(0,18,NRF_GPIO_ACTIVE_LEVEL_LOW,NRF_GPIO_PIN_NOPULL)

#define LED1_nrf_pin			def_nrf_io_output_pin(1,12,NRF_GPIO_ACTIVE_LEVEL_HIGH,GPIO_PIN_INACTIVE)
#define LED1					((LED1_nrf_pin).io)

void	initialise_io_board (io_t*);


#ifdef IMPLEMENT_IO_BOARD
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

#define SHORT_DELAY(n)		{volatile int i;	for(i = 0; i < (n * 1000);i++);}

void
io_board_panic (io_t *io,int code) {
	DISABLE_INTERRUPTS;
	
	while (1) {
		toggle_io_pin (io,LED1);
		SHORT_DELAY(1000);
	}
}

void
initialise_io_board (io_t *io) {
	initialise_cpu_io (io);

	nrf52_configure_reset_pin (RESET_PIN);
}

#endif /* IMPLEMENT_IO_BOARD */
#endif
/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2020 Gregor Bruce
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
