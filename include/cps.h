// Custom Pre-Set Header

#ifndef _CPS_H_
#define _CPS_H_

#define HASH_BLOCK_SIZE 1024

#ifdef EXPORTING_APIS
#define __rhct_api __declspec( dllexport )
#else
#define __rhct_api __declspec( dllimport )
#endif

#endif