
/**
 * $Id: execglue.h,v 0.1 2009/04/12 19:04:43 diegocr Exp $
 */

#ifndef EXECGLUE_EXECGLUE_H
#define EXECGLUE_EXECGLUE_H

#include <proto/exec.h>
#include <proto/execglue.h>
#include <proto/utility.h>

#if defined(__amigaos__)
#   include <SDI_lib.h>
#   define EG_API(func)	LIBFUNC LFUNC(func)
#   define EG_EXTERN	GLOBAL
#   ifdef __amigaos4__
#     include <exec/interfaces.h>
#     define egIFACE	struct Interface *self,
#     define egIFace	self,
#   else
#     include <exec/libraries.h>
#     define egIFACE
#     define egIFace
#   endif
#   define EG_ARGS(a...) (egIFACE a, REG(a6, struct Library * ExecGlueBase))
#   define egBase	,ExecGlueBase
#   define AFIX( a... )	egIFace a egBase
#else
#   define EG_API(func) func
#   define EG_EXTERN extern
#endif
#ifndef __amigaos__
#   define EG_ARGS(a...) (a)
#   define REG(r,a) a
#   define AFIX( a... ) a
#endif

EG_EXTERN VOID EG_API(GetCPUInfo) EG_ARGS(REG(a0, struct TagItem *tagList));


#endif /* EXECGLUE_EXECGLUE_H */
