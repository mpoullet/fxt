
#include "comb/composition-nz.h"
#include "comb/composition-nz-rank.h"

#include "comb/comb-print.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts.

// Cf. comb/composition-nz-rl-demo.cc for compositions in run-length order
// Cf. comb/composition-nz-subset-lex-demo.cc for compositions in subset-lex order

// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx
// Cf. comb/composition-nz-min-demo.cc for compositions into parts >= mi

// Cf. comb/composition-nz-left-smooth-demo.cc for left-smooth compositions
// Cf. comb/composition-nz-smooth-demo.cc for smooth compositions
// Cf. comb/composition-nz-max-demo.cc for compositions into parts <= mx

// Cf. comb/partition-asc-demo.cc for partitions as weakly ascending list of parts
// Cf. comb/partition-desc-demo.cc for partitions as weakly descending list of parts

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n");

    composition_nz P(n);
    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
#ifdef COMPOSITION_NZ_FIXARRAYS
    cout << "COMPOSITION_NZ_FIXARRAYS defined." << endl;
#endif
    if ( ! bq )
    {
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
//    ulong C[64];
    do
    {
        cout << setw(4) << ct << ":";

        const ulong r = P.rank();
        print_bin("  ", r, (n>1 ? n-1 : 1) );

//        cout << "[" << n-m << "]  ";  // OEIS sequence A000120
//        cout << " [" << setw(2) << P.last_part() << "] ";  // A001511
        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

#if 1  // increment ct below these tests
        jjassert( r == ct );
        P.unrank(r);  jjassert( r == P.rank() );
        jjassert( r == composition_nz_rank(P.data(), m) );
#endif

        jjassert( P.OK() );

        ++ct;
    }
    while ( (m=P.next()) );

#endif  // TIMING

    cout << " ct=" << ct << endl;  // A011782

    return 0;
}
// -------------------------


/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)
GCC 8.3.0

time ./bin 33 0
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_FIXARRAYS defined.
forward:
 ct=4294967296
./bin 33 0  9.37s user 0.00s system 99% cpu 9.379 total
 ==> 4294967296/9.37 == 458,374,311 per second

time ./bin 33 1
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_FIXARRAYS defined.
backward:
 ct=4294967296
./bin 33 1  5.35s user 0.00s system 99% cpu 5.349 total
 ==> 4294967296/5.35 == 802,797,625 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 33 0
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
  ct=4294967296
./bin 33 0  9.99s user 0.00s system 99% cpu 9.995 total
 ==> 4294967296/9.99 == 429,926,656 per second

 time ./bin 33 1
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
  ct=4294967296
./bin 33 1  15.26s user 0.00s system 99% cpu 15.261 total
 ==> 4294967296/15.26 == 281,452,640 per second


With COMPOSITION_NZ_FIXARRAYS defined:

 time ./bin 33 0
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_FIXARRAYS defined.
forward:
  ct=4294967296
./bin 33 0  7.24s user 0.00s system 99% cpu 7.246 total
 ==> 4294967296/7.24 == 593,227,527 per second

 time ./bin 33 1
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_FIXARRAYS defined.
backward:
  ct=4294967296
./bin 33 1  15.50s user 0.00s system 99% cpu 15.505 total
 ==> 4294967296/15.50 == 277,094,664 per second

*/

/*
BENCHARGS=33 0
BENCHARGS=33 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-demo.cc DEMOFLAGS=-DTIMING"
/// End:

