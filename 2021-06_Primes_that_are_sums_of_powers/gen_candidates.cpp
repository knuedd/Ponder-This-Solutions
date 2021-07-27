#include <iostream>
#include <stdint.h>
#include <math.h>
#include <string>

#include <gmp.h>
#include <gmpxx.h>

using namespace std;

#include "check.h"


/* 
generate numbers of the form n == a**b + b**a for a,b \in [a_start,a_end] as long as n <= max_n
*/
void gen( uint64_t a_start, uint64_t a_end, mpz_class max_n ) {

    for ( auto a= a_start; a <= a_end; a++ ) {

        // cerr << "gen outer loop " << a << endl;

        for ( auto b= a_start; b <= a ; b++ ) {
            
            mpz_class n1;
            mpz_ui_pow_ui(n1.get_mpz_t(), a, b);
            mpz_class n2;
            mpz_ui_pow_ui(n2.get_mpz_t(), b, a);

            mpz_class n= n1 + n2;

            if ( n > max_n ) break; // abort inner loop

            // check if prime
            if ( mpz_probab_prime_p ( n.get_mpz_t(), 50 ) < 1 ) continue;

            // check if it can be constructed as x² + k*y² without solving it 
            if ( ! check_quick_1( n ) ) continue; // if ( ! check( p, 1, 0, MAX_X_Y ) ) continue;
            if ( ! check_quick_2( n ) ) continue; // if ( ! check( p, 2, 0, MAX_X_Y ) ) continue;
            if ( ! check_quick_7( n ) ) continue; // if ( ! check( p, 7, 0, MAX_X_Y ) ) continue;

            cout << n << endl;
        }
    }
}

int main( int argc, char** argv ) {


    uint64_t MAX_A_B= 10;
    if ( argc > 1 ) {

        MAX_A_B= atoll( argv[1] );
    }

    uint64_t MAX_EXP= 110;
    if ( argc > 2 ) {

        MAX_EXP= atoll( argv[2] );
    }

    /* maximum n, ignore larger ones */
    mpz_class MAX_N= 1000;
    mpz_ui_pow_ui( MAX_N.get_mpz_t(), 10, MAX_EXP );

    gen( 2, MAX_A_B, MAX_N );

    return 0;
}
