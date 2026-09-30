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
* NVM-Express-NVM-Command-Set-Specification-Revision-1.3-Ratified-2026.07.31
* NVM Command Set Identify Namespace Data Structure (CNS 00h)
* section 4.1.5.1 
*********************************************************************/

#define NVME_IDENTIFY_DATA_SIZE_IN_DWORDS    (1024)
#define NVME_IDENTIFY_DATA_SIZE              (NVME_IDENTIFY_DATA_SIZE_IN_DWORDS * 4)

typedef enum nidt_e
{
    NIDT_RESERVED           = 0x0,
    NIDT_IEEE_EXT_UNIQUE_ID = 0x1,
    NIDT_NGUID              = 0x2,
    NIDT_NAMESPACE_UUID     = 0x3        
}nidt_e;

typedef struct nsfeat_t
{
    uint8_t thinProvisioningSupported             : 1;    //bit 0
    uint8_t namespaceSupportedAtomicBoundaryPower : 1;    //bit 1
    uint8_t deallocatedErrorSupported             : 1;    //bit 2
    uint8_t uidReuse                              : 1;    //bit 3
    uint8_t optionalWritePerformance              : 2;    //bits 4-5
    uint8_t multipleAtomicityMode                 : 1;    //bit 6
    uint8_t optionalReadPerformance               : 1;    //bit 7
}nsfeat_t;

typedef struct flbas_t
{
    uint8_t formatIndexLower                  : 4;    //bits 0-3
    uint8_t metadataTransferredAsExtendedLba  : 1;    //bit 4
    uint8_t formatIndexUpper                  : 2;    //bits 5-6
    uint8_t reserved                          : 1;    //bit 7
}flbas_t;

typedef struct mc_t
{
    uint8_t metadataInExtendedLBA               : 1;    //bit  0
    uint8_t metadataInSeparateBuffer            : 1;    //bit  1
    uint8_t reserved                            : 6;    //bits 2-7    
}mc_t;

typedef struct dpc_t
{
    uint8_t protectionInformationType1          : 1;    //bit  0
    uint8_t protectionInformationType2          : 1;    //bit  1
    uint8_t protectionInformationType3          : 1;    //bit  2
    uint8_t protectionInformationFirst8Metadata : 1;    //bit  3
    uint8_t protectionInformationLast8Metadata  : 1;    //bit  4
    uint8_t reserved                            : 3;    //bits 5-7     
}dpc_t;

typedef struct dps_t
{
    uint8_t protectionInformationType           : 3;    //bits 0-2
    uint8_t protectionInformationPosition       : 1;    //bit  3
    uint8_t reserved                            : 4;    //bits 4-7
}dps_t;

typedef struct nmic_t
{
    uint8_t sharedNamespace                     : 1;    //bit  0
    uint8_t dispersedNamespace                  : 1;    //bit  1
    uint8_t reserved                            : 6;    //bits 2-7
}nmic_t;

typedef struct rescap_t
{
    uint8_t persistThroughPowerLoss             : 1;    //bit 0
    uint8_t writeExclusiveReservationType       : 1;    //bit 1
    uint8_t exclusiveAccessReservationType      : 1;    //bit 2
    uint8_t writeExclusiveRegistrantsOnly       : 1;    //bit 3
    uint8_t exclusiveAccessRegistrantsOnly      : 1;    //bit 4
    uint8_t writeExclusiveAllRegistrants        : 1;    //bit 5
    uint8_t exclusiveAccessAllRegistrants       : 1;    //bit 6
    uint8_t ignoreExistingKey                   : 1;    //bit 7
}rescap_t;

typedef struct fpi_t
{
    uint8_t formatProgressIndicator             : 7;    //bits 0-6
    uint8_t formatProgressIndicatorSupport      : 1;    //bit 7
}fpi_t;

typedef struct dlfeat_t
{
    uint8_t deallocatedLogicalBlockReadBehavior : 2;    //bits 0-2
    uint8_t supportDeallocateWriteZero          : 1;    //bit  3
    uint8_t deallocatedPiGuardCrc               : 1;    //bit  4
    uint8_t reserved                            : 3;    //bits 5-7
}dlfeat_t;

typedef struct nsattr_t
{
    uint8_t writeProtected                      : 1;    //bit  0
    uint8_t reserved                            : 7;    //bits 1-7
}nsattr_t;

typedef struct nguid_t
{
    uint64_t vendorSpecificExtensionId;                 //byte 104-111 NGUID vendor specific extension id
    uint64_t oui                                : 24;   //byte 112-114 NGUID OUI
    uint64_t extensionId                        : 40;   //byte 115-119 NGUID extension id
}nguid_t;    

typedef struct lbaFormat_t
{
    uint32_t metaDataSize                       : 16;  //bit 15:00
    uint32_t lbaDataSize                        : 8;   //bit 23:16
    uint32_t relativePerformance                : 2;   //bit 25:24
    uint32_t reserved                           : 6;   //bit 32:26
}lbaFormat_t;

