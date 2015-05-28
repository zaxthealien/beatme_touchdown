#ifndef BTM_TD_DLL_H
#define BTM_TD_DLL_H

#ifndef BTM_TD_DLL_EXPORTS
#define BTM_TD_DLL_API __declspec(dllexport)
#else
#define BTM_TD_DLL_API
#endif

#endif