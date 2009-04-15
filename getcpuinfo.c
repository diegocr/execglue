/* ***** BEGIN LICENSE BLOCK *****
 * Version: APL License
 * 
 * Copyright (c) 2009 Diego Casorran <dcasorran@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * ***** END LICENSE BLOCK ***** */


/**
 * $Id: getcpuinfo.c,v 0.1 2009/04/12 19:05:50 diegocr Exp $
 */

#include "execglue.h"

STATIC ULONG GetPVR(struct ExecIFace *pIExec UNUSED)
{
	ULONG pvr;
	
	__asm__ __volatile__ ("mfpvr %0" : "=r"(pvr));
	return(pvr);
}

VOID EG_API(GetCPUInfo) EG_ARGS(REG(a0, struct TagItem *tagList))
{
	ULONG *pvr;
	
	IExec->GetCPUInfo((const struct TagItem *)tagList);
	
	// ExecGlue's Extension...
	if((pvr = (ULONG *)IUtility->GetTagData(GCIT_MachinePVR,0,tagList)))
	{
		(*pvr) = IExec->Supervisor((void *)&GetPVR);
	}
}