typedef struct kpios_t
{
    uint8_t keyPerIoEnabledInNamespace          : 1;    //bit  0
    uint8_t keyPerIoSupportedInNamespace        : 1;    //bit  1
    uint8_t reserved                            : 6;    //bits 2-7
}kpios_t;

typedef union __attribute__((packed, aligned (4))) identifyNamespace_t
{
    uint32_t mDword[NVME_IDENTIFY_DATA_SIZE_IN_DWORDS];

    struct
    {    
        uint64_t    namespaceSize;                                      //NSZE;                    //byte(s) 0-7     (host specified)
        uint64_t    namespaceCapacity;                                  //NCAP;                    //byte(s) 8-15    (host specified)
        uint64_t    namespaceUtilization;                               //NUSE;                    //byte(s) 16-23
        nsfeat_t    namespaceFeatures;                                  //NSFEAT;                  //byte(s) 24    
        uint32_t    numberOfLBAFormats                          :8;     //NLBAF                    //byte(s) 25
        flbas_t     formattedLbaSize;                                   //FLBAS;                   //byte(s) 26      (host specified)
        mc_t        metadataCapabilities;                               //MC;                      //byte(s) 27 
        dpc_t       endToEndProtectionCapabilities;                     //DPC;                     //byte(s) 28 
        dps_t       dataProtectionTypeSettings;                         //DPS;
        nmic_t      namespaceMultipathIoSharingCapabilities;            //NMIC;                    //byte(s) 30      (host specified)        
        rescap_t    reservationCapabilities;                            //RESCAP;                  //byte(s) 31
        fpi_t       formatProgressIndicator;                            //FPI;                     //byte(s) 32
        dlfeat_t    deallocateLogicalBlockFeatures;                     //DLFEAT;                  //byte(s) 33
        uint32_t    namespaceAtomicWriteUnitNormal              :16;    //NAWUN                    //byte(s) 34-35
        uint32_t    namespaceAtomicWriteUnitPowerFail           :16;    //NAWUPF                   //byte(s) 36-37
        uint32_t    namespaceAtomicCompareAndWriteUnit          :16;    //NACWU                    //byte(s) 38-39
        uint32_t    namespaceAtomicBoundarySizeNormal           :16;    //NABSN                    //byte(s) 40-41
        uint32_t    namespaceAtomicBoundaryOffset               :16;    //NABO                     //byte(s) 42-43
        uint32_t    namespaceAtomicBoundarySizePowerFail        :16;    //NABSPF                   //byte(s) 44-45  
        uint32_t    namespaceOptimalIoBoundary                  :16;    //NOIOB                    //byte(s) 46-47
        uint64_t    nvmCapacity[2];                                     //NVMCAP[2];               //byte(s) 48-63    
        uint32_t    namespacePreferredWriteGranularity          :16;    //NPWG                     //Byte(s) 64-65    
        uint32_t    namespacePreferredWriteAlignment            :16;    //NPWA                     //Byte(s) 66-67
        uint32_t    namespacePreferredDeallocatedGranularity    :16;    //NPDG                     //Byte(s) 68-69
        uint32_t    namespacePreferredDeallocatedAlignment      :16;    //NPDA                     //Byte(s) 70-71
        uint32_t    namespaceOptimalWriteSize                   :16;    //NOWS                     //Byte(s) 72-73
        uint32_t    maxSingleSourceRangeLength                  :16;    //MSSRL                    //Byte(s) 74-75
        uint32_t    maxCopyLength;                                      //MCL                      //Byte(s) 76-79
        uint32_t    maxSourceRangeCount                         :8;     //MSRC                     //Byte(s) 80
        kpios_t     keyPerIoStatus;                                     //KPIOS                    //Byte(s) 81
        uint32_t    numberOfUniqueAttributeLbaFormats           :8;     //NULBAF                   //Byte(s) 82
        uint32_t    _reserved0                                  :8;                                //Byte(s) 83
        uint32_t    keyPerIoDataAccessAlignmentAndGranularity;          //KPIODAAG                 //Byte(s) 84-87
        uint8_t     _reserved1[4];                                                                 //Byte(s) 88-91
        uint32_t    anaGroupId;                                         //ANAGRPID;                //Byte(s) 92-95
        uint8_t     _reserved2[3];                                                                 //Byte(s) 96-98    
        nsattr_t    namespaceAttributes;                                //NSATTR;                  //Byte(s) 99
        uint32_t    nvmSetIdentifier                            :16;    //NVMSETID                 //Byte(s) 100-101
        uint32_t    enduranceGroupIdentifier                    :16;    //ENGID                    //Byte(s) 102-103    
        nguid_t     namespaceGloballyUniqueId;                          //NGUID;                   //byte(s) 104-119
        uint64_t    ieeeExtendedUniqueIdentifier;                       //EUI64;                   //byte(s) 120-127    
        lbaFormat_t lbaFormat[64];                                      //LBAF[64];                //byte(s) 128-383        
        uint8_t     vendorSpecific[3712];                               //vendorSpecific[3712];    //byte(s) 384-4095
    };        
}identifyNamespace_t;
static_assert(sizeof(identifyNamespace_t) == NVME_IDENTIFY_DATA_SIZE, "identifyNamespace_t incorrect size!");

