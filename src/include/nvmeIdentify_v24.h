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
* NVMe 2.4 Identify
*********************************************************************/

#define NVME_IDENTIFY_DATA_SIZE_IN_DWORDS    (1024)
#define NVME_IDENTIFY_DATA_SIZE              (NVME_IDENTIFY_DATA_SIZE_IN_DWORDS * 4)

typedef enum 
{
    IDENTIFY_NAMESPACE                          = 0x0,
    IDENTIFY_CONTROLLER                         = 0x1,
    ACTIVE_NAMESPACE_ID_LIST                    = 0x2,        
    NAMESPACE_IDENTIFICATION_DESCRIPTOR_LIST    = 0x3,
    NVM_SET_LIST                                = 0x4,
    IO_CMD_SET_SPECIFIC_IDENTIFY_NAMESPACE      = 0x5,
    IO_CMD_SET_SPECIFIC_IDENTIFY_CONTROLLER     = 0x6,
    IO_CMD_SET_SPECIFIC_ACTIVE_NAMESPACE_ID_LIST= 0x7,
    IO_CMD_SET_INDEPENDENT_IDENTIFY_NAMESPACE   = 0x8,
    ALLOCATED_NAMESPACE_ID_LIST                 = 0x10,
    ALLOCATED_IDENTIFY_NAMESPACE                = 0x11,
    ATTACHED_CONTROLLER_LIST                    = 0x12,
    NVM_SUBSYSTEM_CONTROLLER_LIST               = 0x13,
    PRIMARY_CONTROLLER_CAPABILITIES             = 0x14,
    SECONDARY_CONTROLLER_LIST                   = 0x15,
    NAMESPACE_GRANULARITY_LIST                  = 0x16,
    UUID_LIST                                   = 0x17,
}identifyCns_e;

typedef struct cmic_t
{
    uint8_t     multiplePorts                               : 1;    //bit  0
    uint8_t     multipleControllers                         : 1;    //bit  1
    uint8_t     functionType                                : 1;    //bit  2
    uint8_t     asymmetricNamespaceAccessReportingSupport   : 1;    //bit  3
    uint8_t     _reserved                                   : 4;    //bits 4-7
}cmic_t;    

typedef struct oaes_t
{
    uint32_t    _reserved0                                  : 8;    //bits  0-7     
    uint32_t    attachedNamespaceAttributeNotices           : 1;    //bit   8       
    uint32_t    firmwareActivationNotices                   : 1;    //bit   9       
    uint32_t    _reserved1                                  : 1;    //bit   10
    uint32_t    asymmetricNamespaceAccessChangeNotices      : 1;    //bit   11
    uint32_t    predictableLatencyEventAggrLogChangeNotices : 1;    //bit   12
    uint32_t    lbaStatusInfoAlertNotices                   : 1;    //bit   13
    uint32_t    enduranceGroupEventAggrLogPageChangeNotices : 1;    //bit   14    
    uint32_t    normalNvmSubsystemShutdown                  : 1;    //bit   15
    uint32_t    temperatureThresholdHysteresisRecovery      : 1;    //bit   16
    uint32_t    reachabilityGroupsChangeNoticesSupport      : 1;    //bit   17
    uint32_t    _reserved2                                  : 1;     //bit   18
    uint32_t    allocatedNamespaceAttributeNotices          : 1;    //bit   19
    uint32_t    crossControllerResetCompletedNotices        : 1;    //bit   20
    uint32_t    lostHostCommunicationNotices                : 1;    //bit   21
    uint32_t    rateLimitingConfigurationChange             : 1;    //bit   22
    uint32_t    _reserved3                                  : 4;    //bits  23-26
    uint32_t    zoneDescriptorChangedNotice                 : 1;    //bit   27
    uint32_t    _reserved4                                  : 3;    //bits  28-30
    uint32_t    discoveryLogPageChangeNotification          : 1;    //bit   31    
}oaes_t;

typedef struct ctratt_t
{
    uint32_t    support128bitHostIdentifier                 : 1;    //bit   0       
    uint32_t    supportNonOpPowerStatePermissiveMode        : 1;    //bit   1      
    uint32_t    supportNvmeSets                             : 1;    //bit   2
    uint32_t    supportReadRecoveryLevels                   : 1;    //bit   3
    uint32_t    supportEnduranceGroups                      : 1;    //bit   4
    uint32_t    supportPredictableLatencyMode               : 1;    //bit   5
    uint32_t    supportTrafficBasedKeepAliveSupport         : 1;    //bit   6
    uint32_t    supportNamespaceGranularity                 : 1;    //bit   7
    uint32_t    supportSqAssociations                       : 1;    //bit   8
    uint32_t    supportUUIDList                             : 1;    //bit   9    
    uint32_t    reserved                                    :22;    //bits  10-31
}ctratt_t;

