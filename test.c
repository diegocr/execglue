
#include <proto/exec.h>
#include <proto/execglue.h>
#include <proto/dos.h>

struct Library *ExecGlueBase;

#define PV(x) Printf("%s: %08lx,%ld\n",(LONG) #x,x,x)
#define PS(x) Printf("%s: %08lx,\"%s\"\n",(LONG) #x,x,(LONG)(x?x:"NULL"))
#define PLL(x) Printf("%s: %08lx%08lx\n",(LONG) #x,*((long *)x),*((long *)&x[4]))

int main( void )
{
	if(!(ExecGlueBase = OpenLibrary("execglue.library",50)))
	{
		Printf("Could not open %s V%ld\n",(LONG)"execglue.library",50);
	}
	else
	{
		ULONG Version = 0x7f7f7f7f;
		ULONG NumberOfCPUs = 0;
		ULONG Family = 0;
		ULONG Model = 0;
		ULONG L1CacheSize = 0;
		ULONG L2CacheSize = 0;
		ULONG L3CacheSize = 0;
		ULONG CacheLineSize = 0;
		ULONG VectorUnit = 0;
		ULONG CPUPageSize = 0;
		ULONG ExecPageSize = 0;
		CONST_STRPTR ModelString = NULL;
		CONST_STRPTR VersionString = NULL;
		CONST_STRPTR Extensions = NULL;
		UBYTE FrontsideSpeed[9];
		UBYTE ProcessorSpeed[9];
		UBYTE TimeBaseSpeed[9];
		
		GetCPUInfoTags(
			GCIT_Version,(ULONG)&Version,
			GCIT_NumberOfCPUs,(ULONG)&NumberOfCPUs,
			GCIT_Family,(ULONG)&Family,
			GCIT_Model,(ULONG)&Model,
			GCIT_L1CacheSize,(ULONG)&L1CacheSize,
			GCIT_L2CacheSize,(ULONG)&L2CacheSize,
			GCIT_L3CacheSize,(ULONG)&L3CacheSize,
			GCIT_CacheLineSize,(ULONG)&CacheLineSize,
			GCIT_VectorUnit,(ULONG)&VectorUnit,
			GCIT_CPUPageSize,(ULONG)&CPUPageSize,
			GCIT_ExecPageSize,(ULONG)&ExecPageSize,
			GCIT_ModelString,(ULONG)&ModelString,
			GCIT_VersionString,(ULONG)&VersionString,
			GCIT_Extensions,(ULONG)&Extensions,
			GCIT_FrontsideSpeed,(ULONG)&FrontsideSpeed,
			GCIT_ProcessorSpeed,(ULONG)&ProcessorSpeed,
			GCIT_TimeBaseSpeed,(ULONG)&TimeBaseSpeed,
		TAG_DONE);
		
		PV(Version);
		PV(NumberOfCPUs);
		PV(Family);
		PV(Model);
		PV(L1CacheSize);
		PV(L2CacheSize);
		PV(L3CacheSize);
		PV(CacheLineSize);
		PV(VectorUnit);
		PV(CPUPageSize);
		PV(ExecPageSize);
		PS(ModelString);
		PS(VersionString);
		PS(Extensions);
		PLL(FrontsideSpeed);
		PLL(ProcessorSpeed);
		PLL(TimeBaseSpeed);
		
		CloseLibrary(ExecGlueBase);
	}
}
