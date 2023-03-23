#include"hash.h"

int main(){
    char out[16];
    FILE* fp = NULL;
    fp = fopen( "D:/texlive2022.iso" , "rb" );
    if ( fp == NULL )
    {
        printf( "error" );
        return 0;
    }
    hashfile_md5( fp , &out );
    printf( "%s\n" , out );
}