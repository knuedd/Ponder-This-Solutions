#ifndef CHECK_H
#define CHECK_H 


#define PROGRESS_STEP 10000000


/*
check if given number n can be expressed as n == a² + b² by 
using https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz
*/
bool check_quick_1( mpz_class n );
    
bool check_quick_1( mpz_class n ) {

    mpz_class m= n % 4;

    /*
    cerr << "        check_quick_1() " << n << " %4 == " << m  << " ... " << 
        ( (1==m) ?"true":"false" ) << endl;
    */

    return (1==m);
}

/*
check if given number n can be expressed as n == 2 * a² + b² by 
using https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz#Verwandte_Resultate
*/
bool check_quick_2( mpz_class n );

bool check_quick_2( mpz_class n ) {

    mpz_class m= n % 8;

    /*
    cerr << "        check_quick_2() " << n << " %8 == " << m << " ... " << 
        ( ((1==m)or(3==m))?"true":"false" ) << endl;
    */

    return (1==m) or (3==m);
}

/*
check if given number n can be expressed as n == 2 * a² + b² by 
using https://math.stackexchange.com/questions/3764866/the-diophantine-equation-m-x2-7y2 / 
https://www.amazon.co.uk/Primes-Form-ny2-Multiplication-Mathematics/dp/1118390180/

A prime number $m \ne 7$ can be written as $x^2 + 7y^2$ for $x,y$ integers
iff $m$ is one of these residues modulo $28$: $1, 9, 11, 15, 23, 25$

*/
bool check_quick_7( mpz_class n );

bool check_quick_7( mpz_class n ) {

    mpz_class m= n % 28;

    /*
    cerr << "        check_quick_7() " << n << " %28 == " << m << " ... " << 
        ( ( (1==m) or (9==m) or (11==m) or (15==m) or (23==m) or (25==m) )?"true":"false" ) << endl;
    */

    return (1==m) or (9==m) or (11==m) or (15==m) or (23==m) or (25==m);
}

/* 
check if given number n can be expressed as n == a**b + b**a any a,b \in [a_start,a_end]
*/
bool check_gen( mpz_class nn, uint64_t a_start, uint64_t a_end, mpz_class max_n, bool print= false );

bool check_gen( mpz_class nn, uint64_t a_start, uint64_t a_end, mpz_class max_n, bool print) {

    for ( auto a= a_start; a <= a_end; a++ ) {

        for ( auto b= a_start; b <= a ; b++ ) {
            
            mpz_class n1;
            mpz_ui_pow_ui(n1.get_mpz_t(), a, b);
            mpz_class n2;
            mpz_ui_pow_ui(n2.get_mpz_t(), b, a);

            mpz_class n= n1 + n2;

            if ( n == nn ) {

                if ( print ) {
                    cout << n << " == " << a << "**" << b << " + " << b << "**" << a << endl;
                }
                return true;
            }

            if ( n > max_n ) break; // abort inner loop
        }
    }

    return false;
}


/* 
check if given number n can be expressed as n == f * a² + b² for 
any a \in [a_start,a_end] by  testing many a, determine and print a and b when 'print' == true

- see much quicker versions for the test but not for the deconstruction in check_quick_1() below

- first case: n == f * a² + b² for a<b

*/
bool check_case_1( mpz_class n, uint64_t f, mpz_class a_start, mpz_class a_end, bool print= false );

bool check_case_1( mpz_class n, uint64_t f, mpz_class a_start, mpz_class a_end, bool print ) {

    //cerr << "        check(f=" << f << ") " << n << "\r";

    for ( mpz_class a= a_start; a <= a_end; a++ ) {

        if ( 0 == (a % PROGRESS_STEP) ) {
            cerr << "        progress " << (a-a_start) * 100.0 / (a_end-a_start) << 
                "%                                                            \r";
        }

        mpz_class aa= a;
        mpz_class r= n - f* aa*aa;

        if ( r < 1 ) break; /* don't need to go on here because following r would be even smaller */

        if ( 0 != mpz_perfect_square_p( r.get_mpz_t() ) ) {

            mpz_class sqrt;
            mpz_class remainder;
            mpz_sqrtrem( sqrt.get_mpz_t(), remainder.get_mpz_t(), r.get_mpz_t() ); // calculate sqrt and remainder in on go 

            if ( print ) {
                cout << n << " == " << f << " * " <<  a << "**2 + " << sqrt << "**2 (remainder " << remainder << ")" << endl;
            }
            return true;
        }

#if 0

#define AVOID_SOME_SQRT 1
#ifdef AVOID_SOME_SQRT

        mpz_class m= r % 16;

        /* 
        it can only by a square if n mod 15 \in {0, 1, 4, or 9}, 
        see https://www.johndcook.com/blog/2008/11/17/fast-way-to-test-whether-a-number-is-a-square/
        */
        if ( 9 < m ) continue;
        if ( ( 1 < m ) and ( m != 4 ) and ( m != 9 ) ) continue;
        
        /* if none of the above cases, we need to do a sqrt */

#endif /* AVOID_SOME_SQRT */

        mpz_class sqrt;
        mpz_class remainder;
        mpz_sqrtrem( sqrt.get_mpz_t(), remainder.get_mpz_t(), r.get_mpz_t() ); // calculate sqrt and remainder in on go 

        //cout << a << ": remainder " << r << "; mod 15 " << m << " sqrt " << sqrt << " remainder " << remainder << endl;

        if ( 0 == remainder ) {

            if ( print ) {
                cout << n << " == " << f << " * " <<  a << "**2 + " << sqrt << "**2" << endl;
            }
            return true;
        }

#endif /* 0 */

    }

    return false;
}