typedef struct rrls_t
{
    uint8_t     readRecoveryLevel0                          : 1;    //bit   0
    uint8_t     readRecoveryLevel1                          : 1;    //bit   1
    uint8_t     readRecoveryLevel2                          : 1;    //bit   2
    uint8_t     readRecoveryLevel3                          : 1;    //bit   3
    uint8_t     readRecoveryLevel4                          : 1;    //bit   4
    uint8_t     readRecoveryLevel5                          : 1;    //bit   5
    uint8_t     readRecoveryLevel6                          : 1;    //bit   6
    uint8_t     readRecoveryLevel7                          : 1;    //bit   7
    uint8_t     readRecoveryLevel8                          : 1;    //bit   8
    uint8_t     readRecoveryLevel9                          : 1;    //bit   9
    uint8_t     readRecoveryLevel10                         : 1;    //bit   10
    uint8_t     readRecoveryLevel11                         : 1;    //bit   11
    uint8_t     readRecoveryLevel12                         : 1;    //bit   12
    uint8_t     readRecoveryLevel13                         : 1;    //bit   13
    uint8_t     readRecoveryLevel14                         : 1;    //bit   14
    uint8_t     readRecoveryLevel15                         : 1;    //bit   15
}rrls_t;
    
typedef struct bpcap_t
{
    uint8_t     rpmbBootPartitionWriteProtectionSupport        : 2;    //bits 0-1
    uint8_t     setFeaturesBootPartitionWriteProtectionSupport : 1;    //bit  2
    uint8_t     _reserved                                      : 5;    //bits 3-7
}bpcap_t;

typedef struct chsi_t
{
    uint8_t     cxlHdmSupport                                  : 1;    //bit  0
    uint8_t     _reserved                                      : 7;    //bits 1-7
}chsi_t;

typedef struct plsi_t
{
    uint8_t     plsEmergencyPowerFail                          : 1;    //bit  0
    uint8_t     plsForcedQuiescence                            : 1;    //bit  1
    uint8_t     _reserved                                      : 6;    //bits 2-7
}plsi_t;

typedef struct crcap_t
{
    uint8_t     reachabilityReportingSupported                 : 1;    //bit  0
    uint8_t     reachabilityGroupIdChangeable                  : 1;    //bit  1
    uint8_t     _reserved                                      : 6;    //bits 2-7
}crcap_t;

typedef struct nvmsr_t
{
    uint8_t     nvmeStorageDevice                              : 1;    //bit  0
    uint8_t     nvmeEnclosure                                  : 1;    //bit  1
    uint8_t     _reserved                                      : 6;    //bits 2-7
}nvmsr_t;

typedef struct vwci_t
{
    uint8_t     vpdWriteCyclesRemaining                       : 7;    //bits 0-6
    uint8_t     vpdWriteCyclesRemainingValid                  : 1;    //bit  7
}vwci_t;

typedef struct mec_t
{
    uint8_t     twoWirePortManagementEndpoint                 : 1;    //bit  0
    uint8_t     pciePortManagementEndpoint                    : 1;    //bit  1
    uint8_t     _reserved                                     : 6;    //bits 2-7
}mec_t;

typedef struct oacs_t
{
    uint16_t    securitySendReceiveSupported                        : 1;    //bit  0
    uint16_t    formatNvmSupported                                  : 1;    //bit  1
    uint16_t    firmwareDownloadSupported                           : 1;    //bit  2
    uint16_t    namespaceManagementSupported                        : 1;    //bit  3
    uint16_t    deviceSelfTestSupported                             : 1;    //bit  4
    uint16_t    directivesSupported                                 : 1;    //bit  5
    uint16_t    nvmeMiSendReceiveSupported                          : 1;    //bit  6
    uint16_t    virtualizationManagementSupported                   : 1;    //bit  7
    uint16_t    doorbellBufferConfigSupported                       : 1;    //bit  8
    uint16_t    getLbaStatusSupported                               : 1;    //bit  9
    uint16_t    commandAndFeatureLockdownSupported                  : 1;    //bit 10
    uint16_t    hostManagedLiveMigrationSupported                   : 1;    //bit 11
    uint16_t    exportedNvmSubsystemSupported                       : 1;    //bit 12
    uint16_t    controllerScopedCommandAndFeatureLockdownSupported  : 1;    //bit 13
    uint16_t    _reserved                                           : 2;    //bits 14-15
}oacs_t;

typedef struct frmw_t
{
    uint8_t     firstFirmwareSlotReadOnly                      : 1;    //bit  0
    uint8_t     numberOfFirmwareSlots                          : 3;    //bits 1-3
    uint8_t     firmwareActivationWithoutReset                 : 1;    //bit  4
    uint8_t     supportMultipleUpdateDetection                 : 1;    //bit  5
    uint8_t     _reserved                                      : 2;    //bits 6-7
}frmw_t;

typedef struct lpa_t
{
    uint8_t     smartSupport                                   : 1;    //bit  0
    uint8_t     commandsSupportedAndEffectsSupport             : 1;    //bit  1
    uint8_t     logPageExtendedDataSupport                     : 1;    //bit  2
    uint8_t     telemetrySupport                               : 1;    //bit  3
    uint8_t     persistentEventSupport                         : 1;    //bit  4
    uint8_t     miscellaneousLogPageSupport                    : 1;    //bit  5
    uint8_t     dataArea4Support                               : 1;    //bit  6
    uint8_t     _reserved                                      : 1;    //bit  7
}lpa_t;

typedef struct avscc_t
{
    uint8_t     vendorSpecificCommandFormat                 : 1;    //bit  0
    uint8_t     reserved                                    : 7;    //bits 1-7
}avscc_t;

typedef struct apsta_t
{
    uint8_t     autonomousPowerStateTransitionAttributes    : 1;    //bit  0
    uint8_t     reserved                                    : 7;    //bits 1-7   
}apsta_t;

typedef struct rpmbs_t
{
    uint32_t    numberOfRpmbUnits                           : 3;    //bits 0-2
    uint32_t    authenticationMethod                        : 3;    //bits 3-5
    uint32_t    reserved                                    : 10;   //bits 6-15
    uint32_t    totalSize                                   : 8;    //bits 16-23
    uint32_t    accessSize                                  : 8;    //bits 24-31
}rpmbs_t;

typedef struct dsto_t
{
    uint8_t     singleDeviceSelfTestOperation                  : 1;    //bit  0
    uint8_t     hostInitiatedRefreshSupport                   : 1;    //bit  1
    uint8_t     _reserved                                      : 6;    //bits 2-7
}dsto_t;

typedef struct hctma_t
{
    uint16_t    hostControlledThermalManagementSupport         : 1;    //bit  0
    uint16_t    _reserved                                      :15;    //bits 1-15
}hctma_t;

typedef struct sanicap_t
{
    uint32_t    cryptoEraseSupport                          : 1;    //bit 0
    uint32_t    blockEraseSupport                           : 1;    //bit 1
    uint32_t    overWriteSupport                            : 1;    //bit 2
    uint32_t    verificationSupport                            : 1;    //bit 3
    uint32_t    namespaceVerificationSupport                   : 1;    //bit 4
    uint32_t    sanitizePurgeRequestAndReportingSupported      : 1;    //bit 5
    uint32_t    reserved                                    : 23;   //bits 6-28
    uint32_t    noDeallocateInhibited                       : 1;    //bit 29
    uint32_t    noDeallocateModifiesMediaAfterSanitize      : 2;    //bits 30-31
}sanicap_t;

typedef struct anacap_t
{
    uint8_t     reportAnaOptimizedState                      : 1;    //bit  0
    uint8_t     reportAnaNonOptimizedState                   : 1;    //bit  1
    uint8_t     reportAnaInaccessibleState                   : 1;    //bit  2
    uint8_t     reportAnaPersistentLossState                 : 1;    //bit  3
    uint8_t     reportAnaChangeState                         : 1;    //bit  4
    uint8_t     _reserved                                    : 1;    //bit  5
    uint8_t     anaGroupIdLockedWhenAttachedSupport          : 1;    //bit  6
    uint8_t     anaGroupIdSupport                            : 1;    //bit  7
}anacap_t;

typedef struct kpioc_t
{
    uint8_t     keyPerIoSupported                             : 1;    //bit  0
    uint8_t     keyPerIoScope                                 : 1;    //bit  1
    uint8_t     _reserved                                     : 6;    //bits 2-7
}kpioc_t;

typedef struct rmdca_t
{
    uint16_t    restoreDefaultNvmSubsystemConfigurationSupported        : 1;    //bit  0
    uint16_t    restoreDefaultNamespaceConfigurationSupported           : 1;    //bit  1
    uint16_t    restoreDefaultCapacityManagementConfigurationSupported  : 1;    //bit  2
    uint16_t    _reserved                                               : 13;   //bits 3-15
}rmdca_t;

typedef struct tmpthha_t
{
    uint8_t     temperatureThresholdMaximumHysteresis        : 3;    //bits 0-2
    uint8_t     _reserved                                    : 5;    //bits 3-7
}tmpthha_t;

typedef struct mupa_t
{
    uint8_t     maximumUnlimitedPowerScale                   : 2;    //bits 0-1
    uint8_t     _reserved                                    : 6;    //bits 2-7
}mupa_t;

typedef struct cdpa_t
{
    uint16_t    hmacSha384Supported                          : 1;    //bit  0
    uint16_t    _reserved0                                   : 7;    //bits 1-7
    uint16_t    _reserved1                                   : 8;    //bits 8-15
}cdpa_t;

typedef struct ipmsr_t
{
    uint8_t     sampleRateValue;                              //bits 0-7
    uint8_t     sampleRateScale;                              //bits 8-15
}ipmsr_t;

typedef struct ensa_t
{
    uint8_t     exportedNvmSubsystemTemplateSupport          : 1;    //bit  0
    uint8_t     exportedNvmSubsystemMigrationSupport         : 1;    //bit  1
    uint8_t     _reserved                                    : 6;    //bits 2-7
}ensa_t;

typedef struct endsfs_t
{
    uint8_t     exportedNamespaceFormat0                     : 1;    //bit  0
    uint8_t     exportedNamespaceFormat1                     : 1;    //bit  1
    uint8_t     _reserved                                    : 6;    //bits 2-7
}endsfs_t;

typedef struct sqes_t
{
    uint8_t     minimumIoSubmissionQueueEntrySize           : 4;    //bits 0-3
    uint8_t     maximumIoSubmissionQueueEntrySize           : 4;    //bits 4-7    
}sqes_t;

typedef struct cqes_t
{    
    uint8_t     minimumIoCompletionQueueEntrySize           : 4;    //bits 0-3
    uint8_t     maximumIoCompletionQueueEntrySize           : 4;    //bits 4-7  
}cqes_t;

typedef struct oncs_t
{
    uint16_t    compareCommandSupport                       : 1;    //bit  0
    uint16_t    writeUncorrectableSupportVariants           : 1;    //bit  1
    uint16_t    datasetManagementSupportVariants            : 1;    //bit  2
    uint16_t    writeZeroesSupportVariants                  : 1;    //bit  3
    uint16_t    saveAndSelectFeatureSupport                 : 1;    //bit  4
    uint16_t    reservationsSupport                         : 1;    //bit  5
    uint16_t    timestampSupport                            : 1;    //bit  6
    uint16_t    verifySupport                               : 1;    //bit  7
    uint16_t    copySupport                                 : 1;    //bit  8
    uint16_t    nvmCopySingleAtomicity                      : 1;    //bit  9
    uint16_t    nvmAllFastCopy                              : 1;    //bit 10
    uint16_t    maximumWriteZeroesWithDeallocate            : 1;    //bit 11
    uint16_t    namespaceZeroesSupport                      : 1;    //bit 12
    uint16_t    _reserved                                   : 3;    //bits 13-15
}oncs_t;

typedef struct fuses_t
{
    uint16_t    fuseCompareAndWriteSupported        : 1;    //bit  0
    uint16_t    reserved                            :15;    //bits 1-15
}fuses_t;
    
typedef struct fna_t
{
    uint8_t     formatNamespaceScope                         : 1;    //bit  0
    uint8_t     secureEraseNamespaceScope                    : 1;    //bit  1
    uint8_t     cryptographicEraseSupported                  : 1;    //bit  2
    uint8_t     formatNvmBroadcastNotSupported               : 1;    //bit  3
    uint8_t     _reserved                                    : 4;    //bits 4-7
}fna_t;

typedef struct vwc_t
{
    uint8_t     volatileWriteCache                          : 1;    //bit  0
    uint8_t     flushCommandBehavior                        : 2;    //bits 1-2
    uint8_t     reserved                                    : 5;    //bits 3-7
}vwc_t;

typedef struct icsvscc_t
{
    uint8_t     sameNvmVendorSpecificCommandFormat           : 1;    //bit  0
    uint8_t     _reserved                                    : 7;    //bits 1-7
}icsvscc_t;
    
typedef struct nwpc_t
{
    uint8_t     supportNoWriteProtect                       : 1;    //bit 0
    uint8_t     supportWriteProtectUntilPowerCycleState     : 1;    //bit 1
    uint8_t     supportPermanentWriteProtectState           : 1;    //bit 2
    uint8_t     reserved                                    : 5;    //bits 3-7
}nwpc_t;

typedef struct cdfs_t
{
    uint16_t    copyDescriptorFormat0Support                 : 1;    //bit  0
    uint16_t    copyDescriptorFormat1Support                 : 1;    //bit  1
    uint16_t    copyDescriptorFormat2Support                 : 1;    //bit  2
    uint16_t    copyDescriptorFormat3Support                 : 1;    //bit  3
    uint16_t    copyDescriptorFormat4Support                 : 1;    //bit  4
    uint16_t    _reserved                                    :11;    //bits 5-15
}cdfs_t;

typedef struct sgls_t
{    
    uint32_t    sglSupport                              :2;     //bit 0-1
    uint32_t    keyedSglDataBlockDescriptorSupport      :1;     //bit 2
    uint32_t    _reserved0                              :4;     //bit 3-7
    uint32_t    sglDescriptorThreshold                  :8;     //bit 8-15
    uint32_t    sglBitBucketDescriptorSupported         :1;     //bit 16
    uint32_t    metadataBufferAlignment                 :1;     //bit 17
    uint32_t    lengthLargerThanDataTransferSupport     :1;     //bit 18
    uint32_t    mptrSglDescriptorSupport                :1;     //bit 19
    uint32_t    sglAddressOffsetSupported               :1;     //bit 20
    uint32_t    transportSglDataBlockDescriptorSupport  :1;     //bit 21
    uint32_t    _reserved1                              :10;    //bit 22-31
}sgls_t;
    
typedef struct trattr_t
{
    uint8_t     trackHostMemoryChangesSupport       : 1;    //bit  0
    uint8_t     trackUserDataChangesSupport         : 1;    //bit  1
    uint8_t     memoryRangeTrackingLengthLimit      : 1;    //bit  2
    uint8_t     _reserved                           : 5;    //bits 3-7
}trattr_t;

typedef struct psd_t
{    
    uint16_t    maximumPower;                               //bits 00-15    bytes 0-1   MP
    uint8_t     _reserved0;                                 //bits 16-23    bytes 2-3
    uint8_t     maxPowerScale                       : 1;    //bit  24       byte  4     MXPS
    uint8_t     nonOperationalState                 : 1;    //bit  25       byte  4     NOPS
    uint8_t     _reserved1                          : 6;    //bits 26-31    byte  4
    uint32_t    entryLatency;                               //bits 32-63    bytes 5-8   ENLAT
    uint32_t    exitLatency;                                //bits 64-95    bytes 9-12  EXLAT
    uint8_t     relativeReadThroughput              : 5;    //bits 96-100   byte  13    RRT
    uint8_t     _reserved2                          : 3;    //bits 101-103  byte  13        
    uint8_t     relativeReadLatency                 : 5;    //bits 104-108  byte  14    RRL
    uint8_t     _reserved3                          : 3;    //bits 109-111  byte  14        
    uint8_t     relativeWriteThroughput             : 5;    //bits 112-116  byte  15    RWT
    uint8_t     _reserved4                          : 3;    //bits 117-119  byte  15        
    uint8_t     relativeWriteLatency                : 5;    //bits 120-124  byte  16    RWL
    uint8_t     _reserved5                          : 3;    //bits 125-127  byte  16      
    uint16_t    idlePower;                                  //bits 128-143  bytes 17-18 IDLP
    uint8_t     _reserved6                          : 6;    //bits 144-149  byte  19
    uint8_t     idlePowerScale                      : 2;    //bits 150-151  byte  19    IPS
    uint8_t     _reserved7;                                 //bits 152-159  byte  20
    uint16_t    activePower;                                //bits 160-175  bytes 21-22 ACTP
    uint8_t     activePowerWorkload                 : 3;    //bits 176-178  byte  23    APW
    uint8_t     _reserved8                          : 3;    //bits 179-181  byte  23
    uint8_t     activePowerScale                    : 2;    //bits 182-183  byte  23    APS
    uint8_t     emergencyPowerFailRecoveryTime;             //bits 184-191  byte  24
    uint8_t     forcedQuiescenceVaultTime;                  //bits 192-199  byte  25
    uint8_t     emergencyPowerFailVaultTime;                //bits 200-207  byte  26
    uint8_t     emergencyPowerFailRecoveryTimeScale : 4;    //bits 208-211  byte  26
    uint8_t     forcedQuiescenceVaultTimeScale      : 4;    //bits 212-215  byte  26
    uint8_t     emergencyPowerFailVaultTimeScale    : 4;    //bits 216-219  byte  26
    uint8_t     _reserved9                          : 4;    //bits 220-223  byte  27
    uint8_t     maxBandwidth;                               //bits 224-231  byte  28
    uint8_t     maxBandwidthScale                   : 3;    //bits 232-234  byte  29
    uint8_t     _reserved10                         : 5;    //bits 235-239  byte  29
    uint16_t    minimumIdleIoExitLatencyLimit;              //bits 240-255  bytes 30-31
}psd_t;
  
