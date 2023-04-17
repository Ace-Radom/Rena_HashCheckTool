#include"console_ext.h"

/**
 * @param __pbc  process bar char
 * @param __pbcl process bar char length
 */
__rhct_api void __cdecl print_process_bar( int __process , int __total , char* __pbc , int __pbcl ){
    double process_p = __process * 1.0 / __total; // procent
    int pbc_d = __pbcl * process_p; // process bar char needs to be displayed num

    if ( process_p < 0.1 )
    {
        printf( "[   " );
    }
    else if ( process_p < 1 )
    {
        printf( "[  " );
    }
    else
    {
        printf( "[ " );
    }
    printf( "%0.2f%%: " , process_p * 100 );
    for ( int i = 1 ; i <= __pbcl ; i++ )
    {
        if ( i <= pbc_d )
        {
            printf( __pbc );
        }
        else
        {
            printf( " " );
        }
    }
    printf( " ]" );
    return;
}