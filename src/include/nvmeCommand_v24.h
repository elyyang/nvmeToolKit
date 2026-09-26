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

#include <stdint.h>

#ifndef __cplusplus
    #if !defined(static_assert)
        #define static_assert _Static_assert
    #endif
#endif // __cplusplus

/********************************************************************
* NVME 2.4 - NVMe Command
********************************************************************/

#define NVME_COMMAND_DWORDS_COUNT           (16)
#define NVME_COMMAND_BYTE_SIZE              (NVME_COMMAND_DWORDS_COUNT * 4)

typedef uint64_t prpEntry_t;

typedef uint64_t slba_t;

typedef union __attribute__((packed, aligned(4)))
{
    struct
    {                
        uint64_t address;
        uint32_t length;
        uint32_t reserved0      :24;
        uint32_t sglSubType     :4;
        uint32_t sglType        :4;                
    }
    datablock;    
          
    struct
    {
        uint64_t reserved0;
        uint32_t length;
        uint32_t reserved1      :24;
        uint32_t sglSubType     :4;
        uint32_t sglType        :4;
    }
    bitbucket;

    struct
    {
        uint64_t address;
        uint32_t length;
        uint32_t reserved0      :24;
        uint32_t sglSubType     :4;
        uint32_t sglType        :4;
    }
    segment;

    struct
    {
        uint64_t address;
        uint32_t length;
        uint32_t reserved0      :24;
        uint32_t sglSubType     :4;
        uint32_t sglType        :4;
    }
    lastSegment;

    struct
    {
        uint64_t address        :64;
        uint64_t length         :24;
        uint64_t key            :32;
        uint64_t sglSubType     :4;
        uint64_t sglType        :4;
    }
    keyedDatablock;
   
    struct
    {
        uint64_t reserved0;                
        uint32_t length;
        uint32_t reserved1      :24;                
        uint32_t sglSubType     :4;
        uint32_t sglType        :4;
    }
    transportDatablock;
        
    struct
    {
        uint64_t address;
        uint32_t length;
        uint32_t reserved0      :24;
        uint32_t sglSubType     :4;
        uint32_t sglType        :4;
    }
    sglIdentifier;
}
sglDescriptor_t;

typedef union __attribute__((packed, aligned(4)))
{
    struct
    {
        prpEntry_t prpEntry1; 
        prpEntry_t prpEntry2; 
    }
    prpEntries;

    sglDescriptor_t sglEntry; 
}
dataPointer_t;

typedef struct __attribute__((packed, aligned(4)))
{
    //dw0 bytes 0-3
    uint32_t opcode             : 8;        
    uint32_t fuseOperation      : 2;        
    uint32_t _reserved_0        : 4;        
    uint32_t prpSglDataTransfer : 2;
    uint32_t commandIdentifier  : 16;

    //dw1 bytes 4-7                        
    uint32_t namespaceIdentifier;

    //dw2 bytes 8-11
    uint32_t commonDword2;

    //dw3 bytes 12-15
    uint32_t commonDword3;

    //dw4-5 bytes 16-23
    uint64_t metadataPointer;

    //dw6-9 bytes 24-39        
    dataPointer_t dataPointer;    
}
nvmeCommandCommon_t;

