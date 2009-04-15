
/**
 * $Id: execglue.h,v 0.1 2009/04/12 21:05:54 diegocr Exp $
 */

#ifndef LIBRARIES_EXECGLUE_H
#define LIBRARIES_EXECGLUE_H

#include <exec/types.h>

#if INCLUDE_VERSION > 45
# warning I guess this library is useless to you...
#else

/* Tags for GetCPUInfo */
#define GCIT_NumberOfCPUs   (TAG_USER +  1)
#define GCIT_Family         (TAG_USER +  2)
#define GCIT_Model          (TAG_USER +  3)
#define GCIT_ModelString    (TAG_USER +  4)
#define GCIT_Version        (TAG_USER +  5)
#define GCIT_VersionString  (TAG_USER +  6)
#define GCIT_FrontsideSpeed (TAG_USER +  7)
#define GCIT_ProcessorSpeed (TAG_USER +  8)
#define GCIT_L1CacheSize    (TAG_USER +  9)
#define GCIT_L2CacheSize    (TAG_USER + 10)
#define GCIT_L3CacheSize    (TAG_USER + 11)
#define GCIT_VectorUnit     (TAG_USER + 12)
#define GCIT_Extensions     (TAG_USER + 13)
#define GCIT_CacheLineSize  (TAG_USER + 14)
#define GCIT_CPUPageSize    (TAG_USER + 15)
#define GCIT_ExecPageSize   (TAG_USER + 16)
#define GCIT_TimeBaseSpeed  (TAG_USER + 17)
#define GCIT_MachinePVR     (TAG_USER + 901)

/* Family codes */
enum enCPUFamiliy
{
    CPUFAMILY_UNKNOWN = 0,
    CPUFAMILY_60X     = 1,
    CPUFAMILY_7X0     = 2,
    CPUFAMILY_74XX    = 3,
    CPUFAMILY_4XX     = 4
};

/* Model codes */
enum enCPUModel
{
    CPUTYPE_UNKNOWN        =  0,
    CPUTYPE_PPC603E        =  1,
    CPUTYPE_PPC604E        =  2,
    CPUTYPE_PPC750CXE      =  3,
    CPUTYPE_PPC750FX       =  4,
    CPUTYPE_PPC750GX       =  5,
    CPUTYPE_PPC7410        =  6,
    CPUTYPE_PPC74XX_VGER   =  7,
    CPUTYPE_PPC74XX_APOLLO =  8,
    CPUTYPE_PPC405LP       =  9,
    CPUTYPE_PPC405EP       = 10,
    CPUTYPE_PPC405GP       = 11,
    CPUTYPE_PPC405GPR      = 12,
    CPUTYPE_PPC440EP       = 13,
    CPUTYPE_PPC440GP       = 14,
    CPUTYPE_PPC440GX       = 15,
    CPUTYPE_PPC440SX       = 16,
    CPUTYPE_PPC440SP       = 17
};

/* Vector unit types */
enum enVectorUnitType
{
    VECTORTYPE_NONE    = 0,
    VECTORTYPE_ALTIVEC = 1,
    VECTORTYPE_VMX     = 2
};

#endif /* INCLUDE_VERSION */
#endif /* LIBRARIES_EXECGLUE_H */
