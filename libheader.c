
/**
 * Startup code for AmigaOS's Shared Libraries.
 * (heavily based on mccheader.c)
 *
 * $Id: libheader.c,v 0.1 2006/07/29 10:08:28 diegocr Exp $
 */

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/

/* MorphOS relevant includes... */
#ifdef __MORPHOS__
#include <emul/emulinterface.h>
#include <emul/emulregs.h>
#endif

/* a few other includes... */

#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <exec/semaphores.h>
#include <exec/resident.h>
#include <exec/execbase.h>
#include <dos/dos.h>

#include <proto/exec.h>
#include <proto/utility.h>
//#include <proto/intuition.h>
#include <SDI_lib.h>

#include "libheader.h"

/* Entry point, if the user try to run me I'll return to the shell nicely */
#ifndef __amigaos4__
STATIC CONST UWORD __rts = 0x4E75;
#else
int _start( void )
{
	return 0;
}
#endif

/* We need a pointer to this string in our ROMTag (see below). */
STATIC CONST UBYTE UserLibID[] = LIBID;
STATIC CONST UBYTE UserLibName[] = LIBNAME;

/* Here's our global data, described above. */

#if defined(__amigaos4__)
#include <inline4/exec.h>
struct Library *SysBase       = NULL;
struct Library *UtilityBase   = NULL;
//struct Library *IntuitionBase = NULL;
struct ExecIFace *IExec       = NULL;
struct UtilityIFace *IUtility = NULL;
//struct IntuitionIFace *IIntuition = NULL;
#else
struct ExecBase       *SysBase       = NULL;
//struct DosLibrary     *DOSBase       = NULL;
//struct IntuitionBase  *IntuitionBase = NULL;
#endif

/* Our library structure, consisting of a struct Library, a segment pointer */
/* and a semaphore. We need the semaphore to protect init/exit stuff in our */
/* open/close functions */

struct LibraryHeader
{
  struct Library         lh_Library;
  UWORD                  lh_Pad1;
  BPTR                   lh_Segment;
  struct SignalSemaphore lh_Semaphore;
  UWORD                  lh_Pad2;
};

/******************************************************************************/
/* Local Structures & Prototypes                                              */
/******************************************************************************/

#if defined(__amigaos4__)

struct LibraryHeader *   LIBFUNC LibInit   (struct LibraryHeader *base, BPTR librarySegment, struct ExecIFace *pIExec);
BPTR                     LIBFUNC LibExpunge(struct LibraryManagerInterface *Self);
struct LibraryHeader *   LIBFUNC LibOpen   (struct LibraryManagerInterface *Self, ULONG version);
BPTR                     LIBFUNC LibClose  (struct LibraryManagerInterface *Self);
ULONG                    LIBFUNC MCC_Query (UNUSED struct Interface *self, REG(d0, LONG which));

#elif defined(__MORPHOS__)

struct LibraryHeader *   LIBFUNC LibInit   (struct LibraryHeader *base, BPTR Segment, struct ExecBase *SysBase);
BPTR                     LIBFUNC LibExpunge(void);
struct LibraryHeader *   LIBFUNC LibOpen   (void);
BPTR                     LIBFUNC LibClose  (void);
ULONG                    LIBFUNC MCC_Query (void);

#else

struct LibraryHeader *   LIBFUNC LibInit   (REG(a0, BPTR Segment), REG(a6, struct ExecBase *SysBase));
BPTR                     LIBFUNC LibExpunge(REG(a6, struct LibraryHeader *base));
struct LibraryHeader *   LIBFUNC LibOpen   (REG(a6, struct LibraryHeader *base));
BPTR                     LIBFUNC LibClose  (REG(a6, struct LibraryHeader *base));
ULONG                    LIBFUNC MCC_Query (REG(d0, LONG which));

#endif

/*****************************************************************************/
/*****************************************************************************/

#define CrossOpenLib( BASE, IFACE, NAME, VERSION )	\
	((BASE = OpenLibrary( NAME,VERSION)) && GETINTERFACE( IFACE, BASE ))

