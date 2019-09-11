/*   Do *not* directly modify this file.  It was    */
/*   generated by the Configuration Tool; any  */
/*   changes risk being overwritten.                */

/* INPUT ex4b.cdb */

#define CHIP_6713 1

/*  Include Header Files  */
#include <std.h>
#include <hst.h>
#include <swi.h>
#include <tsk.h>
#include <log.h>
#include <sts.h>
#include <csl.h>
#include <csl_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

extern far HST_Obj RTA_fromHost;
extern far HST_Obj RTA_toHost;
extern far SWI_Obj KNL_swi;
extern far SWI_Obj SWI_ex4b;
extern far TSK_Obj TSK_idle;
extern far LOG_Obj LOG_system;
extern far STS_Obj IDL_busyObj;
extern far STS_Obj STS_algo;
extern far TIMER_Config timer1Cfg;
extern far TIMER_Handle hTimer1;
extern far void CSL_cfgInit();

#ifdef __cplusplus
}
#endif /* extern "C" */