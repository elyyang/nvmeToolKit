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

#include "stdio.h"
#include "stdint.h"
#include "assertLib.h"


void displayData(uintptr_t address, uint32_t nBytes, uint32_t bytePerLine)
{
    NVME_DBG_ASSERT((bytePerLine%4)==0, "bytePerLine need to be dword aligned!")
    NVME_DBG_ASSERT((bytePerLine>=4), "bytePerLine need to be dword aligned!")
    
    printf("--------------------------------------------------------------------------------\n");
    printf("Line \t Address \t\t Data \n");
    printf("--------------------------------------------------------------------------------\n");

    for(uint32_t i = 0; i<nBytes; i++)
    {
        if( i % bytePerLine == 0)
        {
            printf("\n %4d \t 0x%08lx \t", i, (address + i));            
        }           
        printf("%.2x ", *((uint8_t*)address + i));
    } 

    printf("\n\n");
}

void displayDataChar(uintptr_t address, uint32_t nBytes, uint32_t bytePerLine)
{
    NVME_DBG_ASSERT((bytePerLine%4)==0, "bytePerLine need to be dword aligned!")
    NVME_DBG_ASSERT((bytePerLine>=4), "bytePerLine need to be dword aligned!")
   
    printf("--------------------------------------------------------------------------------\n");
    printf("Line \t Address \t\t Data \n");
    printf("--------------------------------------------------------------------------------\n");

    for(uint32_t i = 0; i<nBytes; i++)
    {
        if( i % bytePerLine == 0)
        {
            printf("\n %4d \t 0x%08lx \t", i, (address + i));            
        }           
        printf("%c ", *((uint8_t*)address + i));
    } 

    printf("\n\n"); 
}