#define CrossCloseLib( BASE, IFACE )	\
	DROPINTERFACE( IFACE );	CloseLibrary( BASE ); BASE = NULL

INLINE BOOL UserLibOpen(struct Library *base)
{
	BOOL UserLibInitFunc(struct Library *base);
	
	if(base->lib_OpenCnt != 1 )
		return(TRUE);
	
//	if(CrossOpenLib( IntuitionBase, IIntuition, "intuition.library", 39))
	{
		if(CrossOpenLib( UtilityBase, IUtility, "utility.library", 39))
		{
			#ifdef UserLibInit
			if(UserLibInitFunc( base ))
			#endif
			
				return(TRUE);
			
			CrossCloseLib( UtilityBase, IUtility );
		}
		
	//	CrossCloseLib( IntuitionBase, IIntuition );
	}
	
	return(FALSE);
}

/*****************************************************************************/
/*****************************************************************************/

INLINE BOOL UserLibClose(struct Library *base)
{
	BOOL UserLibExitFunc(struct Library *base);
	
	if(base->lib_OpenCnt == 1 )
	{
		#ifdef UserLibExit
		UserLibExitFunc( base );
		#endif
		
		CrossCloseLib( UtilityBase, IUtility );
	//	CrossCloseLib( IntuitionBase, IIntuition );
	}
	
	return(TRUE);
}

/*****************************************************************************/
/*****************************************************************************/

/******************************************************************************/
/* Local data structures                                                      */
/******************************************************************************/

#if defined(__amigaos4__)
/* ------------------- OS4 Manager Interface ------------------------ */
STATIC ULONG LibObtain(struct LibraryManagerInterface *Self)
{
   return(Self->Data.RefCount++);
}

STATIC ULONG LibRelease(struct LibraryManagerInterface *Self)
{
   return(Self->Data.RefCount--);
}

STATIC CONST APTR LibManagerVectors[] =
{
   (APTR)LibObtain,
   (APTR)LibRelease,
   (APTR)NULL,
   (APTR)NULL,
   (APTR)LibOpen,
   (APTR)LibClose,
   (APTR)LibExpunge,
   (APTR)NULL,
   (APTR)-1
};

STATIC CONST struct TagItem LibManagerTags[] =
{
   {MIT_Name,             (ULONG)"__library"},
   {MIT_VectorTable,      (ULONG)LibManagerVectors},
   {MIT_Version,          1},
   {TAG_DONE,             0}
};

/* ------------------- Library Interface(s) ------------------------ */

STATIC CONST APTR LibVectors[] =
{
   (APTR)LibObtain,
   (APTR)LibRelease,
   (APTR)NULL,
   (APTR)NULL,
   LIBRARY_API,
   (APTR)-1
};

STATIC CONST struct TagItem MainTags[] =
{
   {MIT_Name,        (ULONG)"main"},
   {MIT_VectorTable, (ULONG)LibVectors},
   {MIT_Version,     1},
   {TAG_DONE,        0}
};

STATIC CONST ULONG LibInterfaces[] =
{
   (ULONG)LibManagerTags,
   (ULONG)MainTags,
   (ULONG)0
};

// Out libraries always have to carry a 68k jump table with it, so
// lets define it here as extern, as we are going to link it to
// our binary here.
#ifndef NO_VECTABLE68K
extern const APTR VecTable68K[];
#endif

STATIC CONST struct TagItem LibCreateTags[] =
{
   {CLT_DataSize,   (ULONG)(sizeof(struct LibraryHeader))},
   {CLT_InitFunc,   (ULONG)LibInit},
   {CLT_Interfaces, (ULONG)LibInterfaces},
   #ifndef NO_VECTABLE68K
   {CLT_Vector68K,  (ULONG)VecTable68K},
   #endif
   {TAG_DONE,       0}
};

#else

LONG LIBFUNC LibNull(VOID) {
	return(0);
}

static const APTR LibVectors[] =
{
  #ifdef __MORPHOS__
  (APTR)FUNCARRAY_32BIT_NATIVE,
  #endif
  (APTR)LibOpen,
  (APTR)LibClose,
  (APTR)LibExpunge,
  (APTR)LibNull,
  LIBRARY_API,
  (APTR)-1
};