typedef enum
{
    NVME_COMMAND_ADMIN_DELETE_SQ = 0x00,
    NVME_COMMAND_ADMIN_CREATE_SQ = 0x01,
    NVME_COMMAND_ADMIN_GET_LOG_PAGE = 0x02,
    NVME_COMMAND_ADMIN_DELETE_CQ = 0x04,
    NVME_COMMAND_ADMIN_CREATE_CQ = 0x05,
    NVME_COMMAND_ADMIN_IDENTIFY = 0x06,
    NVME_COMMAND_ADMIN_ABORT = 0x08,
    NVME_COMMAND_ADMIN_SET_FEATURES = 0x09,
    NVME_COMMAND_ADMIN_GET_FEATURES = 0x0A,
    NVME_COMMAND_ADMIN_ASYNCHRONOUS_EVENT_REQUEST = 0x0C,
    NVME_COMMAND_ADMIN_NAMESPACE_MANAGEMENT = 0x0D,
    NVME_COMMAND_ADMIN_FIRMWARE_COMMIT = 0x10,
    NVME_COMMAND_ADMIN_FIRMWARE_IMAGE_DOWNLOAD = 0x11,
    NVME_COMMAND_ADMIN_DEVICE_SELF_TEST = 0x14,
    NVME_COMMAND_ADMIN_NAMESPACE_ATTACHMENT = 0x15,
    NVME_COMMAND_ADMIN_KEEP_ALIVE = 0x18,
    NVME_COMMAND_ADMIN_DIRECTIVE_SEND = 0x19,
    NVME_COMMAND_ADMIN_DIRECTIVE_RECEIVE = 0x1A,
    NVME_COMMAND_ADMIN_VIRTUALIZATION_MANAGEMENT = 0x1C,
    NVME_COMMAND_ADMIN_NVME_MI_SEND = 0x1D,
    NVME_COMMAND_ADMIN_NVME_MI_RECEIVE = 0x1E,
    NVME_COMMAND_ADMIN_CAPACITY_MANAGEMENT = 0x20,
    NVME_COMMAND_ADMIN_DISCOVERY_INFORMATION_MANAGEMENT = 0x21,
    NVME_COMMAND_ADMIN_FABRIC_ZONING_RECEIVE = 0x22,
    NVME_COMMAND_ADMIN_LOCKDOWN = 0x24,
    NVME_COMMAND_ADMIN_FABRIC_ZONING_LOOKUP = 0x25,
    NVME_COMMAND_ADMIN_CLEAR_EXPORT_NVM_RESOURCE_CFG = 0x28,
    NVME_COMMAND_ADMIN_FABRIC_ZONING_SEND = 0x29,
    NVME_COMMAND_ADMIN_MANAGE_EXPORTED_NVM_SUBSYS_RECEIVE = 0x2A,
    NVME_COMMAND_ADMIN_MANAGE_EXPORTED_NVM_SUBSYS_SEND = 0x2D,
    NVME_COMMAND_ADMIN_MANAGE_EXPORTED_NAMESPACE = 0x31,   
    NVME_COMMAND_ADMIN_MANAGE_EXPORTED_PORT = 0x35,
    NVME_COMMAND_ADMIN_CROSS_CONTROLLER_RESET = 0x38,
    NVME_COMMAND_ADMIN_SEND_DISCOVERY_LOG_PAGE = 0x39,
    NVME_COMMAND_ADMIN_TRACK_SEND = 0x3D,
    NVME_COMMAND_ADMIN_TRACK_RECEIVE = 0x3E,
    NVME_COMMAND_ADMIN_MIGRATION_SEND = 0x41,
    NVME_COMMAND_ADMIN_MIGRATION_RECEIVE = 0x42,
    NVME_COMMAND_ADMIN_CONTROLLER_DATA_QUEUE = 0x45,
    NVME_COMMAND_ADMIN_DOORBELL_BUFFER_CONFIG = 0x7C,
    NVME_COMMAND_ADMIN_FABRICS_COMMANDS = 0x7F,
    NVME_COMMAND_ADMIN_FORMAT_NVM = 0x80,
    NVME_COMMAND_ADMIN_SECURITY_SEND = 0x81,
    NVME_COMMAND_ADMIN_SECURITY_RECEIVE = 0x82,
    NVME_COMMAND_ADMIN_SANITIZE = 0x84,
    NVME_COMMAND_ADMIN_LOAD_PROGRAM = 0x85,
    NVME_COMMAND_ADMIN_GET_LBA_STATUS = 0x86,
    NVME_COMMAND_ADMIN_PROGRAM_ACTIVATION_MANAGEMENT = 0x88,
    NVME_COMMAND_ADMIN_MEMORY_RANGE_SET_MANAGEMENT = 0x89,
    NVME_COMMAND_ADMIN_SANITIZE_NAMESPACE = 0x8C,
    NVME_COMMAND_ADMIN_VENDOR_SPECIFIC0 = 0xC0,
    NVME_COMMAND_ADMIN_VENDOR_SPECIFIC1 = 0xFF
} 
nvmeAdminOpcode_e;

