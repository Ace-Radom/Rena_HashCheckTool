// dir operation header

#ifndef _DIROP_H_
#define _DIROP_H_

#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include"cps.h"
#include"cvector.h"

#ifdef __cplusplus
extern "C" {
#endif

__rhct_api void __cdecl traverse_dir( const PATH __path , c_vector* __out );

#ifdef __cplusplus
}
#endif

#endif