// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BTM_TD_MUSICVARS_DEFAULT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BTM_TD_MUSICVARS_DEFAULT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BTM_TD_MUSICVARS_DEFAULT_EXPORTS
#define BTM_TD_MUSICVARS_DEFAULT_API __declspec(dllexport)
#else
#define BTM_TD_MUSICVARS_DEFAULT_API __declspec(dllimport)
#endif

// This class is exported from the btm_td_musicvars_default.dll
class BTM_TD_MUSICVARS_DEFAULT_API Cbtm_td_musicvars_default {
public:
	Cbtm_td_musicvars_default(void);
	// TODO: add your methods here.
};

extern BTM_TD_MUSICVARS_DEFAULT_API int nbtm_td_musicvars_default;

BTM_TD_MUSICVARS_DEFAULT_API int fnbtm_td_musicvars_default(void);