typedef enum
{
    NVME_COMMAND_IO_FLUSH = 0x0,
    NVME_COMMAND_IO_WRITE = 0x1,
    NVME_COMMAND_IO_READ = 0x2,
    NVME_COMMAND_IO_WRITE_UNCORRECTABLE = 0x4,
    NVME_COMMAND_IO_COMPARE = 0x5,
    NVME_COMMAND_IO_WRITE_ZEROES = 0x8,
    NVME_COMMAND_IO_DATASET_MANAGEMENT = 0x9,
    NVME_COMMAND_IO_VERIFY = 0xC,
    NVME_COMMAND_IO_RESERVATION_REGISTER = 0xD,
    NVME_COMMAND_IO_RESERVATION_REPORT = 0xE,
    NVME_COMMAND_IO_RESERVATION_ACQUIRE = 0x11,
    NVME_COMMAND_IO_MANAGEMENT_RECEIVE = 0x12,
    NVME_COMMAND_IO_RESERVATION_RELEASE = 0x15,
    NVME_COMMAND_IO_CANCEL = 0x18,
    NVME_COMMAND_IO_COPY = 0x19,    
    NVME_COMMAND_IO_MANAGEMENT_SEND = 0x1D,
    NVME_COMMAND_IO_FABRIC_COMMANDS = 0x7F,
    NVME_COMMAND_IO_VENDOR_SPECIFIC0 = 0x80,
    NVME_COMMAND_IO_VENDOR_SPECIFIC1 = 0xFF
} 
nvmeIoOpcode_e;

/********************************************************************
* NVMe admin command set
*********************************************************************/

typedef struct __attribute__((packed, aligned(4)))
{
    //dw0-9 bytes 0-39
    nvmeCommandCommon_t common;

    //dw10 bytes 40-43
    uint32_t queueIdentifier        : 16;               
    uint32_t queueSize              : 16;

    //dw11 bytes 44-47
    uint32_t physicallyContiguous   : 1;    
    uint32_t interruptsEnabled      : 1;    
    uint32_t _reserved_0            : 14;   
    uint32_t interruptVector        : 16;

    //dw12 bytes 48-51
    uint32_t dword12;

    //dw13 bytes 52-55
    uint32_t dword13;

    //dw14 bytes 56-59
    uint32_t dword14;                   

    //dw15 bytes 60-63
    uint32_t dword15;
}
createIoCompletionQueueCommand_t;

typedef struct __attribute__((packed, aligned(4)))
{
    //dw0-9 bytes 0-39
    nvmeCommandCommon_t common;

    //dw10 bytes 40-43    
    uint32_t queueIdentifier        : 16;               
    uint32_t queueSize              : 16;      
    
    //dw11 bytes 44-47
    uint32_t physicallyContiguous   : 1;      
    uint32_t queuePriority          : 2;
    uint32_t _reserved_0            : 13;     
    uint32_t completionQueueId      : 16;

    //dw12 bytes 48-51
    uint32_t nvmeSetIdentifier      : 16;
    uint32_t _reserved_1            : 16;

    //dw13 bytes 52-55
    uint32_t dword13;                   

    //dw14 bytes 56-59
    uint32_t dword14; 
    
    //dw15 bytes 60-63
    uint32_t dword15;
}
createIoSubmissionQueueCommand_t;

