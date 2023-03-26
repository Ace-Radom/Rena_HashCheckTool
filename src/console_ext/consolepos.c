#include"console_ext.h"

__rhct_api int __cdecl wherex(){
    CONSOLE_SCREEN_BUFFER_INFO pBuf;
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ) , &pBuf );
    return pBuf.dwCursorPosition.X;
}

__rhct_api int __cdecl wherey(){
    CONSOLE_SCREEN_BUFFER_INFO pBuf;
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ) , &pBuf );
    return pBuf.dwCursorPosition.Y;
}

__rhct_api void __cdecl gotoxy( int __x , int __y ){
    COORD pos = { __x , __y };
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleCursorPosition( hOut , pos );
    return;
}

__rhct_api void __cdecl erase_output_chars( int __num ){
    for ( int i = 0 ; i < __num ; i++ )
    {
        printf( " " );
        // overlay output-ed chars
    }
    return;
}