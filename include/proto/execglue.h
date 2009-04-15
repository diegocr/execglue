#ifndef _PROTO_EXECGLUE_H
#define _PROTO_EXECGLUE_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#if !defined(CLIB_EXECGLUE_PROTOS_H) && !defined(__GNUC__)
#include <clib/execglue_protos.h>
#endif

#ifndef __NOLIBBASE__
extern struct Library *ExecGlueBase;
#endif

#ifdef __GNUC__
#include <inline/execglue.h>
#elif defined(__VBCC__)
#include <inline/execglue_protos.h>
#else
#include <pragma/execglue_lib.h>
#endif

#endif	/*  _PROTO_EXECGLUE_H  */
