#include"hash.h"

__rhct_api void __cdecl hashstr_sha256( unsigned const char* __str , char* __out ){
    if ( !__str )
    {
        return;
    }
    unsigned char md[SHA256_DIGEST_LENGTH];
    memset( md , '\0' , sizeof( md ) );
    SHA256( __str , strlen( __str ) , md );
    for ( int i = 0 ; i < SHA256_DIGEST_LENGTH ; i++ )
    {
        sprintf( &( __out[i*2] ) , "%02x" , ( unsigned char ) md[i] );
    }
    return;
}

__rhct_api void __cdecl hashfile_sha256( FILE* __f , char* __out ){
    unsigned char md[SHA256_DIGEST_LENGTH];
    memset( md , '\0' , sizeof( md ) );
    SHA256_CTX C;
    SHA256_Init( &C );

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
        SHA256_Update( &C , buf , rFileLength );
    }
    SHA256_Final( md , &C );

#pragma endregion HASH

    for ( int i = 0 ; i < SHA256_DIGEST_LENGTH ; i++ )
    {
        sprintf( &( __out[i*2] ) , "%02x" , ( unsigned char ) md[i] );
    }
    OPENSSL_cleanse( &C , sizeof( C ) );
    return;
}