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

#include "controllerHandle.h"
#include "controllerMmio.h"
#include "udma.h"   
#include "regAccess.h"

extern int g_uioId;

controllerHandle_c::controllerHandle_c()
{
    udma_c& udmaDrv = udma_c::getInstance();
    mAdminSubmissionQueueBaseAddress = udmaDrv.getBufferPhysicalAddress(0);
    mAdminCompletionQueueBaseAddress = udmaDrv.getBufferPhysicalAddress(1);
    mAdminDataBaseAddress = udmaDrv.getBufferPhysicalAddress(2);
    mAdminQueueSize = 128;
    mCommandId = 0;
}

controllerHandle_c::~controllerHandle_c()    
{	
}

controllerHandle_c& controllerHandle_c::getInstance()
{
    static controllerHandle_c mInstance;
    return mInstance;
}

void controllerHandle_c::configureAdminQueue()
{    
    aqa_t aqaShadowReg;
    acq_t acqShadowReg;
    asq_t asqShadowReg;

    aqaShadowReg.adminSubmissionQueueSize = mAdminQueueSize;
    aqaShadowReg.adminCompletionQueueSize = mAdminQueueSize;
    acqShadowReg.adminCompletionQueueBase = mAdminCompletionQueueBaseAddress;
    asqShadowReg.adminSubmissionQueueBase = mAdminSubmissionQueueBaseAddress;

    controllerMmio_c& nvmeControllerDrv = controllerMmio_c::getInstance();

    nvmeControllerDrv.setAdminQueueAttributes(g_uioId, aqaShadowReg);
    nvmeControllerDrv.setAdminCompletionQueueBaseAddress(g_uioId, acqShadowReg);
    nvmeControllerDrv.setAdminSubmissionQueueBaseAddress(g_uioId, asqShadowReg); 
}

void controllerHandle_c::enableController()
{
    controllerMmio_c& nvmeControllerDrv = controllerMmio_c::getInstance();
    cc_t shadowReg = nvmeControllerDrv.getControllerConfiguration(g_uioId);
    shadowReg.enable = 1;
    nvmeControllerDrv.setControllerConfiguration(g_uioId, shadowReg);
}

bool controllerHandle_c::isControllerReady()
{
    controllerMmio_c& nvmeControllerDrv = controllerMmio_c::getInstance();
    csts_t statusReg = nvmeControllerDrv.getControllerStatus(g_uioId);
    return (statusReg.ready == 1);
}

void controllerHandle_c::issueIdentifyCommand()
{
    identifyCommand_t nvmCommand = {};
    nvmCommand.common.opcode = NVME_COMMAND_ADMIN_IDENTIFY;
    nvmCommand.common.commandIdentifier = mCommandId++;
    nvmCommand.common.dataPointer.prpEntries.prpEntry1 = mAdminDataBaseAddress;

    controllerMmio_c& nvmeControllerDrv = controllerMmio_c::getInstance();
    uint16_t sqTailDoorbell = nvmeControllerDrv.getSqTailDoorbell(g_uioId, ADMIN_QUEUE_ID);

    uint64_t destAddress = mAdminSubmissionQueueBaseAddress + (sqTailDoorbell * sizeof(nvmeCommand_t));

    regWrite64Bit(destAddress, *(uint64_t*)&nvmCommand);

    nvmeControllerDrv.incrementSqTailDoorbell(g_uioId, ADMIN_QUEUE_ID);
}
