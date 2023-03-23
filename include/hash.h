// hash function header

#ifndef _HASH_H_
#define _HASH_H_

#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/md5.h>

#include"cps.h"

#ifdef __cplusplus
extern "C" {
#endif

__rhct_api void __cdecl hashfile_md5( FILE* __f , char* __out );

#ifdef __cplusplus
}
#endif

#endif