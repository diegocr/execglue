#ifndef PROTO_EXECGLUE_H
#define PROTO_EXECGLUE_H

/*
**	$Id$
**	Includes Release 50.1
**
**	Prototype/inline/pragma header file combo
**
**	(C) Copyright 2003-2004 Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef LIBRARIES_EXECGLUE_H
#include <libraries/execglue.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  extern struct Library * ExecGlueBase;
 #else
  extern struct Library * ExecGlueBase;
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/execglue.h>
 #ifdef __USE_INLINE__
  #include <inline4/execglue.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_EXECGLUE_PROTOS_H
  #define CLIB_EXECGLUE_PROTOS_H 1
 #endif /* CLIB_EXECGLUE_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct ExecGlueIFace *IExecGlue;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_EXECGLUE_PROTOS_H
  #include <clib/execglue_protos.h>
 #endif /* CLIB_EXECGLUE_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/execglue.h>
  #else
   #include <ppcinline/execglue.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/execglue_protos.h>
  #endif /* __PPC__ */
 #else
  #include <pragmas/execglue_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_EXECGLUE_H */
