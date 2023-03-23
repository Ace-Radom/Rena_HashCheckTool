#include"hash.h"

__rhct_api void __cdecl hashfile_md5( FILE* __f , char* __out ){
    unsigned char md[MD5_DIGEST_LENGTH];
    memset( md , '\0' , sizeof( md ) );
    MD5_CTX C;
    MD5_Init( &C );

#pragma region HASH

    unsigned char buf[MD5_BLOCK_SIZE];
    memset( buf , '\0' , sizeof( buf ) );
    while ( 1 )
    {
        int rFileLength = fread( buf , sizeof( unsigned char ) , MD5_BLOCK_SIZE , __f );
        if ( rFileLength == 0 )
        {
            break;
        }
        MD5_Update( &C , buf , rFileLength );
    }
    MD5_Final( md , &C );

#pragma endregion HASH

    for ( int i = 0 ; i < MD5_DIGEST_LENGTH ; i++ )
    {
        sprintf( &( __out[i*2] ) , "%02x" , ( unsigned char ) md[i] );
    }
    return;
}