#endif

/* ------------------- ROM Tag ------------------------ */
static const USED_VAR struct Resident ROMTag =
{
  RTC_MATCHWORD,
  (struct Resident *)&ROMTag,
  (struct Resident *)&ROMTag + 1,
  #if defined(__amigaos4__)
  RTF_AUTOINIT|RTF_NATIVE,      // The Library should be set up according to the given table.
  #elif defined(__MORPHOS__)
  RTF_PPC,
  #else
  0,
  #endif
  VERSION,
  NT_LIBRARY,
  0,
  (char *)UserLibName,
  (char *)UserLibID+5,
  #if defined(__amigaos4__)
  (APTR)LibCreateTags,           // This table is for initializing the Library.
  #else
  (APTR)LibInit,
  #endif
  #if defined(__MORPHOS__)
  REVISION,
  0
  #endif
};

#if defined(__MORPHOS__)
/*
 * To tell the loader that this is a new emulppc elf and not
 * one for the ppc.library.
 * ** IMPORTANT **
 */
const USED_VAR ULONG __amigappc__ = 1;
const USED_VAR ULONG __abox__ = 1;

#undef USE_SEMAPHORE

#else

#ifndef USE_SEMAPHORE
#define USE_SEMAPHORE
#endif

#endif /* __MORPHOS */

#ifndef __amigaos4__
#define DeleteLibrary(LIB) \
  FreeMem((STRPTR)(LIB)-(LIB)->lib_NegSize, (ULONG)((LIB)->lib_NegSize+(LIB)->lib_PosSize))
#endif

/******************************************************************************/
/* Standard Library Functions, all of them are called in Forbid() state.      */
/******************************************************************************/

#if defined(__amigaos4__)
struct LibraryHeader * ASM SAVEDS LibInit(struct LibraryHeader *base, BPTR librarySegment, struct ExecIFace *pIExec)
{
  struct ExecBase *sb = (struct ExecBase *)pIExec->Data.LibBase;
  IExec = pIExec;
  SysBase = (struct Library *)sb;

  base->lh_Library.lib_Node.ln_Type = NT_LIBRARY;
  base->lh_Library.lib_Node.ln_Pri  = 0;
  base->lh_Library.lib_Node.ln_Name = (char *)UserLibName;
  base->lh_Library.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
  base->lh_Library.lib_Version      = VERSION;
  base->lh_Library.lib_Revision     = REVISION;
  base->lh_Library.lib_IdString     = (char *)UserLibID;

  base->lh_Segment = librarySegment;

  InitSemaphore(&base->lh_Semaphore);

  /*
  if(!UserLibInit((struct Library *)base))
  {
    DeleteLibrary((struct Library *)base);
    return(NULL);
  }
  */

  return(base);
}

#else

#ifdef __MORPHOS__
#undef CLASS_STACKSWAP
struct LibraryHeader *LibInit(struct LibraryHeader *base, BPTR Segment, struct ExecBase *sb)
{
#else
struct LibraryHeader * ASM SAVEDS LibInit(REG(a0, BPTR Segment), REG(a6, struct ExecBase *sb))
{
#endif

  #if !defined(__MORPHOS__)
  struct LibraryHeader *base;
  #endif

  SysBase = sb;

#if defined(__HAVE_68881__)
  if(!(SysBase->AttnFlags & AFF_68881))
  	return(NULL);
#endif
#if defined(_M68060) || defined(mc68060) || defined(__mc68060)
  if(!(SysBase->AttnFlags & AFF_68060))
    return(NULL);
#elif defined(_M68040) || defined(mc68040) || defined(__mc68040)
  if(!(SysBase->AttnFlags & AFF_68040))
    return(NULL);
#elif defined(_M68030) || defined(mc68030) || defined(__mc68030)
  if(!(SysBase->AttnFlags & AFF_68030))
    return(NULL);
#elif defined(_M68020) || defined(mc68020) || defined(__mc68020)
  if(!(SysBase->AttnFlags & AFF_68020))
    return(NULL);
#endif

