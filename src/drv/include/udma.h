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

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DEFAULT_UDMA_BUFFER_COUNT   (8)

class udma_c
{
    private:

        udma_c();        
        ~udma_c();
        
        int mUdmaBuffer_fd[DEFAULT_UDMA_BUFFER_COUNT];
        int mUdmaBufferPhysicalAddress_fd[DEFAULT_UDMA_BUFFER_COUNT];        
        void* mBufferAddress[DEFAULT_UDMA_BUFFER_COUNT];
        void* mBufferPhysicalAddress[DEFAULT_UDMA_BUFFER_COUNT];
        uint32_t mBufferSize[DEFAULT_UDMA_BUFFER_COUNT];

    public:

        static udma_c& getInstance();      

        uintptr_t getBufferAddress(uint32_t udmaId);        
        uintptr_t getBufferPhysicalAddress(uint32_t udmaId);
        uint32_t getBufferSize(uint32_t udmaId);

        void dumpUdmaBufferInformation();
        void dumpUdmaBufferContent(uint32_t udmaId, uint32_t offset, uint32_t length);
        void writeBuffer(uint32_t udmaId, uint32_t offset, uint32_t length, uint32_t dwordData);
};
