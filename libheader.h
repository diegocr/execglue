
/**
 * $Id: libheader.h,v 0.1 2006/07/29 09:41:02 diegocr Exp $
 */

#ifndef LIBHEADER_H
#define LIBHEADER_H

#include <proto/intuition.h>

/****************************************************************************/

#ifdef __amigaos4__

/* redefine some defines to allow complexer macro use later on */
#define DoMethod	IDoMethod
#define DoMethodA	IDoMethodA
#define DoSuperMethod	IDoSuperMethod
#define DoSuperMethodA	IDoSuperMethodA
#define SetSuperAttrs	ISetSuperAttrs
#define CoerceMethod	ICoerceMethod
#define CoerceMethodA	ICoerceMethodA
#define CallHookA	CallHookPkt

#ifdef OpenWindowTags
#undef OpenWindowTags
#define OpenWindowTags	IIntuition->OpenWindowTags
#endif

#ifdef NewObject
#undef NewObject
#define NewObject	IIntuition->NewObject
#endif

#define GETINTERFACE(iface, base)	\
	(iface = (APTR)GetInterface((struct Library *)(base), "main", 1L, NULL))
#define DROPINTERFACE(iface)		\
	(DropInterface((struct Interface *)iface), iface = NULL)

#else /* !__amigaos4__ */

#include <clib/alib_protos.h>

#define GETINTERFACE(iface, base)	TRUE
#define DROPINTERFACE(iface)

GLOBAL ULONG STDARGS DoSuperNew(struct IClass *cl,Object *obj,ULONG tag1,...);

#endif /* ! __amigaos4__ */

/****************************************************************************/

#ifndef CPU_TAG
	#ifdef __PPC__
		#ifdef WARPUP
			#define CPU_TAG "WarpOS"
		#elif defined(__MORPHOS__)
			#define CPU_TAG "MorphOS"
		#elif defined(__amigaos4__)
			#define CPU_TAG "OS4"
		#else
			#define CPU_TAG "PPC"
		#endif
	#else
		#if defined(_M68060) || defined(mc68060) && !defined(mcmulti)
			#define CPU_TAG "68060"
		#elif defined(_M68040) || defined(mc68040) && !defined(mcmulti)
			#if defined(_M68881) || defined(__HAVE_68881__)
				#define CPU_TAG "68040+FPU"
			#else
				#define CPU_TAG "68040"
			#endif
		#elif defined(_M68030) || defined(mc68030)
			#if defined(_M68881) || defined(__HAVE_68881__)
				#define CPU_TAG "68030+FPU"
			#else
				#define CPU_TAG "68030"
			#endif
		#elif defined(_M68020) || defined(mc68020)
			#if defined(_M68881) || defined(__HAVE_68881__)
				#define CPU_TAG "68020+FPU"
			#else
				#define CPU_TAG "68020"
			#endif
		#elif defined(_M68000) || defined(mc68000)
			#define CPU_TAG "680x0"
		#else
			#define CPU_TAG "???"
		#endif
	#endif
#endif

/****************************************************************************/

#ifdef APIPROTOS
# include APIPROTOS
#endif

#ifndef LIBRARY_API
# error LIBRARY_API isnt defined...
#endif

/****************************************************************************/

#ifndef VERSION
# error VERSION isnt defined
#endif
#ifndef BUILD_DATE
# define BUILD_DATE __DATE__
# warning wrong date format used...
#endif
#ifndef BUILD_COPYRIGHT
# define BUILD_COPYRIGHT	"(c)2009 Diego Casorran"
#endif

#define mstr(str)	#str
#define d2str(v,r)	mstr(v) "." mstr(r)

#define PACKAGE_VERSION_TEXT	LIBNAME " " d2str(VERSION,REVISION)

#define LIBID	\
	"$VER:" PACKAGE_VERSION_TEXT " (" BUILD_DATE ") " BUILD_COPYRIGHT

/****************************************************************************/


#endif /* LIBHEADER_H */
