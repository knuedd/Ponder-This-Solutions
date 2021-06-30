#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


uint8_t* mem;


uint8_t ispromising( uint8_t num, uint8_t* line, uint32_t LEN ) {

    /* test if for all num <*/
    for ( int l= num; l > 0; l-- ) {

        uint8_t fit= 0;
        for ( int i= 0; i+l+1 < LEN; i++ ) {

            if ( 0 == line[i] && 0 == line[i+l+1] ) fit++;
        }
        if ( 0 == fit ) return 0;
    }

    return 1;
}


void printline( uint8_t* line, uint32_t LEN ) {

    for ( int i= 0; i < LEN; i++ ) {

        if ( 0 != line[i] ) {
            printf( "%2u:", line[i] );
        } else {
            printf( "  :" );
        }
    }
}


void printabc( uint8_t* line, uint32_t LEN ) {

    for ( int i= 0; i < LEN; i++ ) {

        if ( 0 == line[i] ) {
            printf( "-" );
        } else if ( 26 >= line[i] ) {
            printf( "%c", line[i]+'A'-1 );
        } else if ( 2*26 >= line[i] ) {
            printf( "%c", line[i]-26+'a'-1 );
        } else {
            printf( "*" );
        }
    }
}


void backtrack( uint8_t num, uint8_t* line, uint32_t LEN ) {

    if ( 0 == num ) {

        //printf( "Solution " );
        //printline( line, LEN );
        //printf( "    " );
        printabc( line, LEN );
        printf( "\n" );
        return;
    }

    uint8_t* newline= line+LEN;

    for ( int i= 0; i+num+1 < LEN; i++ ) {

        if ( 0 == line[i] && 0 == line[i+num+1] ) {

            memcpy( newline, line, LEN );
            newline[i]= num;
            newline[i+num+1]= num;

            if ( ispromising( num-1, newline, LEN ) ) {

                backtrack( num-1, newline, LEN );
            }
        }
    }
}


void backtrack_outer( uint8_t num, uint8_t* line, uint32_t LEN ) {

    uint8_t* newline= line+LEN;

    for ( int i= 0; i+num+1 < LEN; i++ ) {

        //printf( "%u/%u\n", i, LEN-num-1 );

        if ( 0 == line[i] && 0 == line[i+num+1] ) {

            memcpy( newline, line, LEN );
            newline[i]= num;
            newline[i+num+1]= num;

            if ( ispromising( num-1, newline, LEN ) ) {

                backtrack( num-1, newline, LEN );
            }
        }
    }
}


int main( int argc, char** argv ) {

    uint32_t N= 26;

    if ( 1 < argc ) {

        N= atoi( argv[1] );
    }
    fprintf( stderr, "N= %u\n", N );

    uint32_t LEN= 2*N+1;
    //uint32_t LEN= 2*N;

    mem= (uint8_t*) calloc( LEN*(N+1), sizeof(uint8_t) );

    backtrack_outer( N, mem, LEN );

    return 0;
}
