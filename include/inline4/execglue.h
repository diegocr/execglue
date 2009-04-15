#ifndef INLINE4_EXECGLUE_H
#define INLINE4_EXECGLUE_H

/*
** This file was auto generated by idltool 50.13.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef LIBRARIES_EXECGLUE_H
#include <libraries/execglue.h>
#endif

/* Inline macros for Interface "main" */
#define GetCPUInfo(tagList) IExecGlue->GetCPUInfo(tagList) 
#if !defined(__cplusplus) && (__STDC_VERSION__ >= 199901L || __GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95))
#define GetCPUInfoTags(...) IExecGlue->GetCPUInfoTags(__VA_ARGS__) 
#endif

#endif /* INLINE4_EXECGLUE_H */