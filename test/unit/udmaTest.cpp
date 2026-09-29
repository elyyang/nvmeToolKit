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

#include "udma.h"
#include "prbs32.h"
#include "util.h"

void test_udma1()
{
    udma_c& udmaDriver = udma_c::getInstance();
   
    for(uint32_t udmaId=0; udmaId<DEFAULT_UDMA_BUFFER_COUNT; udmaId++)
    {        
        uintptr_t bufferAddressUnderTest = udmaDriver.getBufferAddress(udmaId);
        uint32_t bufferSizeUnderTest = udmaDriver.getBufferSize(udmaId);
        uint32_t prbs32StartingSeed = 0x1;

        prbs32_fill(bufferAddressUnderTest, prbs32StartingSeed, BYTE_TO_DWORD(bufferSizeUnderTest));
        bool verificationResult = prbs32_verify(bufferAddressUnderTest, prbs32StartingSeed, BYTE_TO_DWORD(bufferSizeUnderTest));

        if(verificationResult)
        {
            printf("PRBS32 verification passed for buffer index %u\n", udmaId);
        }
        else
        {
            printf("PRBS32 verification failed for buffer index %u\n", udmaId);
        }
    }
}

void test_udma2()
{
    udma_c& udmaDriver = udma_c::getInstance();

    uint32_t udmaId=0;        
    uintptr_t bufferAddressUnderTest = udmaDriver.getBufferAddress(udmaId);
    uint32_t bufferSizeUnderTest = 0x100; // Limit the length to 1024 bytes for demonstration
    uint32_t prbs32StartingSeed = 0x1;

    prbs32_fill(bufferAddressUnderTest, prbs32StartingSeed, BYTE_TO_DWORD(bufferSizeUnderTest));
    udmaDriver.dumpUdmaBufferContent(udmaId, 0, bufferSizeUnderTest+0x100, 4);    
}

#pragma message("add udma clear buffer test")