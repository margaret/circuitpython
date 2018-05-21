/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Margaret Sy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <string.h>

#include "py/obj.h"
#include "py/runtime.h"
#include "shared-bindings/precise_time/__init__.h"

//| :mod:`precise_time` --- integer time and timing related functions
//| =======================================================================
//|
//| .. module:: precise_time
//|   :synopsis: integer time related functions
//|   :platform: SAMD21
//|
//| The `precise_time` module. See the `time` module instead for an API that is
//| also available in CPython.
//|
//| .. method:: monotonic()
//|
//|   Returns an always increasing value of time with an unknown reference
//|   point. Only use it to compare against other values from `monotonic`.
//|   Unlike time.monotonic, which is a float, precise_time.monotonic returns an
//|   int so precision will not degrade over time.
//|
//|   :return: the current monotonic time
//|   :rtype: int
//|
STATIC mp_obj_t precise_time_monotonic(void) {
    return mp_obj_new_int_from_uint(common_hal_precise_time_monotonic());
}
MP_DEFINE_CONST_FUN_OBJ_0(precise_time_monotonic_obj, precise_time_monotonic);

//| .. method:: sleep(milliseconds)
//|
//|   Sleep for a given number of milliseconds.
//|
//|   :param int seconds: the time to sleep in milliseconds
//|
STATIC mp_obj_t precise_time_sleep(mp_obj_t milliseconds_o) {
    int milliseconds = mp_obj_get_int(milliseconds_o);
    if (milliseconds < 0) {
        mp_raise_ValueError("sleep length must be non-negative");
    }
    common_hal_precise_time_delay_ms(milliseconds);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(precise_time_sleep_obj, precise_time_sleep);

STATIC const mp_rom_map_elem_t precise_time_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR__name__), MP_ROM_QSTR(MP_QSTR_precise_time) },

    { MP_ROM_QSTR(MP_QSTR_monotonic), MP_ROM_PTR(&precise_time_monotonic_obj) },
    { MP_ROM_QSTR(MP_QSTR_sleep), MP_ROM_PTR(&precise_time_sleep_obj) }
};

STATIC MP_DEFINE_CONST_DICT(precise_time_module_globals, precise_time_module_globals_table);

const mp_obj_module_t precise_time_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&precise_time_module_globals,
};