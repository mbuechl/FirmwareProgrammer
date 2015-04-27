/* 
 * File:   XSVFPlayerConstants.h
 * Author: pperek
 *
 * Created on 24 kwiecień 2015, 10:42
 */

#ifndef XSVFPLAYERCONSTANTS_H
#define	XSVFPLAYERCONSTANTS_H

/*============================================================================
* #include files
============================================================================*/
#define DEBUG_MODE
#ifdef  DEBUG_MODE
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
#endif  /* DEBUG_MODE */

/*============================================================================
* XSVF #define
============================================================================*/

#define XSVF_VERSION    "5.01"

/*****************************************************************************
* Define:       XSVF_SUPPORT_ERRORCODES
* Description:  Define this to support the new XSVF error codes.
*               (The original XSVF player just returned 1 for success and
*               0 for an unspecified failure.)
*****************************************************************************/
#ifndef XSVF_SUPPORT_ERRORCODES
    #define XSVF_SUPPORT_ERRORCODES     1
#endif

#ifdef  XSVF_SUPPORT_ERRORCODES
    #define XSVF_ERRORCODE(errorCode)   errorCode
#else   /* Use legacy error code */
    #define XSVF_ERRORCODE(errorCode)   ((errorCode==XSVF_ERROR_NONE)?1:0)
#endif  /* XSVF_SUPPORT_ERRORCODES */

/*****************************************************************************
* Define:       XSVF_MAIN
* Description:  Define this to compile with a main function for standalone
*               debugging.
*****************************************************************************/
#ifndef XSVF_MAIN
    #ifdef DEBUG_MODE
        #define XSVF_MAIN   1
    #endif  /* DEBUG_MODE */
#endif  /* XSVF_MAIN */

/*============================================================================
* DEBUG_MODE #define
============================================================================*/

#ifdef  DEBUG_MODE
    #define XSVFDBG_PRINTF(iDebugLevel,pzFormat) \
                { if ( xsvf_iDebugLevel >= iDebugLevel ) \
                    printf( pzFormat ); }
    #define XSVFDBG_PRINTF1(iDebugLevel,pzFormat,arg1) \
                { if ( xsvf_iDebugLevel >= iDebugLevel ) \
                    printf( pzFormat, arg1 ); }
    #define XSVFDBG_PRINTF2(iDebugLevel,pzFormat,arg1,arg2) \
                { if ( xsvf_iDebugLevel >= iDebugLevel ) \
                    printf( pzFormat, arg1, arg2 ); }
    #define XSVFDBG_PRINTF3(iDebugLevel,pzFormat,arg1,arg2,arg3) \
                { if ( xsvf_iDebugLevel >= iDebugLevel ) \
                    printf( pzFormat, arg1, arg2, arg3 ); }
    #define XSVFDBG_PRINTLENVAL(iDebugLevel,plenVal) \
                { if ( xsvf_iDebugLevel >= iDebugLevel ) \
                    xsvfPrintLenVal(plenVal); }
#else   /* !DEBUG_MODE */
    #define XSVFDBG_PRINTF(iDebugLevel,pzFormat)
    #define XSVFDBG_PRINTF1(iDebugLevel,pzFormat,arg1)
    #define XSVFDBG_PRINTF2(iDebugLevel,pzFormat,arg1,arg2)
    #define XSVFDBG_PRINTF3(iDebugLevel,pzFormat,arg1,arg2,arg3)
    #define XSVFDBG_PRINTLENVAL(iDebugLevel,plenVal)
#endif  /* DEBUG_MODE */

/*============================================================================
* XSVF Type Declarations
============================================================================*/

/*****************************************************************************
* Struct:       SXsvfInfo
* Description:  This structure contains all of the data used during the
*               execution of the XSVF.  Some data is persistent, predefined
*               information (e.g. lRunTestTime).  The bulk of this struct's
*               size is due to the lenVal structs (defined in lenval.h)
*               which contain buffers for the active shift data.  The MAX_LEN
*               #define in lenval.h defines the size of these buffers.
*               These buffers must be large enough to store the longest
*               shift data in your XSVF file.  For example:
*                   MAX_LEN >= ( longest_shift_data_in_bits / 8 )
*               Because the lenVal struct dominates the space usage of this
*               struct, the rough size of this struct is:
*                   sizeof( SXsvfInfo ) ~= MAX_LEN * 7 (number of lenVals)
*               xsvfInitialize() contains initialization code for the data
*               in this struct.
*               xsvfCleanup() contains cleanup code for the data in this
*               struct.
*****************************************************************************/

/*============================================================================
* XSVF Command Bytes
============================================================================*/

