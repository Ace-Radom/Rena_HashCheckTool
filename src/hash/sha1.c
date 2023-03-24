#include"hash.h"

__rhct_api void __cdecl hashstr_sha1( unsigned const char* __str , char* __out ){
    if ( !__str )
    {
        return;
    }
    unsigned char md[SHA_DIGEST_LENGTH];
    memset( md , '\0' , sizeof( md ) );
    SHA1( __str , strlen( __str ) , md );
    for ( int i = 0 ; i < SHA_DIGEST_LENGTH ; i++ )
    {
        sprintf( &( __out[i*2] ) , "%02x" , ( unsigned char ) md[i] );
    }
    return;
}

__rhct_api void __cdecl hashfile_sha1( FILE* __f , char* __out ){
    unsigned char md[SHA_DIGEST_LENGTH];
    memset( md , '\0' , sizeof( md ) );
    SHA_CTX C;
    SHA1_Init( &C );

#pragma region HASH

    unsigned char buf[HASH_BLOCK_SIZE];
    memset( buf , '\0' , sizeof( buf ) );
    while ( 1 )
    {
        int rFileLength = fread( buf , sizeof( unsigned char ) , HASH_BLOCK_SIZE , __f );
        if ( rFileLength == 0 )
        {
            break;
        }
        SHA1_Update( &C , buf , rFileLength );
    }
    SHA1_Final( md , &C );

#pragma endregion HASH

    for ( int i = 0 ; i < SHA_DIGEST_LENGTH ; i++ )
    {
        sprintf( &( __out[i*2] ) , "%02x" , ( unsigned char ) md[i] );
    }
    OPENSSL_cleanse( &C , sizeof( C ) );
}