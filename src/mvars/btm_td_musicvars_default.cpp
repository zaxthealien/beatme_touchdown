// btm_td_musicvars_default.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "btm_td_musicvars_default.h"


// This is an example of an exported variable
BTM_TD_MUSICVARS_DEFAULT_API int nbtm_td_musicvars_default=0;

// This is an example of an exported function.
BTM_TD_MUSICVARS_DEFAULT_API int fnbtm_td_musicvars_default(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see btm_td_musicvars_default.h for the class definition
Cbtm_td_musicvars_default::Cbtm_td_musicvars_default()
{
	return;
}