/* encodings of xsvf instructions */
#define XCOMPLETE        0
#define XTDOMASK         1
#define XSIR             2
#define XSDR             3
#define XRUNTEST         4
/* Reserved              5 */
/* Reserved              6 */
#define XREPEAT          7
#define XSDRSIZE         8
#define XSDRTDO          9
#define XSETSDRMASKS     10
#define XSDRINC          11
#define XSDRB            12
#define XSDRC            13
#define XSDRE            14
#define XSDRTDOB         15
#define XSDRTDOC         16
#define XSDRTDOE         17
#define XSTATE           18         /* 4.00 */
#define XENDIR           19         /* 4.04 */
#define XENDDR           20         /* 4.04 */
#define XSIR2            21         /* 4.10 */
#define XCOMMENT         22         /* 4.14 */
#define XWAIT            23         /* 5.00 */
/* Insert new commands here */
/* and add corresponding xsvfDoCmd function to xsvf_pfDoCmd below. */
#define XLASTCMD         24         /* Last command marker */

/*============================================================================
* XSVF Command Parameter Values
============================================================================*/

#define XSTATE_RESET     0          /* 4.00 parameter for XSTATE */
#define XSTATE_RUNTEST   1          /* 4.00 parameter for XSTATE */

#define XENDXR_RUNTEST   0          /* 4.04 parameter for XENDIR/DR */
#define XENDXR_PAUSE     1          /* 4.04 parameter for XENDIR/DR */

/* TAP states */
#define XTAPSTATE_RESET     0x00
#define XTAPSTATE_RUNTEST   0x01    /* a.k.a. IDLE */
#define XTAPSTATE_SELECTDR  0x02
#define XTAPSTATE_CAPTUREDR 0x03
#define XTAPSTATE_SHIFTDR   0x04
#define XTAPSTATE_EXIT1DR   0x05
#define XTAPSTATE_PAUSEDR   0x06
#define XTAPSTATE_EXIT2DR   0x07
#define XTAPSTATE_UPDATEDR  0x08
#define XTAPSTATE_IRSTATES  0x09    /* All IR states begin here */
#define XTAPSTATE_SELECTIR  0x09
#define XTAPSTATE_CAPTUREIR 0x0A
#define XTAPSTATE_SHIFTIR   0x0B
#define XTAPSTATE_EXIT1IR   0x0C
#define XTAPSTATE_PAUSEIR   0x0D
#define XTAPSTATE_EXIT2IR   0x0E
#define XTAPSTATE_UPDATEIR  0x0F

#ifdef  DEBUG_MODE
    const char* xsvf_pzCommandName[]  =
    {
        "XCOMPLETE",
        "XTDOMASK",
        "XSIR",
        "XSDR",
        "XRUNTEST",
        "Reserved5",
        "Reserved6",
        "XREPEAT",
        "XSDRSIZE",
        "XSDRTDO",
        "XSETSDRMASKS",
        "XSDRINC",
        "XSDRB",
        "XSDRC",
        "XSDRE",
        "XSDRTDOB",
        "XSDRTDOC",
        "XSDRTDOE",
        "XSTATE",
        "XENDIR",
        "XENDDR",
        "XSIR2",
        "XCOMMENT",
        "XWAIT"
    };

    const char*   xsvf_pzErrorName[]  =
    {
        "No error",
        "ERROR:  Unknown",
        "ERROR:  TDO mismatch",
        "ERROR:  TDO mismatch and exceeded max retries",
        "ERROR:  Unsupported XSVF command",
        "ERROR:  Illegal state specification",
        "ERROR:  Data overflows allocated MAX_LEN buffer size"
    };

    const char*   xsvf_pzTapState[] =
    {
        "RESET",        /* 0x00 */
        "RUNTEST/IDLE", /* 0x01 */
        "DRSELECT",     /* 0x02 */
        "DRCAPTURE",    /* 0x03 */
        "DRSHIFT",      /* 0x04 */
        "DREXIT1",      /* 0x05 */
        "DRPAUSE",      /* 0x06 */
        "DREXIT2",      /* 0x07 */
        "DRUPDATE",     /* 0x08 */
        "IRSELECT",     /* 0x09 */
        "IRCAPTURE",    /* 0x0A */
        "IRSHIFT",      /* 0x0B */
        "IREXIT1",      /* 0x0C */
        "IRPAUSE",      /* 0x0D */
        "IREXIT2",      /* 0x0E */
        "IRUPDATE"      /* 0x0F */
    };
#endif  /* DEBUG_MODE */

#ifdef DEBUG_MODE
    FILE* in;   /* Legacy DEBUG_MODE file pointer */
    int xsvf_iDebugLevel = 0;
#endif /* DEBUG_MODE */

#endif	/* XSVFPLAYERCONSTANTS_H */

