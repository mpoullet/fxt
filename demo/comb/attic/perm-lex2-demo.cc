
#include "comb/perm-lex2.h"

#include "comb/comb-print.h"

#include "comb/fact2perm.h"
#include "perm/perminvert.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"


//% Generate all permutations in lexicographic order

// Cf. comb/perm-lex-inv-demo.cc for an algorithm also giving inverse permutations

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements, n>=2.");
#ifdef PERM_LEX2_OPT
    jjassert( n>=2 );
#else
    jjassert( n>=1 );
#endif

    perm_lex2 P(n);

    ulong ct = 0;
#ifdef TIMING

#ifdef PERM_LEX2_FIXARRAYS
    cout << "PERM_LEX2_FIXARRAYS is defined." << endl;
#endif
#ifdef PERM_LEX2_OPT
        cout << "PERM_LEX2_OPT is defined." << endl;
#endif

    do { ++ct; }  while ( P.next() );

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros
    const ulong *x = P.data();
    const ulong *d = P.d_;
    ulong *ix = new ulong[n];  // inverse permutations
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        print_perm("    ", x, n, dfz);
        print_mixedradix("    ", d, n-1, dfz);

        make_inverse(x, ix, n);
        print_perm("    ", ix, n, dfz);

        cout << endl;
    }
    while ( P.next() );

    delete [] ix;
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)

GCC 8.3.0

time ./bin 13
arg 1: 13 == n  [Permutations of n elements, n>=2.]  default=4
PERM_LEX2_FIXARRAYS is defined.
PERM_LEX2_OPT is defined.
 ct=6227020800
./bin 13  5.53s user 0.00s system 99% cpu 5.530 total
 ==> 13!/5.53 == 1,126,043,544 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements, n>=2.]  default=4
PERM_LEX2_FIXARRAYS is defined.
PERM_LEX2_OPT is defined.
  ct=479001600
./bin 12  1.11s user 0.00s system 99% cpu 1.113 total
 ==> 12!/1.11 == 431,532,972 per second

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements, n>=2.]  default=4
PERM_LEX2_OPT is defined.
  ct=479001600
./bin 12  1.72s user 0.00s system 99% cpu 1.721 total
 ==> 12!/1.72 == 278,489,302 per second

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements, n>=2.]  default=4
PERM_LEX2_FIXARRAYS is defined.
  ct=479001600
./bin 12  1.43s user 0.00s system 99% cpu 1.438 total
 ==> 12!/1.43 == 334,966,153 per second

 time ./bin 12
arg 1: 12 == n  [Permutations of n elements, n>=2.]  default=4
  ct=479001600
./bin 12  2.46s user 0.00s system 99% cpu 2.462 total
 ==> 12!/2.46 == 194,716,097 per second

*/

/*
BENCHARGS=13
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-lex2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-lex2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

