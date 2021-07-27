#include <iostream>
#include <fstream>
#include <stdint.h>
#include <math.h>
#include <string>

#include <gmp.h>
#include <gmpxx.h>

#include <omp.h>

using namespace std;

#include "check.h"
/* For a very large number n which assumed to be prime, deconstruct into a² + f * b² for f= 1, 2, 7 */

int main( int argc, char** argv ) {

    mpz_class N= 32993;
    if ( argc > 1 ) {
        
        N= mpz_class( argv[1], 10 );
    }

    uint64_t F= 1;
    if ( argc > 2 ) {

        F= atoll( argv[2] );
    }

    uint64_t MIN_X_Y= 0;
    if ( argc > 3 ) {

        MIN_X_Y= atoll( argv[3] );
    }



    mpz_class step= 1000000;

    if ( 1 == F ) {
        
        if ( ! check_quick_1( N ) ) {

            cerr << "N= " << N << " cannot be represented as a² + b²: " << endl;
            return 1;
        }

        mpz_class max_x_y= N/2;
        mpz_class sqrt;
        mpz_sqrt( sqrt.get_mpz_t(), max_x_y.get_mpz_t() );
        max_x_y= sqrt;

        cerr << "N= " << N << ", F= " << F << ", MAX_X_Y= " << max_x_y << endl;

        bool goon= true;
        mpz_class max_loop= ( max_x_y - MIN_X_Y ) / step;
        uint64_t max_loop_ui= mpz_get_ui(max_loop.get_mpz_t());

        #pragma omp parallel for
        for ( uint64_t i= 0; i < max_loop_ui; i++) {

            mpz_class start= MIN_X_Y + i*step;
            mpz_class end= ( MIN_X_Y + (i+1)*step < max_x_y ) ? MIN_X_Y + (i+1)*step : max_x_y;

            //cerr << "    step " << i << " - " << end << endl;
            if ( goon && check_both_cases( N, F, start, end ) ) {

                goon= false;
            }

            if ( 0 == omp_get_thread_num() ) {
                uint64_t nt= omp_get_num_threads();
                cerr << "        progress " << nt*i*100.0/max_loop_ui << "% with " << nt << " threads "
                    "                                                            \r";
            }
        }

        return 0;
    
    } else if ( 2 == F ) {
        
        if ( ! check_quick_2( N ) ) {

            cerr << "N= " << N << " cannot be represented as a² + 2b²: " << endl;
            return 1;
        }

        mpz_class max_x_y= N/3;
        mpz_class sqrt;
        mpz_sqrt( sqrt.get_mpz_t(), max_x_y.get_mpz_t() );
        max_x_y= sqrt;
        
        cerr << "N= " << N << ", F= " << F << ", MAX_X_Y= " << max_x_y << endl;

        bool goon= true;
        mpz_class max_loop= ( max_x_y - MIN_X_Y ) / step;
        uint64_t max_loop_ui= mpz_get_ui(max_loop.get_mpz_t());

        #pragma omp parallel for
        for ( uint64_t i= 0; i < max_loop_ui; i++) {

            mpz_class start= MIN_X_Y + i*step;
            mpz_class end= ( MIN_X_Y + (i+1)*step < max_x_y ) ? MIN_X_Y + (i+1)*step : max_x_y;

            //cerr << "    step " << i << " - " << end << endl;
            if ( goon && check_both_cases( N, F, start, end ) ) {

                goon= false;
            }

            if ( 0 == omp_get_thread_num() ) {
                uint64_t nt= omp_get_num_threads();
                cerr << "        progress " << nt*i*100.0/max_loop_ui << "% with " << nt << " threads "
                    "                                                            \r";
            }
        }

        return 0;

    } else if ( 7 == F ) {
        
        if ( ! check_quick_7( N ) ) {

            cerr << "N= " << N << " cannot be represented as a² + 7b²: " << endl;
            return 1;
        }

        mpz_class max_x_y= N/8;
        mpz_class sqrt;
        mpz_sqrt( sqrt.get_mpz_t(), max_x_y.get_mpz_t() );
        max_x_y= sqrt;
        
        cerr << "N= " << N << ", F= " << F << ", MAX_X_Y= " << max_x_y << endl;

        bool goon= true;
        mpz_class max_loop= ( max_x_y - MIN_X_Y ) / step;
        uint64_t max_loop_ui= mpz_get_ui(max_loop.get_mpz_t());

        #pragma omp parallel for
        for ( uint64_t i= 0; i < max_loop_ui; i++) {

            mpz_class start= MIN_X_Y + i*step;
            mpz_class end= ( MIN_X_Y + (i+1)*step < max_x_y ) ? MIN_X_Y + (i+1)*step : max_x_y;

            //cerr << "    step " << i << " - " << end << endl;
            if ( goon && check_both_cases( N, F, start, end ) ) {

                goon= false;
            }

            if ( 0 == omp_get_thread_num() ) {
                uint64_t nt= omp_get_num_threads();
                cerr << "        progress " << nt*i*100.0/max_loop_ui << "% with " << nt << " threads "
                    "                                                            \r";
            }
        }
 
        return 0;

    } else {

        check_gen( N, 0, 10000, N, /* print */ true );
        return 0;
    }

    return 3;
}
