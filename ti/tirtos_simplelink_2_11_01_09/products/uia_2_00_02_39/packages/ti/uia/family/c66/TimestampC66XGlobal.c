/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  ======== TimestampC64X.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Startup.h>

#include "package/internal/TimestampC66XGlobal.xdc.h"



Int TimestampC66XGlobal_Module_startup(Int state) {

    volatile UInt32* globalTimerCntLo = (UInt32 *)(TimestampC66XGlobal_timerBaseAdrs);

    // start the timer
     *globalTimerCntLo = 0;
    return (Startup_DONE);
}
/*
 *  ======== TimestampC66XGlobal_get32 ========
 */
Bits32 TimestampC66XGlobal_get32() {
    volatile UInt32* globalTimerCntLo = (UInt32 *)(TimestampC66XGlobal_timerBaseAdrs);
    return ((Bits32)*globalTimerCntLo);
}

/*
 *  ======== TimestampC66XGlobal_get64 ========
 *  Reads the timer's timestamp register and returns the 64b result.
 *
 *  NOTE: caller's must ensure that this function is protected
 *  from preemption in order to ensure that a coherent 64b result is returned.
 *  Since this is a shared resource, it is best if some form of
 *  system-level lock (e.g. Lampart's bakery algorithm, spinlock or Peterson lock)
 *  or IPC round-robin mechanism is used to ensure that there are no collisions.
 */
Void TimestampC66XGlobal_get64(Types_Timestamp64 *result) {
    /*  must read the low word of the timestamp first, as this */
    /* causes a snapshot of the high word to be stored in TSCH  */
    volatile UInt32* globalTimerCntLo = (UInt32 *)(TimestampC66XGlobal_timerBaseAdrs);
    volatile UInt32* globalTimerCntHi = (UInt32 *)(4+TimestampC66XGlobal_timerBaseAdrs);

    result->lo = (Bits32)*globalTimerCntLo;
    result->hi = (Bits32)*globalTimerCntHi;
}

/*
 *  ======== TimestampC66XGlobal_getFreq ========
 */
Void TimestampC66XGlobal_getFreq(Types_FreqHz *freq) {
    freq->lo = TimestampC66XGlobal_maxTimerClockFreq.lo;
    freq->hi = TimestampC66XGlobal_maxTimerClockFreq.hi;
}