/* 
check if given number n can be expressed as n == f * a² + b² for 
any a \in [a_start,a_end] by  testing many a, determine and print a and b when 'print' == true

- see much quicker versions for the test but not for the deconstruction in check_quick_1() below
- first case: n == a² + f*b² for a<b

*/
bool check_case_2( mpz_class n, uint64_t f, mpz_class a_start, mpz_class a_end, bool print= false );

bool check_case_2( mpz_class n, uint64_t f, mpz_class a_start, mpz_class a_end, bool print ) {

    //cerr << "        check(f=" << f << ") " << n << "\r";

    /* don't do this case for f == 1 */
    if ( 1 == f ) {

        cerr << "... don't need to check this case" << endl;
        return false;
    }

    /* second case: n == a² + f * b² */
    for ( mpz_class a= a_start; a <= a_end; a++ ) {

        if ( 0 == (a % PROGRESS_STEP) ) {
            cerr << "        progress " << (a-a_start) * 100.0 / (a_end-a_start) << 
                "%                                                            \r";
        }

        mpz_class aa= a;
        mpz_class r= n - aa*aa;

        if ( r < 1 ) break; /* don't need to go on here because following r would be even smaller */

        /* if not divisible continue */
        if ( 0 == mpz_divisible_ui_p( r.get_mpz_t(), f ) ) continue;

#if 0
        /* divide remainder by f, is it divisible? */
        if (rr*f != r ) {

            //cout << "    failed: " << rr << " * " << f << " != " << r << endl;
            continue;
        }
#endif /* 0 */

        r= r / f;

        if ( 0 != mpz_perfect_square_p( r.get_mpz_t() ) ) {

            mpz_class sqrt;
            mpz_class remainder;
            mpz_sqrtrem( sqrt.get_mpz_t(), remainder.get_mpz_t(), r.get_mpz_t() ); // calculate sqrt and remainder in on go 

            if ( print ) {
                cout << n << " == " << f << " * " <<  a << "**2 + " << sqrt << "**2 (remainder " << remainder << ")" << endl;
            }
            return true;
        }

#if 0

#ifdef AVOID_SOME_SQRT

        mpz_class m= rr % 16;

        /* 
        it can only by a square if n mod 15 \in {0, 1, 4, or 9}, 
        see https://www.johndcook.com/blog/2008/11/17/fast-way-to-test-whether-a-number-is-a-square/
        */
        if ( 9 < m ) continue;
        if ( ( 1 < m ) and ( m != 4 ) and ( m != 9 ) ) continue;
        
        /* if none of the above cases, we need to do a sqrt */

#endif /* AVOID_SOME_SQRT */

        mpz_class sqrt;
        mpz_class remainder;
        mpz_sqrtrem( sqrt.get_mpz_t(), remainder.get_mpz_t(), r.get_mpz_t() ); // calculate sqrt and remainder in on go 

        //cout << a << ": remainder " << r << "; mod 15 " << m << " sqrt " << sqrt << " remainder " << remainder << endl;

        if ( 0 == remainder ) {
            if ( print ) {
                cout << n << " == " << a << "**2 + " << f << " * " << sqrt << "**2" << endl;
            }
            return true;
        }
#endif /* 0 */

    }
    return false;
}

/* 
check if given number n can be expressed as n == f * a² + b² or n == a² + f * b². Check both 
cases so that solution is found with smaller a or b already. 
Test a \in [a_start,a_end)

- see much quicker versions for the test but not for the deconstruction in check_quick_1()

*/
bool check_both_cases( mpz_class n, uint64_t f, uint64_t a_start, uint64_t a_end );

bool check_both_cases( mpz_class n, uint64_t f, mpz_class a_start, mpz_class a_end ) {

    for ( mpz_class a= a_start; a < a_end; a++ ) {

        mpz_class aa= a*a;
        mpz_class r1= n - f*aa;

        if ( ( r1 < 1)  ) break; /* don't need to go on here because following r would be even smaller */

        if ( 0 != mpz_perfect_square_p( r1.get_mpz_t() ) ) {

            mpz_class sqrt;
            mpz_class remainder;
            mpz_sqrtrem( sqrt.get_mpz_t(), remainder.get_mpz_t(), r1.get_mpz_t() ); // calculate sqrt and remainder in on go 

            cout << n << " == " << f << " * " <<  a << "**2 + " << sqrt << "**2 (remainder " << remainder << ")" << endl;
    
            return true;
        }

        mpz_class r2= n - aa;

        /* if not divisible continue */
        if ( 0 == mpz_divisible_ui_p( r2.get_mpz_t(), f ) ) continue;

        r2= r2 / f;

        if ( 0 != mpz_perfect_square_p( r2.get_mpz_t() ) ) {

            mpz_class sqrt;
            mpz_class remainder;
            mpz_sqrtrem( sqrt.get_mpz_t(), remainder.get_mpz_t(), r2.get_mpz_t() ); // calculate sqrt and remainder in on go 

            cout << n << " == " << f << " * " <<  a << "**2 + " << sqrt << "**2 (remainder " << remainder << ")" << endl;

            return true;
        }
    }

    return false;
}

#endif /* CHECK_H */
