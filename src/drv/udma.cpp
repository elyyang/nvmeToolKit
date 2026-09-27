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
#include "assertLib.h"
#include "debugPrint.h"

udma_c::udma_c(void)
{    
    NVME_DBG_PRINTF(info, "initialize udma_c!");
    
    #define BYTES_TO_READ 64
    
    char fdIdx[BYTES_TO_READ];    
    char fdPath[BYTES_TO_READ];
    char sizePath[BYTES_TO_READ];
    
    for(uint32_t idx=0; idx<DEFAULT_UDMA_BUFFER_COUNT; idx++)
    {
        sprintf(fdIdx, "%d", idx);//convert uint32_t to string
     
        //1. find out buffer size
        strcpy(sizePath, "/sys/class/u-dma-buf/udmabuf");
        strcat(sizePath, fdIdx);
        strcat(sizePath, "/size");

        char sizeBuffer[BYTES_TO_READ];
        read(open(sizePath, O_RDONLY), sizeBuffer, BYTES_TO_READ);
        sscanf(sizeBuffer, "%u", &mBufferSize[idx]);

        //2. mmap buffer
        strcpy(fdPath, "/dev/udmabuf");
        strcat(fdPath, fdIdx);
        
        udmaBuffer_fd[idx] = open(fdPath, O_RDWR | O_SYNC);       
        NVME_DBG_ASSERT((udmaBuffer_fd[idx]>0), "udmaBuffer_fd failed to open!")

        bufferAddress[idx] = mmap(NULL, mBufferSize[idx], PROT_READ | PROT_WRITE, MAP_SHARED, udmaBuffer_fd[idx], 0);
        NVME_DBG_ASSERT((bufferAddress[idx]!=MAP_FAILED), "bufferAddress map failed!")    

        //3. get physical address of the buffer
        strcpy(fdPath, "/sys/class/u-dma-buf/udmabuf");
        strcat(fdPath, fdIdx);
        strcat(fdPath, "/phys_addr");

        udmaBufferPhysicalAddress_fd[idx] = open(fdPath, O_RDONLY);
        NVME_DBG_ASSERT((udmaBufferPhysicalAddress_fd[idx]>0), "udmaBufferPhysicalAddress_fd failed to open!")

        char buffer[BYTES_TO_READ];

        read(udmaBufferPhysicalAddress_fd[idx], buffer, BYTES_TO_READ);
        sscanf(buffer, "%p", &bufferPhysicalAddress[idx]);
    }
}

udma_c::~udma_c()
{   
    NVME_DBG_PRINTF(info, "clean-up udma_c!");    

    for(uint32_t idx=0; idx<DEFAULT_UDMA_BUFFER_COUNT; idx++)
    {
        close(udmaBuffer_fd[idx]);
        close(udmaBufferPhysicalAddress_fd[idx]);        
        munmap(bufferAddress[idx], mBufferSize[idx]);
    } 
}

udma_c& udma_c::getInstance()
{
    static udma_c instance;
    return instance;
}

uintptr_t udma_c::getBufferAddress(uint32_t bufferIndex)
{
    return (uintptr_t)bufferAddress[bufferIndex];
}

uintptr_t udma_c::getBufferPhysicalAddress(uint32_t bufferIndex)
{
    return (uintptr_t)bufferPhysicalAddress[bufferIndex];
}

uint32_t udma_c::getBufferSize(uint32_t bufferIndex)
{
    return mBufferSize[bufferIndex];
}

void udma_c::dumpUdmaBufferInformation()
{   
    for(uint32_t i=0; i<DEFAULT_UDMA_BUFFER_COUNT; i++)
    {
        printf("[udma buffer %d] address: 0x%lx physical address: 0x%lx size: %u(%#x)\n", i, (uintptr_t)bufferAddress[i], (uintptr_t)bufferPhysicalAddress[i], mBufferSize[i], mBufferSize[i]);    
    }
}

void udma_c::dumpUdmaBufferContent(uint32_t bufferIndex, uint32_t offset, uint32_t length)
{
    NVME_DBG_ASSERT((bufferIndex<DEFAULT_UDMA_BUFFER_COUNT), "bufferIndex out of range!")
    NVME_DBG_ASSERT((offset<getBufferSize(bufferIndex)), "offset out of range!")
    NVME_DBG_ASSERT(((offset+length)<=getBufferSize(bufferIndex)), "length out of range!")

    uint8_t* bufferPtr = (uint8_t*)getBufferAddress(bufferIndex);
    
    for(uint32_t i=0; i<length; i++)
    {
        if(i%16==0)
        {
            printf("\n[udma buffer %d] 0x%lx: ", bufferIndex, (uintptr_t)(bufferPtr+offset+i));
        }
        printf("%02x ", *(bufferPtr+offset+i));
    }
    printf("\n");
}