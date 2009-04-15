
#include "execglue.h"

#define LIBNAME		"execglue.library"
#define VERSION		50
#define REVISION	2
#define BUILD_DATE	"15.04.2009"

#define LIBRARY_API	\
  (APTR) LFUNC(GetCPUInfo)


#include "libheader.c"
