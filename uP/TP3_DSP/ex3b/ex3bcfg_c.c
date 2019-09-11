/*   Do *not* directly modify this file.  It was    */
/*   generated by the Configuration Tool; any  */
/*   changes risk being overwritten.                */

/* INPUT ex3b.cdb */

/*  Include Header File  */
#include "ex3bcfg.h"


#ifdef __cplusplus
#pragma CODE_SECTION(".text:CSL_cfgInit")
#else
#pragma CODE_SECTION(CSL_cfgInit,".text:CSL_cfgInit")
#endif


#ifdef __cplusplus
#pragma FUNC_EXT_CALLED()
#else
#pragma FUNC_EXT_CALLED(CSL_cfgInit)
#endif
#include "ex3b.h"

extern far Int16 buffer;

/*  Config Structures */
EDMA_Config confEDMA = {
    0x491E0002,        /*  Option  */
    (Uint32) &buffer,        /*  Source Address - Extern Decl.Obj  */
    0x00000000,        /*  Transfer Counter - Numeric  */
    (Uint32) DXR1,        /*  Destination Address - From User's Header file  */
    0x00000000,        /*  Index register - Numeric  */
    0x00000000         /*  Element Count Reload and Link Address  */
};

/*  Handles  */
EDMA_Handle hEdmaChan14;
EDMA_Handle hEdmaReload;

/*
 *  ======== CSL_cfgInit() ========  
 */
void CSL_cfgInit()
{
    hEdmaChan14 = EDMA_open(EDMA_CHA_XEVT1, EDMA_OPEN_RESET);
    hEdmaReload = EDMA_allocTable(-1);
    confEDMA.rld = (confEDMA.rld & 0xFFFF0000) | (EDMA_RLD_RMK(0,hEdmaReload));
    confEDMA.cnt = EDMA_CNT_RMK(0,BUFFERSIZE);
    EDMA_config(hEdmaChan14, &confEDMA);
    EDMA_enableChannel(hEdmaChan14);
    EDMA_config(hEdmaReload, &confEDMA);
}
