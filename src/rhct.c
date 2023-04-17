#include"rhct.h"

errno_t create_hash_list( PATH __dir , PATH __HashListFile , hash_type __type ){
    c_vector filelist;
    cv_init( &filelist , 10 );
    traverse_dir( __dir , &filelist );
    if ( cv_len( &filelist ) == 0 )
    {
#ifdef ENABLE_ERROUT
        fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): target dir \"%s\" doesn't contain files or accessing target dir error, stop\n" , __dir );
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

/** @note console ext part 
    long long filelist_length = cv_len( &filelist );
    long long file_finishedcheck_NUM = 0;
    printf( "Total %d files collected\n" , filelist_length );
    int pb_x = wherex() + 2;
    int pb_y = wherey();
*/

    while ( cv_len( &filelist ) > 0 )
    {
/** @note console ext part 
        gotoxy( pb_x , pb_y );
        print_process_bar( file_finishedcheck_NUM , filelist_length , PROCESSBAR_CHAR , PROCESSBAR_LENGTH );
        printf( "\n" );
        fflush( stdout );
        // refresh process bar
*/

        char* hash = ( char* ) malloc( SHA512_DIGEST_LENGTH );
        // use the langest output length of all hash function
        char* this_file = ( char* ) malloc( MAX_PATH_LENGTH );
        strcpy( this_file , ( char* ) filelist.items[0] );

/** @note console ext part 
        printf( "Finished checking %d files, total %d files\n" , file_finishedcheck_NUM , filelist_length );
        // checked file num output
*/

        FILE* f = fopen( this_file , "rb" );
        if ( f == NULL )
        {
#ifdef ENABLE_ERROUT
            fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): cannot open file \"%s\", skip\n" , this_file );
#endif
            fclose( f );
            free( hash );
            free( this_file );
            cv_pop_front( &filelist );
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
                fprintf( stderr , "[rhct lib] -> create_hash_list(PATH,PATH,hash_type): enum type error, stop\n" );
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
/** @note console ext part 
        file_finishedcheck_NUM++;
*/
    }

/** @note console ext part 
    gotoxy( pb_x , pb_y );
    print_process_bar( file_finishedcheck_NUM , filelist_length , PROCESSBAR_CHAR , PROCESSBAR_LENGTH );
    printf( "\n" );
    fflush( stdout );
    // refresh process bar (100% display)
*/

    fclose( hashlist );
    cv_clean( &filelist );
    return 0;
}

#ifdef USING_PTHREAD

errno_t create_hash_list_mt( PATH __dir , PATH __HashListFile , hash_type __type , uint16_t threadsNUM ){
    c_vector filelist;
    cv_init( &filelist , 10 );
    traverse_dir( __dir , &filelist );
    if ( cv_len( &filelist ) == 0 )
    {
#ifdef ENABLE_ERROUT
        fprintf( stderr , "[rhct lib] -> create_hash_list_mt(PATH,PATH,hash_type,uint16_t): target dir \"%s\" doesn't contain files or accessing target dir error, stop\n" , __dir );
#endif
        cv_clean( &filelist );
        return TARGETDIR_EMPTY;
    } // no files in target dir
    
    FILE* hashlist = fopen( __HashListFile , "w+" );
    if ( hashlist == NULL )
    {
#ifdef ENABLE_ERROUT
        fprintf( stderr , "[rhct lib] -> create_hash_list_mt(PATH,PATH,hash_type,uint16_t): cannot open or create hashlist \"%s\", stop\n" , __HashListFile );
#endif
        cv_clean( &filelist );
        fclose( hashlist );
        return HASHLISTFILE_CREATION_ERROR;
    } // cannot open / create hashlist

#pragma region MULTI_THREADS

    while ( cv_len( &filelist ) > 0 )
    {
        uint16_t threadsNUM_this_turn;
        if ( cv_len( &filelist ) >= threadsNUM )
        {
            threadsNUM_this_turn = threadsNUM;
        }
        else
        {
            threadsNUM_this_turn = cv_len( &filelist );
        }
        // check how much threads can be started in this turn

        pthread_t threads[threadsNUM_this_turn];
        hashfile_arg_package args[threadsNUM_this_turn];
        errno_t rc;

        for ( int i = 0 ; i < threadsNUM_this_turn ; i++ )
        {
            char* this_file = ( char* ) malloc( MAX_PATH_LENGTH );
            strcpy( this_file , ( char* ) filelist.items[i] );
            args[i].f = fopen( this_file , "rb" );
            if ( args[i].f == NULL )
            {
#ifdef ENABLE_ERROUT
                fprintf( stderr , "[rhct lib] -> create_hash_list_mt(PATH,PATH,hash_type,uint16_t): cannot open file \"%s\", skip\n" , this_file );
#endif
                fclose( args[i].f );
                free( this_file );
                cv_pop_front( &filelist );
                continue;
            }
            args[i].out = ( char* ) malloc( SHA512_DIGEST_LENGTH );
            // use the langest output length of all hash function

            switch ( __type )
            {
                case md5:    rc = pthread_create( &threads[i] , NULL , hashfile_md5_mt , &args[i] );    break;
                case sha1:   rc = pthread_create( &threads[i] , NULL , hashfile_sha1_mt , &args[i] );   break;
                case sha224: rc = pthread_create( &threads[i] , NULL , hashfile_sha224_mt , &args[i] ); break; 
                case sha256: rc = pthread_create( &threads[i] , NULL , hashfile_sha256_mt , &args[i] ); break;
                case sha384: rc = pthread_create( &threads[i] , NULL , hashfile_sha384_mt , &args[i] ); break;
                case sha512: rc = pthread_create( &threads[i] , NULL , hashfile_sha512_mt , &args[i] ); break;

                default:
                    #ifdef ENABLE_ERROUT
                    fprintf( stderr , "[rhct lib] -> create_hash_list_mt(PATH,PATH,hash_type,uint16_t): enum type error, stop\n" );
                    #endif
                    return ENUM_ERR;
                    break;
            }

            if ( rc )
            {
#ifdef ENABLE_ERROUT
                fprintf( stderr , "[rhct lib] -> create_hash_list_mt(PATH,PATH,hash_type,uint16_t): thread creation at file \"%s\" failed, return code of pthread function pthread_create is %d\n" , this_file , rc );
#endif
                free( this_file );
                continue;
            } // thread create failed

            free( this_file );
        } // start each threads

        for ( int i = 0 ; i < threadsNUM_this_turn ; i++ )
        {
            char* this_file = ( char* ) malloc( MAX_PATH_LENGTH );
            strcpy( this_file , ( char* ) filelist.items[i] );
            rc = pthread_join( threads[i] , NULL );

            if ( rc )
            {
#ifdef ENABLE_ERROUT
                fprintf( stderr , "[rhct lib] -> create_hash_list_mt(PATH,PATH,hash_type,uint16_t): thread join at file %s failed, return code of pthread function pthread_join is %d\n" , this_file , rc );
#endif
                fclose( args[i].f );
                free( args[i].out );
                free( this_file );
                continue;
            } // thread joid failed

//          printf( "%s %s\n" , args[i].out , ( char* ) filelist.items[i] );
            fprintf( hashlist , "%s %s\n" , args[i].out , this_file );
            fclose( args[i].f );
            free( args[i].out );
            free( this_file );
        } // join threads and get results

        for ( int i = 0 ; i < threadsNUM_this_turn ; i++ )
        {
            cv_pop_front( &filelist );
        } // filelist pop
    }

#pragma endregion MULTI_THREADS

    fclose( hashlist );
    cv_clean( &filelist );
    return 0;
}

#endif