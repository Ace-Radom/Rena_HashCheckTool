// Rena_HashCheckTool main function library

#ifndef _RHCT_H_
#define _RHCT_H_

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#ifdef USING_PTHREAD
#include<pthread.h>
#endif

#include"cps.h"
#include"hash.h"
#include"dirop.h"

#define ENUM_ERR                     1
#define TARGETDIR_EMPTY             -1
#define HASHLISTFILE_CREATION_ERROR -2

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    md5,
    sha1,
    sha224,
    sha256,
    sha384,
    sha512
} hash_type;

errno_t create_hash_list( PATH __dir , PATH __HashListFile , hash_type __type );
errno_t check_hash_list( PATH __dir );

#ifdef USING_PTHREAD
errno_t create_hash_list_mt( PATH __dir , PATH __HashListFile , hash_type __type , uint16_t threadsNUM );
errno_t check_hash_list_mt( PATH __dir , uint16_t threadsNUM );
#endif

#ifdef __cplusplus
}
#endif

#endif