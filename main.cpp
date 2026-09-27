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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 

#include "menu.h"
#include "demo.h"
#include "unitTests.h"

menu_c::subMenu g_demo_subMenu;
menu_c::subMenu g_tests_subMenu;
menu_c::subMenu g_pcieUtil_subMenu;
menu_c::subMenu g_nvmeUtil_subMenu;
menu_c::mainMenu g_nvmeToolKit_mainMenu;
menu_c g_nvmeToolKit;

void menuInit()
{
    g_demo_subMenu.addDescription("demo");
    g_demo_subMenu.addItem(demo_uio, "a brief demo on uio_c driver...");
    g_demo_subMenu.addItem(demo_uio2, "bar 0 mem dump...");
    g_demo_subMenu.addItem(demo_udma, "udma_c driver");
    g_demo_subMenu.addItem(demo_nvmeEnumeration, "nvme enumeration");

    g_tests_subMenu.addDescription("unit tests");
    g_tests_subMenu.addItem(test_udma1, "udma prbs test");
    g_tests_subMenu.addItem(test_udma2, "udma dump test");
    g_tests_subMenu.addItem(test_udma3, "udma write test");

    g_pcieUtil_subMenu.addDescription("pcie utilities");
    g_pcieUtil_subMenu.addItem(demo_pcieCfgSpace, "pcie config space dump");

    g_nvmeUtil_subMenu.addDescription("nvme utilities");
    g_nvmeUtil_subMenu.addItem(demo_nvmControllerMmioSpace, "nvme controller capabilities");

    g_nvmeToolKit_mainMenu.addDescription("NVMe Toolkit");
    g_nvmeToolKit_mainMenu.addItem(g_demo_subMenu,     "demo");
    g_nvmeToolKit_mainMenu.addItem(g_tests_subMenu,    "unit tests");
    g_nvmeToolKit_mainMenu.addItem(g_pcieUtil_subMenu, "pcie utilities");
    g_nvmeToolKit_mainMenu.addItem(g_nvmeUtil_subMenu, "nvme utilities");
    
    g_nvmeToolKit.build(g_nvmeToolKit_mainMenu);
    g_nvmeToolKit.run();
}

int g_uioId = 0;

int main(int argc, char* argv[])
{  
  if((argc>1)&&(argv[1]!=NULL))
  { 
    g_uioId = atoi(argv[1]);
  }  

  menuInit(); 
  
  printf("goodbye! \n");
  return 0;
}
