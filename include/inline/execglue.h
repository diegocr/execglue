#ifndef _INLINE_EXECGLUE_H
#define _INLINE_EXECGLUE_H

#ifndef CLIB_EXECGLUE_PROTOS_H
#define CLIB_EXECGLUE_PROTOS_H
#endif

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif

#ifndef  LIBRARIES_EXECGLUE_H
#include <libraries/execglue.h>
#endif
#ifndef  UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#ifndef EXECGLUE_BASE_NAME
#define EXECGLUE_BASE_NAME ExecGlueBase
#endif

#define GetCPUInfo(tagList) \
	LP1NR(0x1e, GetCPUInfo, struct TagItem *, tagList, a0, \
	, EXECGLUE_BASE_NAME)

#ifndef NO_INLINE_STDARG
#define GetCPUInfoTags(tags...) \
	({ULONG _tags[] = {tags}; GetCPUInfo((struct TagItem *) _tags);})
#endif

#endif /*  _INLINE_EXECGLUE_H  */
