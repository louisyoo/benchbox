/*!The Benchmark Testing Box 
 * 
 * Benchbox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * Benchbox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with Benchbox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2016-2020, ruki All rights reserved.
 *
 * @author      ruki
 * @file        main.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox/tbox.h"
#ifndef asm
#   define asm __tb_asm__
#endif
#include "libmill/libmill.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the switch count
#define COUNT       (10000000)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
static coroutine tb_void_t switchtask(tb_size_t count)
{
    // loop
    while (count-- > 0) yield();
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    // init tbox
    if (!tb_init(tb_null, tb_null)) return -1;

    // init duration
    tb_hong_t duration = tb_mclock();

    // create task
    go(switchtask(COUNT >> 1));

    // scheduling
    tb_size_t count = COUNT >> 1;
    while (count--) yield();

    // computing time
    duration = tb_mclock() - duration;

    // trace
    tb_trace_i("switch: libmill: %d switches in %lld ms, %lld switches per second", COUNT, duration, (((tb_hong_t)1000 * COUNT) / duration));

    // exit tbox
    tb_exit();

    // ok
    return 0;
}