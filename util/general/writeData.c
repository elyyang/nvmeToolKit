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

#include "stdint.h"

void writeData8(const uintptr_t destinationAddress, const uint32_t offset, const uint32_t size, const uint8_t data) 
{
    uint8_t* bufferPtr = (uint8_t*)destinationAddress + offset;
    
    for(uint32_t i=0; i<(size/sizeof(uint8_t)); i++)
    {
        *(bufferPtr) = data;
        bufferPtr++;
    }
}

void writeData16(const uintptr_t destinationAddress, const uint32_t offset, const uint32_t size, const uint16_t data) 
{
    uint16_t* bufferPtr = (uint16_t*)destinationAddress + offset;

    for(uint32_t i=0; i<(size/sizeof(uint16_t)); i++)
    {
        *(bufferPtr) = data;
        bufferPtr++;
    }
}

void writeData32(const uintptr_t destinationAddress, const uint32_t offset, const uint32_t size, const uint32_t data) 
{
    uint32_t* bufferPtr = (uint32_t*)destinationAddress + offset;
    
    for(uint32_t i=0; i<(size/sizeof(uint32_t)); i++)
    {
        *(bufferPtr) = data;
        bufferPtr++;
    }
}

void writeData(const uintptr_t destinationAddress, const uint32_t offset, const uint32_t size, const char* data) 
{
    uint8_t* bufferPtr = (uint8_t*)destinationAddress + offset;
    
    for(uint32_t i=0; i<(size/sizeof(char)); i++)
    {
        *(bufferPtr) = *(data);
        bufferPtr++;
        data++;
    }
}
