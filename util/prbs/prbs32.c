/********************************************************************************************
*  _  ___   ____  __    _____         _ _  ___ _   
* | \| \ \ / /  \/  |__|_   _|__  ___| | |/ (_) |_ 
* | .` |\ V /| |\/| / -_)| |/ _ \/ _ \ | ' <| |  _|
* |_|\_| \_/ |_|  |_\___||_|\___/\___/_|_|\_\_|\__|
*                                                              
* MIT License
* 
* Copyright (c) 2026 Eric L. Yang
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
* https://github.com/elyyang
* elyyang@gmail.com
*
*********************************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint32_t prbs32_next(const uint32_t seed)
{
    uint32_t mask = (1UL << 32) - 1;

    return( ((seed << 1) | (((seed >> 31) ^
                             (seed >> 21) ^
                             (seed >> 1)  ^
                             (seed >> 0)) & 1 )) & mask);
}

void prbs32_fill(uintptr_t startingAddress, uint32_t startingSeed, uint32_t iteration)
{
    for (uint32_t i=0; i<iteration; i++)
    {
        *(uint32_t*)(startingAddress + i * sizeof(uint32_t)) = startingSeed;
        startingSeed = prbs32_next(startingSeed);        
    }
}

bool prbs32_verify(uintptr_t startingAddress, uint32_t startingSeed, uint32_t iteration)
{
    for (uint32_t i=0; i<iteration; i++)
    {
        if(*(uint32_t*)(startingAddress) != startingSeed)
        {
            return false;
        }
        startingSeed = prbs32_next(startingSeed);
        startingAddress += sizeof(uint32_t);
    }    
    return true;
}

#ifdef __cplusplus
}
#endif