// hash function header

#ifndef _HASH_H_
#define _HASH_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<openssl/crypto.h>
#include<openssl/md5.h>
#include<openssl/sha.h>

#include"cps.h"

#ifdef __cplusplus
extern "C" {
#endif

__rhct_api void __cdecl hashstr_md5( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_md5( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha1( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha1( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha224( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha224( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha256( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha256( FILE* __f , char* __out );

#ifdef __cplusplus
}
#endif

#endif