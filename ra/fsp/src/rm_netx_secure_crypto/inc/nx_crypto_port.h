/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Crypto Component                                                 */
/**                                                                       */
/**   Crypto                                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  COMPONENT DEFINITION                                   RELEASE        */
/*                                                                        */
/*    nx_crypto_port.h                                   Cortex-M3/IAR    */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains data type definitions for the NetX Security      */
/*    Encryption component.                                               */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     Timothy Stapko           Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/

#ifndef _NX_CRYPTO_PORT_H_
 #define _NX_CRYPTO_PORT_H_
 #include <stdlib.h>
 #include <string.h>
 #include "rm_netx_secure_crypto_cfg.h"
 #ifdef NX_CRYPTO_STANDALONE_ENABLE

  #if defined(__ICCARM__)
   #include <intrinsics.h>
  #endif

  #ifdef __cplusplus
extern "C" {
  #endif

/* Default to little endian, since this is what most ARM targets are.  */
  #define NX_CRYPTO_LITTLE_ENDIAN    1

/* Define macros that swap the endian for little endian ports.  */
  #if NX_CRYPTO_LITTLE_ENDIAN
   #if defined(__GNUC__)               /* GCC compiler */
    #define NX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)     (arg) = __builtin_bswap32(arg)
    #define NX_CRYPTO_CHANGE_USHORT_ENDIAN(arg)    (arg) = __builtin_bswap16(arg)
   #elif defined(__ICCARM__)           /* IAR compiler */
    #define NX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)     (arg) = __REV(arg)
    #define NX_CRYPTO_CHANGE_USHORT_ENDIAN(arg)    (arg) = __REV16(arg)
   #elif defined(__ARMCC_VERSION)      /* AC6 compiler */
    #define NX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)     (arg) = (unsigned int) (__rev(arg))
    #define NX_CRYPTO_CHANGE_USHORT_ENDIAN(arg)    (arg) = (unsigned short) (__rev(arg) >> 16)
   #endif
  #else
   #define NX_CRYPTO_CHANGE_ULONG_ENDIAN(a)
   #define NX_CRYPTO_CHANGE_USHORT_ENDIAN(a)
  #endif

  #ifndef VOID
   #define VOID    void
typedef char           CHAR;
typedef unsigned char  UCHAR;
typedef int            INT;
typedef unsigned int   UINT;
typedef long           LONG;
typedef unsigned long  ULONG;
typedef short          SHORT;
typedef unsigned short USHORT;
  #endif

 #endif                                /* NX_CRYPTO_STANDALONE_ENABLE */

 #ifdef __cplusplus
}
 #endif

#endif                                 /* _NX_CRYPTO_PORT_H_ */
