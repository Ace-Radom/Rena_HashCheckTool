#include"dirop.h"

__rhct_api void __cdecl traverse_dir( const PATH __path , c_vector* __out ){
    intptr_t hFile = 0;
    struct _finddata_t FileInfo;
    char* pathName = ( char* ) malloc( MAX_PATH_LENGTH );
    strcpy( pathName , __path );
    strcat( pathName , "\\*" );
    if ( ( hFile = _findfirst( pathName , &FileInfo ) ) == -1 )
    {
        return;
    } // found no more

    do
    {
        if ( ( strcmp( FileInfo.name , "." ) != 0 ) && ( strcmp( FileInfo.name , ".." ) != 0 ) )
        {
            char* this_path = ( char* ) malloc( MAX_PATH_LENGTH );
            strcpy( this_path , __path );
            strcat( this_path , "\\" );
            strcat( this_path , FileInfo.name );
            // build current absolute path searched by this function

            if ( FileInfo.attrib & _A_SUBDIR )
            {
                traverse_dir( this_path , __out );
            }
            else
            {
                cv_push_back( __out , ( void* ) this_path );
            }
        }
    } while ( _findnext( hFile , &FileInfo ) == 0 );
    _findclose( hFile );
    return;
}