// Custom Pre-Set Header

#ifndef _CPS_H_
#define _CPS_H_

#define HASH_BLOCK_SIZE 1024
#define MAX_PATH_LENGTH 0x7fff
#define THREADS_NUM     4

#define PROCESSBAR_CHAR   "="
#define PROCESSBAR_LENGTH  50

typedef char* PATH;

#ifdef EXPORTING_APIS
#define __rhct_api __declspec( dllexport )
#else
#define __rhct_api __declspec( dllimport )
#endif

#endif