typedef union __attribute__((packed, aligned (4))) identifyController_t
{
    uint32_t    mDword[NVME_IDENTIFY_DATA_SIZE_IN_DWORDS];

    struct
    {
        //------------------------------------------------------------------------------------------------------------------
        //Section 1 - Controller Capabilities and Features
        //bytes 0-255 (256 bytes)
        //------------------------------------------------------------------------------------------------------------------
        uint32_t    pciVendorID                                         : 16;   //VID                       //byte(s) 0-1
        uint32_t    pciSubsystemVendorID                                : 16;   //SSVID                     //byte(s) 2-3
        uint8_t     serialNumber[20];                                           //SN[20];                   //byte(s) 4-23
        uint8_t     modelNumber[40];                                            //MN[40];                   //byte(s) 24-63
        uint8_t     firmwareRevision[8];                                        //FR[8];                    //byte(s) 64-71
        uint32_t    recommendedArbitrationBurst                         : 8;    //RAB                       //byte(s) 72        
        uint32_t    ieeeOuiIdentifier                                   : 24;   //IEEE                      //byte(s) 73-75            
        cmic_t      controllerMultipathIoNamespaceSharingCapabilities;          //CMIC;                     //byte(s) 76    
        uint32_t    maximumDataTransferSize                             : 8;    //MDTS                      //byte(s) 77    
        uint32_t    controllerId                                        : 16;   //CNTLID                    //byte(s) 78-79        
        uint32_t    version;                                                    //VER;                      //byte(s) 80-83    
        uint32_t    rtd3ResumeLatency;                                          //RTD3R;                    //byte(s) 84-87
        uint32_t    rtd3EntryLatency;                                           //RTD3E;                    //byte(s) 88-91    
        oaes_t      optionalAysnchronouseEventsSupported;                       //OAES;                     //byte(s) 92-95    
        ctratt_t    controllerAttributes;                                       //CTRATT;                   //byte(s) 96-99
        rrls_t      readRecoveryLevelsSupported;                                //RRLS;                     //byte(s) 100-101                
        bpcap_t     bootPartitionCapabilities;                                  //BPCAP;                    //byte(s) 102
        chsi_t      cxlHdmSupportInformation;                                   //CHSI;                     //byte(s) 103
        uint32_t    nvmSubsystemShutdownLatency;                                //NSSL;                     //byte(s) 104-107        
        uint8_t     section1Reserved0[2];                                       //reserved                  //byte(s) 108-109
        plsi_t      powerLossSignalingInformation;                              //PLSI;                     //byte(s) 110
        uint8_t     controllerType                                      : 8;    //CNTRLTYPE                 //byte(s) 111
        uint8_t     fruGloballyUniqueId[16];                                    //FGUID[16];                //byte(s) 112-127
        uint32_t    commandRetryDelayTimer1                             : 16;   //CRDT1                     //byte(s) 128-129
        uint32_t    commandRetryDelayTimer2                             : 16;   //CRDT2                     //byte(s) 130-131
        uint32_t    commandRetryDelayTimer3                             : 16;   //CRDT3                     //byte(s) 132-133
        crcap_t     controllerReachabilityCapabilities;                         //CRCAP;                    //byte(s) 134 
        uint8_t     controllerInstanceUniquifier;                               //CIU;                     `//byte(s) 135
        uint64_t    controllerInstanceRandomNumber;                             //CIRN;                     //byte(s) 136-143
        uint8_t     section1Reserved1[96];                                      //reserved;                 //byte(s) 144-239
        uint8_t     managementInterface[13];                                    //managementInterface[16];  //byte(s) 240-252
        nvmsr_t     nvmSubsystemReport;                                         //NVMSR;                    //byte(s) 253
        vwci_t      vdpWriteCycleInformation;                                   //VWCI;                     //byte(s) 254
        mec_t       managementEndpointCapabilities;                             //MEC;                      //byte(s) 255

        //------------------------------------------------------------------------------------------------------------------
        //Section 2 - Admin Command Set Attributes
        //bytes 256-511 (256 bytes)
        //------------------------------------------------------------------------------------------------------------------
        oacs_t      optionalAdminCommandSupport;                                //OACS;                     //byte(s) 256-257     
        uint32_t    abortCommandLimit                                   : 8;    //ACL                       //byte(s) 258    
        uint32_t    asynchronousEventRequestLimit                       : 8;    //AERL                      //byte(s) 259    
        frmw_t      firmwareUpdates;                                            //FRMW;                     //byte(s) 260
        lpa_t       logPageAttributes;                                          //LPA;                      //byte(s) 261
        uint32_t    errorLogPageEntries                                 : 8;    //ELPE                      //byte(s) 262    
        uint32_t    numberOfPowerStatesSupported                        : 8;    //NPSS                      //byte(s) 263
        avscc_t     adminVendorSpecificCommandConfig;                           //AVSCC;                    //byte(s) 264
        apsta_t     autonomousPowerStateTransitionAttributes;                   //APSTA;                    //byte(s) 265
        uint32_t    warningCompositeTemperatureThreshold                : 16;   //WCTEMP                    //byte(s) 266-267
        uint32_t    criticalCompositeTemperatureThreshold               : 16;   //CCTEMP                    //byte(s) 268-269
        uint32_t    maximumTimeForFirmwareActivation                    : 16;   //MTFA                      //byte(s) 270-271
        uint32_t    hostMemoryBufferPreferredSize;                              //HMPRE;                    //byte(s) 272-275
        uint32_t    hostMemoryBufferMinimumSize;                                //HMMIN;                    //byte(s) 276-279        
        uint64_t    totalNVMCapacity[2];                                        //TNVMCAP[2];               //byte(s) 280-295    
        uint64_t    unallocatedNvmCapacity[2];                                  //UNVMCAP[2];               //byte(s) 296-311        
        rpmbs_t     replayProtectedMemoryBlockSupport;                          //RPMBS;                    //byte(s) 312-315
        uint32_t    extendedDeviceSelfTestMinutes                       : 16;   //EDSTT                     //byte(s) 316-317
        uint32_t    deviceSelfTestOptions                               : 8;    //DSTO                      //byte(s) 318
        uint32_t    firmwareUpdateGranularity                           : 8;    //FWUG                      //byte(s) 319    
        uint32_t    keepAliveSupport                                    : 16;   //KAS                       //byte(s) 320-321        
        hctma_t     hostControlledThermalManagementAttributes;                  //HCTMA                     //byte(s) 322-323
        uint32_t    minThermalManagementTemperature                     : 16;   //MNTMT                     //byte(s) 324-325
        uint32_t    maxThermalManagementTemperature                     : 16;   //MXTMT                     //byte(s) 326-327    
        sanicap_t   sanitizeCapabilities;                                       //SANICAP;                  //byte(s) 328-331    
        uint32_t    hostMemoryBufferMinimumDescriptorEntrySize;                 //HMMINDS;                  //byte(s) 332-335
        uint32_t    hostMemoryMaximumDescriptorsEntries                 : 16;   //HMMAXD                    //byte(s) 336-337
        uint32_t    nvmSetidentifierMaximum                             : 16;   //NSETIDMAX                 //byte(s) 338-339
        uint32_t    enduranceGroupIdentifierMaximum                     : 16;   //ENDGIDMAX                 //byte(s) 340-341
        uint32_t    anaTransitionTime                                   : 8;    //ANATT                     //byte(s) 342        
        anacap_t    asymmetricNamespaceAccessCapabilities;                      //ANACAP                    //byte(s) 343        
        uint32_t    anaGroupIdentifierMaximum;                                  //ANAGRPMAX;                //byte(s) 344-347
        uint32_t    numberOfAnaGroupIdentifiers;                                //NANAGRPID;                //byte(s) 348-351
        uint32_t    persistentEventLogSize;                                     //PELS;                     //byte(s) 352-355
        uint32_t    domainIdentifier                                    :16;    //DID;                      //byte(s) 356-357
        kpioc_t     keyPerIoCapabilities;                                       //KPIOC;                    //byte(s) 358
        uint8_t     section2Reserved0;                                                                      //byte(s) 359
        uint32_t    maxProcessingTimeForFirmwareActivationWithoutReset  :16;    //MPTFAWR;                  //byte(s) 360-361        
        
        rmdca_t     restoreManufacturingConfigurationAttributes;                //RMDCA;                    //byte(s) 362-363        
        uint8_t     section2Reserved1[4];                                       //reserved;                 //byte(s) 364-367        

        uint8_t     maxEnduranceGroupCapacity[16];                              //MEGCAP;                   //byte(s) 368-383
        tmpthha_t   temperatureThresholdHysteresisAttributes;                   //TMPTHHA;                  //byte(s) 384
        mupa_t      maxmimumUnlimitedPowerAttributes;                           //MUPTA;                    //byte(s) 385
        uint32_t    commandQuiesceTime                                  :16;    //CQT;                      //byte(s) 386-387
        cdpa_t      configurableDevicePersonalityAttributes;                    //CDPA;                     //byte(s) 388-389
        uint32_t    maxUnlimitedPower                                   :16;    //MUP;                      //byte(s) 390-391
        ipmsr_t     intervalPowerMeasurementSampleRate;                         //IPMSR;                    //byte(s) 392-393
        uint32_t    maxStopMeasurementTime                              :16;    //MSMT;                     //byte(s) 394-395
        uint32_t    maxNumberOfExportedNvmSubsystems                    :16;    //MNENS;                    //byte(s) 396-397
        uint32_t    maxNumberOfExportedControllersPerExportedNvmSubsys  :16;    //MNECPENS;                 //byte(s) 398-399
        uint32_t    maxExportedNvmSubsystemNumberOfNamespaces;                  //MENSNN;                   //byte(s) 400-403
        ensa_t      exportedNvmSubsystemAttributes;                             //ENSA;                     //byte(s) 404
        endsfs_t    exportedNamespaceDataStructureFormatsSupported;             //ENDSFS;                   //byte(s) 405
        uint32_t    voltageSensor1;                                             //VSEN1                     //byte(s) 406-409
        uint32_t    voltageSensor2;                                             //VSEN2                     //byte(s) 410-413
        uint32_t    voltageSensor3;                                             //VSEN3                     //byte(s) 414-417
        uint32_t    voltageSensor4;                                             //VSEN4                     //byte(s) 418-421
        uint32_t    maximumStopVoltageMeasurementTime                   :16;    //MSVMT;                    //byte(s) 422-423
        uint8_t     section2Reserved2[88];                                      //reserved;                 //byte(s) 424-511

        //------------------------------------------------------------------------------------------------------------------
        //Section 3 - NVM Command Set Attributes
        //bytes 512-703 (192 bytes)
        //------------------------------------------------------------------------------------------------------------------
        sqes_t      submissionQueueEntrySize;                                   //SQES;                     //byte(s) 512
        cqes_t      completionQueueEntrySize;                                   //CQES;                     //byte(s) 513    
        uint32_t    maximumOutstandingCommands                          : 16;   //MAXCMD                    //byte(s) 514-515
        uint32_t    numberOfNamespaces;                                         //NN;                       //byte(s) 516-519    
        oncs_t      optionalNvmCommandSupport;                                  //ONCS;                     //byte(s) 520-521
        fuses_t     fusedOperationSupport;                                      //FUSES;                    //byte(s) 522-523
        fna_t       formatNvmAttributes;                                        //FNA;                      //byte(s) 524
        vwc_t       volatileWriteCache;                                         //VWC;                      //byte(s) 525    
        uint32_t    atomicWriteUnitNormal                               : 16;   //AWUN                      //byte(s) 526-527
        uint32_t    atomicWriteUnitPowerFail                            : 16;   //AWUPF                     //byte(s) 528-529
        icsvscc_t   ioCommandSetVendorSpecificCommandConfiguration;             //ICSVSCC;                  //byte(s) 530    
        nwpc_t      namespaceWriteProtectionCapabilities;                       //NWPC;                     //byte(s) 531    
        uint32_t    atomicCompareAndWriteUnit                           : 16;   //ACWU                      //byte(s) 532-533    
        uint32_t    section3Reserved0                                   : 16;   //reserved                  //byte(s) 534-535    
        sgls_t      sglSupport;                                                 //SGLS;                     //byte(s) 536-539
        uint32_t    maximumNumberOfAllowedNamespaces;                           //MNAN;                     //byte(s) 540-543    
        uint8_t     section3Reserved1[224];                                     //section3Reserved1[224];   //byte(s) 544-767
        uint8_t     nvmSubsystemNvmeQualifiedName[256];                         //SUBNQN[256];              //byte(s) 768-1023
        uint8_t     section3Reserved2[768];                                     //section3Reserved2[768];   //byte(s) 1024-1791
        uint8_t     section3Reserved3[256];                                     //section3Reserved3[256];   //byte(s) 1792-2047
        //------------------------------------------------------------------------------------------------------------------
        //Section 4 - Power State Descriptors
        //bytes 2048-3071 (1024 bytes)
        //bytes 2048-2079 power state 0 descriptor is mandatory with up to 31 additional optional power state descriptors at 32 bytes each for a total of 1024 bytes
        //bytes 2080-3071 power state 1-31 descriptors are optional
        //------------------------------------------------------------------------------------------------------------------
        psd_t       powerStateDescriptor[32];                                   //PSD[32];                  //byte(s) 2048-3071
        //------------------------------------------------------------------------------------------------------------------
        //Section 5 - Vendor specific
        //bytes 3072-4095 (1024 bytes)
        //------------------------------------------------------------------------------------------------------------------
        uint8_t     vendorSpecific[1024];                                                                   //byte(s) 3072-4095    
    };    
}identifyController_t;
static_assert(sizeof(identifyController_t) == (NVME_IDENTIFY_DATA_SIZE), "identifyController_t incorrect size!");