typedef struct __attribute__((packed, aligned(4)))
{
    //dw0-9 bytes 0-39
    nvmeCommandCommon_t common;
    
    //dw10 bytes 40-43
    uint32_t controllerOrNamespaceStructure : 8;
    uint32_t _reserved_0                    : 8;  
    uint32_t controllerIdentifier           : 16;
    
    //dw11 bytes 44-47
    uint32_t cnsSpecificIdentifier          : 16;
    uint32_t _reserved_1                    : 8;
    uint32_t commandSetIdentifier          : 8;
    
    //dw12 bytes 48-51
    uint32_t dword12;    
    
    //dw13 bytes 52-55
    uint32_t dword13;
    
    //dw14 bytes 56-59                                               
    uint32_t uuidIndex                      : 7;
    uint32_t _reserved_2                    : 25;
    
    //dw15 bytes 60-63
    uint32_t dword15;                                               
}
identifyCommand_t;

/********************************************************************
* NVMe io command set
*********************************************************************/

typedef struct __attribute__((packed, aligned(4)))
{
    //dw0-9
    nvmeCommandCommon_t common;
    
    //dw10-11                                  
    slba_t startingLba;
    
    //dw12                                                
    uint32_t numOfLogicalBlocks     : 16;    
    uint32_t commandExtensionType   : 4;
    uint32_t _reserved_0            : 4;
    uint32_t storageTagCheck        : 1;
    uint32_t _reserved_1            : 1;   
    uint32_t protectionInformation  : 4;    
    uint32_t forceUnitAccess        : 1;    
    uint32_t limitedRetry           : 1;

    //dw13    
    union 
    {
        struct
        {
            uint32_t datasetManagementAccessFrequency   : 4;    
            uint32_t datasetManagementAccessLatency     : 2;
            uint32_t datasetManagementSequentialRequest : 1;    
            uint32_t datasetManagementIncompressible    : 1;    
            uint32_t _reserved_2                        : 24;
        };

        struct
        {
            uint32_t commandExtensionValue  : 16;
            uint32_t _reserved_3            : 16;            
        };
    };

    //dw14
    uint32_t expectedLogicalBlockTagsLower;

    //dw15   
    uint32_t expectedLogicalBlockApplicationTag     : 16;                
    uint32_t expectedLogicalBlockApplicationTagMask : 16;            
}
readCommand_t;

typedef struct __attribute__((packed, aligned(4)))
{
    //dw0-9
    nvmeCommandCommon_t common;

    //dw10-11                                  
    slba_t startingLba;

    //dw12                                                
    uint32_t numOfLogicalBlocks     : 16;    
    uint32_t commandExtensionType   : 4;    
    uint32_t directiveType          : 4;
    uint32_t storageTagCheck        : 1;
    uint32_t _reserved_0            : 1;   
    uint32_t protectionInformation  : 4;    
    uint32_t forceUnitAccess        : 1;    
    uint32_t limitedRetry           : 1;

    //dw13    
    union 
    {
        struct
        {
            uint16_t datasetManagementAccessFrequency   : 4;    // accessFrequency_e values
            uint16_t datasetManagementAccessLatency     : 2;    // accessLatency_e values
            uint16_t datasetManagementSequentialRequest : 1;    
            uint16_t datasetManagementIncompressible    : 1;
            uint16_t _reserved_1                        : 8;                
        };

        uint16_t commandExtenstionValue;
    };
    uint16_t directiveSpecific;

    //dw14
    uint32_t logicalBlockTagsLower;
    
    //dw15   
    uint32_t logicalBlockApplicationTag         : 16;                
    uint32_t logicalBlockApplicationTagMask     : 16;
}
writeCommand_t;

/********************************************************************
* NVMe command set
*********************************************************************/

typedef union __attribute__((packed, aligned (4))) nvmeCommand_t
{
    uint32_t dword[16];
    
    createIoCompletionQueueCommand_t createIoCompletionQueueCommand;
    createIoSubmissionQueueCommand_t createIoSubmissionQueueCommand;
    identifyCommand_t identifyCommand;

    readCommand_t readCommand;
    writeCommand_t writeCommand;   
}
nvmeCommand_t;
static_assert(sizeof(nvmeCommand_t) == NVME_COMMAND_BYTE_SIZE, "NVMe command is not 16 dwords (64 Byte)");
