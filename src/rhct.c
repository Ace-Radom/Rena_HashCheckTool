#include"rhct.h"

errno_t create_hash_list( PATH __dir , PATH __HashListFile , hash_type __type ){
    c_vector filelist;
    cv_init( &filelist , 10 );
    traverse_dir( __dir , &filelist );
    if ( cv_len( &filelist ) == 0 )
    {
#ifdef ENABLE_ERROUT
        fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): target dir \"%s\" doesn't contain files or accessing target dir error, stop" , __dir );
#endif
        cv_clean( &filelist );
        return TARGETDIR_EMPTY;
    } // no files in target dir
    
    FILE* hashlist = fopen( __HashListFile , "w+" );
    if ( hashlist == NULL )
    {
#ifdef ENABLE_ERROUT
        fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): cannot open or create hashlist \"%s\", stop\n" , __HashListFile );
#endif
        cv_clean( &filelist );
        fclose( hashlist );
        return HASHLISTFILE_CREATION_ERROR;
    } // cannot open / create hashlist

#ifdef USING_PTHREAD

    pthread_t threads[THREADS_NUM];

#else

    while ( cv_len( &filelist ) > 0 )
    {
        char* hash = ( char* ) malloc( SHA512_DIGEST_LENGTH );
        // use the langest output length of all hash function
        char* this_file = ( char* ) malloc( MAX_PATH_LENGTH );
        strcpy( this_file , ( char* ) filelist.items[0] );
        FILE* f = fopen( this_file , "rb" );
        if ( f == NULL )
        {
#ifdef ENABLE_ERROUT
            fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): cannot open file \"%s\", skip" , this_file );
#endif
            continue;
        }
        
        switch ( __type )
        {
            case md5:    hashfile_md5( f , hash );    break;
            case sha1:   hashfile_sha1( f , hash );   break;
            case sha224: hashfile_sha224( f , hash ); break; 
            case sha256: hashfile_sha256( f , hash ); break;
            case sha384: hashfile_sha384( f , hash ); break;
            case sha512: hashfile_sha512( f , hash ); break;

            default:
                #ifdef ENABLE_ERROUT
                fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): enum type error, stop" );
                #endif
                return ENUM_ERR;
                break;
        }

//      printf( "%s %s\n" , hash , this_file );
        fprintf( hashlist , "%s %s\n" , hash , this_file );
        fclose( f );
        free( hash );
        free( this_file );
        cv_pop_front( &filelist );
    }

#endif

    fclose( hashlist );
    cv_clean( &filelist );

}