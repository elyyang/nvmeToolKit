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

#include "writeData.h"
#include "displayData.h"
#include "udma.h"

void test_wdata8()
{
    udma_c& udmaDriver = udma_c::getInstance();

    uint32_t udmaId = 0;
    uintptr_t destAddr = udmaDriver.getBufferAddress(udmaId);
    
    udmaDriver.clearUdmaBuffer(udmaId);
    writeData8(destAddr, 0, 0x100, 0xab);     
    udmaDriver.dumpUdmaBufferContent(udmaId, 0, 0x200, 4);
}

void test_wdata16()
{
    udma_c& udmaDriver = udma_c::getInstance();

    uint32_t udmaId = 0;
    uintptr_t destAddr = udmaDriver.getBufferAddress(udmaId);
    
    udmaDriver.clearUdmaBuffer(udmaId);
    writeData16(destAddr, 0, 0x100, 0xaaaa);     
    udmaDriver.dumpUdmaBufferContent(udmaId, 0, 0x200, 4);
}

void test_wdata32()
{
    udma_c& udmaDriver = udma_c::getInstance();

    uint32_t udmaId = 0;
    uintptr_t destAddr = udmaDriver.getBufferAddress(udmaId);
    
    udmaDriver.clearUdmaBuffer(udmaId);
    writeData32(destAddr, 0, 0x1000, 0xaabbccdd);    
    udmaDriver.dumpUdmaBufferContent(udmaId, 0, 0x1100, 4);
}

#pragma message("update writeData unit test to be more comprehensive")
void test_wdata()
{
    udma_c& udmaDriver = udma_c::getInstance();

    uint32_t udmaId = 0;
    uintptr_t destAddr = udmaDriver.getBufferAddress(udmaId);
 
    const char* data = "I've got another confession to make; I'm your fool; Everyone's got their chains to break; Holding you";
    size_t size = strlen(data);

    udmaDriver.clearUdmaBuffer(udmaId);
    writeData(destAddr, 0, size, data);    
    
    displayDataChar(destAddr, size, 0);
    displayDataChar(destAddr, size, 8);
    displayDataChar(destAddr, size, 16);
    displayData(destAddr, size, 16);
}
