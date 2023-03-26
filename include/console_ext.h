// console ext header

#ifndef _CONSOLE_EXT_H_
#define _CONSOLE_EXT_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

#include"cps.h"

#ifdef __cplusplus
extern "C" {
#endif

__rhct_api int __cdecl wherex();
__rhct_api int __cdecl wherey();
__rhct_api void __cdecl gotoxy( int __x , int __y );
__rhct_api void __cdecl erase_output_chars( int __num );

#ifdef __cplusplus
}
#endif

#endif