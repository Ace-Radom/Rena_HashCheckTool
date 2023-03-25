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

#ifdef USING_PTHREAD
typedef struct {
    FILE* f;
    char* out;
} hashfile_arg_package;
#endif

__rhct_api void __cdecl hashstr_md5( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_md5( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha1( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha1( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha224( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha224( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha256( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha256( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha384( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha384( FILE* __f , char* __out );
__rhct_api void __cdecl hashstr_sha512( unsigned const char* __str , char* __out );
__rhct_api void __cdecl hashfile_sha512( FILE* __f , char* __out );

#ifdef USING_PTHREAD
__rhct_api void* __cdecl hashfile_md5_mt( void* __arg_package );
__rhct_api void* __cdecl hashfile_sha1_mt( void* __arg_package );
__rhct_api void* __cdecl hashfile_sha224_mt( void* __arg_package );
__rhct_api void* __cdecl hashfile_sha256_mt( void* __arg_package );
__rhct_api void* __cdecl hashfile_sha384_mt( void* __arg_package );
__rhct_api void* __cdecl hashfile_sha512_mt( void* __arg_package );
#endif

#ifdef __cplusplus
}
#endif

#endif