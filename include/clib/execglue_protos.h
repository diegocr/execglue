#ifndef CLIB_EXECGLUE_PROTOS_H
#define CLIB_EXECGLUE_PROTOS_H


/*
**	$VER: execglue_protos.h 1.0 (12.04.2009)
**
**	C prototypes. For use with 32 bit integers only.
**
**	Copyright © 2009 Diego Casorran
**	All Rights Reserved
*/

#ifndef  LIBRARIES_EXECGLUE_H
#include <libraries/execglue.h>
#endif
#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

VOID GetCPUInfo(struct TagItem * tagList);
VOID GetCPUInfoTags(ULONG tagList, ...);

#endif	/*  CLIB_EXECGLUE_PROTOS_H  */