  if((base = (struct LibraryHeader *)MakeLibrary((APTR)LibVectors,NULL,NULL,sizeof(struct LibraryHeader),NULL)))
  {
    base->lh_Library.lib_Node.ln_Type = NT_LIBRARY;
    base->lh_Library.lib_Node.ln_Name = (char *)UserLibName;
    base->lh_Library.lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
    base->lh_Library.lib_Version      = VERSION;
    base->lh_Library.lib_Revision     = REVISION;
    base->lh_Library.lib_IdString     = (char *)UserLibID;

    base->lh_Segment  = Segment;

    #if defined(USE_SEMAPHORE)
    InitSemaphore(&base->lh_Semaphore);
    #endif

    AddLibrary((struct Library *)base);
  }

  return(base);
}
#endif

/*****************************************************************************/
/*****************************************************************************/

#ifdef __amigaos4__
BPTR LibExpunge(struct LibraryManagerInterface *Self)
{
  struct LibraryHeader *base = (struct LibraryHeader *)Self->Data.LibBase;
#elif __MORPHOS__
BPTR LibExpunge(void)
{
  struct LibraryHeader *base = (void *)REG_A6;
#else
BPTR ASM SAVEDS LibExpunge(REG(a6, struct LibraryHeader *base))
{
#endif
  BPTR rc;

  if(base->lh_Library.lib_OpenCnt > 0)
  {
    base->lh_Library.lib_Flags |= LIBF_DELEXP;
    return(0);
  }

  Remove((struct Node *)base);
  rc = base->lh_Segment;

  DeleteLibrary(&base->lh_Library);

  return(rc);
}

/*****************************************************************************/
/*****************************************************************************/

#ifdef __amigaos4__
struct LibraryHeader *LibOpen(struct LibraryManagerInterface *Self, UNUSED ULONG version)
{
  struct LibraryHeader *base = (struct LibraryHeader *)Self->Data.LibBase;
#elif __MORPHOS__
struct LibraryHeader *LibOpen( void )
{
  struct LibraryHeader *base = (void *)REG_A6;
#else
struct LibraryHeader * ASM SAVEDS LibOpen(REG(a6, struct LibraryHeader *base))
{
#endif
  struct LibraryHeader *rc;

  /* Kill the Delayed Expunge flag since we are opened again */
  base->lh_Library.lib_Flags &= ~LIBF_DELEXP;

  #ifdef USE_SEMAPHORE
  ObtainSemaphore(&base->lh_Semaphore);
  #endif

  base->lh_Library.lib_OpenCnt++;

  if(UserLibOpen(&base->lh_Library))
  {
    rc = base;
  }
  else
  {
    rc = NULL;
    base->lh_Library.lib_OpenCnt--;
  }

  #ifdef USE_SEMAPHORE
  ReleaseSemaphore(&base->lh_Semaphore);
  #endif

  return(rc);
}

/*****************************************************************************/
/*****************************************************************************/

#ifdef __amigaos4__
BPTR LibClose(struct LibraryManagerInterface *Self)
{
  struct LibraryHeader *base = (struct LibraryHeader *)Self->Data.LibBase;
#elif __MORPHOS__
BPTR LibClose(void)
{
  struct LibraryHeader *base = (struct LibraryHeader *)REG_A6;
#else
BPTR ASM SAVEDS LibClose(REG(a6, struct LibraryHeader *base))
{
#endif
  BPTR rc = 0;

  #ifdef USE_SEMAPHORE
  ObtainSemaphore(&base->lh_Semaphore);
  #endif

  UserLibClose((struct Library *)base);

  base->lh_Library.lib_OpenCnt--;

  #ifdef USE_SEMAPHORE
  ReleaseSemaphore(&base->lh_Semaphore);
  #endif

  if(base->lh_Library.lib_OpenCnt == 0 &&
     base->lh_Library.lib_Flags & LIBF_DELEXP)
  {
    #ifdef __amigaos4__
    rc = LibExpunge(Self);
    #elif __MORPHOS__
    rc = LibExpunge();
    #else
    rc = LibExpunge(base);
    #endif
  }

  return(rc);
}
