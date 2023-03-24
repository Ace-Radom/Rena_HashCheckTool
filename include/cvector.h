#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#include"cps.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    long long cap;  // capacity
    long long len;  // length
    void** items;   // items
} c_vector;

__rhct_api void __cdecl cv_init( c_vector* __v , long long __cap );
__rhct_api void __cdecl cv_resize( c_vector* __v , long long __cap );
__rhct_api void __cdecl cv_push_front( c_vector* __v , void* __item );
__rhct_api void __cdecl cv_push_back( c_vector* __v , void* __item );
__rhct_api void* __cdecl cv_pop_front( c_vector* __v );
__rhct_api void* __cdecl cv_pop_back( c_vector* __v );
__rhct_api void __cdecl cv_insert( c_vector* __v , void* __item , long long __pos );
__rhct_api void* __cdecl cv_delete( c_vector* __v , long long __pos );
__rhct_api void __cdecl cv_clean( c_vector* __v );
__rhct_api long long __cdecl cv_len( c_vector* __v );

__rhct_api void __cdecl cv_print_int( c_vector* __v );
__rhct_api void __cdecl cv_print_str( c_vector* __v );

#ifdef __cplusplus
}
#endif

#endif // _CVECTOR_H_