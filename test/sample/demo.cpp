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
#include "uio.h"
#include "controllerMmio.h"
#include "pcieCfgSpace.h"
#include "menu.h"
#include "demo.h"
#include "controllerHandle.h"

extern int g_uioId;

void demo_udma()
{
    udma_c& udmaDriver = udma_c::getInstance();
    udmaDriver.dumpUdmaBufferInformation();
}

void demo_uio()
{    
    pcieCfgSpace_c& pcieDrv = pcieCfgSpace_c::getInstance();
  
    printf("BME status: %d \n", pcieDrv.getBusMasterEnable(g_uioId));

    capability_msix_t msixShadow = pcieDrv.getMsixCapability(g_uioId);
    printf("MSIX table BIR: 0x%x \n", msixShadow.msixTableBir);
    printf("MSIX table offset: 0x%x \n", msixShadow.msixTableOffset*8);
    printf("MSIX pba offset: 0x%x \n", msixShadow.pbaOffset*8);
    
    pcieConfigurationHeader_t pcieHeaderShadow = pcieDrv.getPcieConfigHeader(g_uioId);
    printf("pcie vendor id: 0x%x \n", pcieHeaderShadow.type0.vendorId);
    printf("pcie device id: 0x%x \n", pcieHeaderShadow.type0.deviceId);
}

void demo_uio2()
{
    uio_c& uioDriver = uio_c::getInstance(g_uioId);    
    uioDriver.dumpBar0MemorySpace(0, 12);
    uioDriver.dumpBar0MemorySpace(0x1000, 32);
}

void demo_pcieCfgSpace()
{
    pcieCfgSpace_c& pcieDrv = pcieCfgSpace_c::getInstance();

    pcieConfigurationHeader_t pcieHeaderShadow = pcieDrv.getPcieConfigHeader(g_uioId);

    printf("pcie config space (type 0) header:\n");
    printf("vendor id: 0x%x \n", pcieHeaderShadow.type0.vendorId);
    printf("device id: 0x%x \n", pcieHeaderShadow.type0.deviceId);
    printf("command: 0x%x \n", pcieHeaderShadow.type0.command.all);
    printf("status: 0x%x \n", pcieHeaderShadow.type0.status.all);
    printf("rev id: 0x%x \n", pcieHeaderShadow.type0.revId);
    printf("class code: 0x%x \n", pcieHeaderShadow.type0.classCode);
    printf("cache line size: 0x%x \n", pcieHeaderShadow.type0.cacheLineSize);
    printf("latency timer: 0x%x \n", pcieHeaderShadow.type0.latencyTimer);
    printf("header type: 0x%x \n", pcieHeaderShadow.type0.headerType);
    printf("bist: 0x%x \n", pcieHeaderShadow.type0.bist);
    printf("bar0: 0x%x \n", pcieHeaderShadow.type0.bar0);
    printf("bar1: 0x%x \n", pcieHeaderShadow.type0.bar1);
    printf("bar2: 0x%x \n", pcieHeaderShadow.type0.bar2);
    printf("bar3: 0x%x \n", pcieHeaderShadow.type0.bar3);
    printf("bar4: 0x%x \n", pcieHeaderShadow.type0.bar4);
    printf("bar5: 0x%x \n", pcieHeaderShadow.type0.bar5);
    printf("card bus cis ptr: 0x%x \n", pcieHeaderShadow.type0.cardBusCisPtr);
    printf("subsys vendor id: 0x%x \n", pcieHeaderShadow.type0.subsysVendorId); 
    printf("subsys device id: 0x%x \n", pcieHeaderShadow.type0.subsysDeviceId);
    printf("expansion rom base addr: 0x%x \n", pcieHeaderShadow.type0.expansionRomBaseAddr);
    printf("cap ptr: 0x%x \n", pcieHeaderShadow.type0.capPtr);
    printf("interrupt line: 0x%x \n", pcieHeaderShadow.type0.interruptLine);
    printf("interrupt pin: 0x%x \n", pcieHeaderShadow.type0.interruptPin);
    printf("min gnt: 0x%x \n", pcieHeaderShadow.type0.minGnt);
    printf("max lat: 0x%x \n", pcieHeaderShadow.type0.maxLat);
}

void demo_nvmControllerMmioSpace()
{
    controllerMmio_c& controllerMmioDriver = controllerMmio_c::getInstance();

    cap_t controllerCapabiltiyShadow = controllerMmioDriver.getControllerCapabilities(g_uioId);

    printf("controller capabilities:\n");
    printf("maximum queue entries supported: 0x%x \n", controllerCapabiltiyShadow.maximumQueueEntriesSupported);
    printf("contiguous queues required: 0x%x \n", controllerCapabiltiyShadow.contiguousQueuesRequired);
    printf("arbitration mechanism supported: 0x%x \n", controllerCapabiltiyShadow.arbitrationMechanismSupported);
    printf("timeout: 0x%x \n", controllerCapabiltiyShadow.timeout);
    printf("doorbell stride: 0x%x \n", controllerCapabiltiyShadow.doorbellStride);
    printf("NVM subsystem reset supported: 0x%x \n", controllerCapabiltiyShadow.nvmSubsystemResetSupported);
    printf("command sets supported: 0x%x \n", controllerCapabiltiyShadow.commandSetsSupported);
    printf("boot partition support: 0x%x \n", controllerCapabiltiyShadow.bootPartitionSupport);
    printf("controller power scope: 0x%x \n", controllerCapabiltiyShadow.controllerPowerScope);
    printf("memory page size minimum: 0x%x \n", controllerCapabiltiyShadow.memoryPageSizeMinimum);
    printf("memory page size maximum: 0x%x \n", controllerCapabiltiyShadow.memoryPageSizeMaximum);
    printf("persistent memory region supported: 0x%x \n", controllerCapabiltiyShadow.persistentMemoryRegionSupported);
    printf("controller memory buffer supported: 0x%x \n", controllerCapabiltiyShadow.controllerMemoryBufferSupported);
    printf("NVM subsystem shutdown supported: 0x%x \n", controllerCapabiltiyShadow.nvmSubsystemShutdownSupported);
    printf("controller ready modes supported: 0x%x \n", controllerCapabiltiyShadow.controllerReadyModesSupported);
    printf("NVM subsystem shutdown enhancements supported: 0x%x \n", controllerCapabiltiyShadow.nvmSubsystemShutdownEnhancementsSupported);

}

void demo_nvmeEnumeration()
{
    pcieCfgSpace_c& pcieDrv = pcieCfgSpace_c::getInstance();
    controllerHandle_c& nvmCtrlHandle = controllerHandle_c::getInstance();

    printf("BME status: %d \n", pcieDrv.getBusMasterEnable(g_uioId));
    pcieDrv.setBusMasterEnable(g_uioId, true);
    printf("BME status: %d \n", pcieDrv.getBusMasterEnable(g_uioId));

    nvmCtrlHandle.configureAdminQueue();
    nvmCtrlHandle.enableController();
    while (!nvmCtrlHandle.isControllerReady())
    {
        printf("Waiting for controller to be ready...\n");
    }
    nvmCtrlHandle.issueIdentifyCommand();

    udma_c& udmaDriver = udma_c::getInstance();
    udmaDriver.dumpUdmaBufferContent(0, 0, 4096, 16);
    udmaDriver.dumpUdmaBufferContent(1, 0, 4096, 16);
    udmaDriver.dumpUdmaBufferContent(2, 0, 4096, 16);
}