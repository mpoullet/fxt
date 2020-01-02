
#include "comb/composition-nz-subset-lex.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"
#include "bits/print-bin.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts, subset-lex order.
//% Loopless generation.
//% See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//%   http://arxiv.org/abs/1405.6503

// Cf. comb/composition-nz-demo.cc for compositions into positive parts.
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

    composition_nz_subset_lex P(n);

    ulong ct = 0;

#ifdef TIMING
    bool bq = 0;
    NXARG(bq, "With benchmark: whether to generate in backward order");
#ifdef COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS
    cout << "COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined." << endl;
#endif
    if ( !bq )
    {
#ifdef COMPOSITION_NZ_SUBSET_LEX_NEXT_A
        cout << "next() version A." << endl;
#else
        cout << "next() version B." << endl;
#endif
        cout << "forward:" << endl;
        P.first();
        do  { ++ct; }  while ( P.next() );
    }
    else
    {
#ifdef COMPOSITION_NZ_SUBSET_LEX_PREV_A
        cout << "prev() version A." << endl;
#else
        cout << "prev() version B." << endl;
#endif
        cout << "backward:" << endl;
        P.last();
        do  { ++ct; }  while ( P.prev() );
    }

#else  // TIMING


    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    ulong m = P.num_parts();
    do
    {
//        cout << P.last_part() << ",";  continue;  // A082850 (with backward order)
//        cout << m-1 << ",";  continue;  // A100661 (with backward order)

        cout << setw(4) << ct << ":";

        cout << "  [" << setw(2) << m << "]";

        ulong r = composition_nz_rank(P.data(), m);
        r = ~r;
        r &= (1UL<<n) - 1;
        print_bin("  ", r, (n>1 ? n-1 : 1));

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            P.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( P.OK() );
#if 1  // check rank/unrank
        ulong mx = P.unrank(ct);
        jjassert( P.OK() );
        jjassert( m == mx );
        jjassert( ct == P.rank() );
#endif
        ++ct;

    }
    while ( (m=P.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)
GCC 8.3.0

time ./bin 33 0
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
next() version A.
forward:
 ct=4294967296
./bin 33 0  4.56s user 0.00s system 99% cpu 4.559 total
 ==> 4294967296 / 4.56 == 941,878,792 per second

time ./bin 33 1
arg 1: 33 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
prev() version A.
backward:
 ct=4294967296
./bin 33 1  3.90s user 0.00s system 99% cpu 3.899 total
 ==> 4294967296 / 3.90 == 1,101,273,665 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
  ct=2147483648
./bin 32 0  4.18s user 0.00s system 99% cpu 4.185 total
 ==> 2147483648/4.18 == 513,752,068 per second

 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
forward:
  ct=2147483648
./bin 32 0  4.17s user 0.00s system 99% cpu 4.170 total
 ==> 2147483648/4.17 == 514,984,088 per second



 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
  ct=2147483648
./bin 32 1  4.37s user 0.00s system 99% cpu 4.376 total
 ==> 2147483648/4.37 == 491,415,022 per second


 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
backward:
  ct=2147483648
./bin 32 1  3.86s user 0.00s system 99% cpu 3.866 total
 ==> 2147483648/3.86 == 556,342,913 per second



GCC 4.8.0:

implementation version A (in next() and previous()):


 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
next() version A.
forward:
 ct=2147483648
./bin 32 0  3.64s user 0.00s system 99% cpu 3.640 total
 ==> 2147483648/3.64 == 589,968,035 per second

 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
prev() version A.
backward:
 ct=2147483648
./bin 32 1  5.17s user 0.00s system 99% cpu 5.170 total
 ==> 2147483648/5.17 == 415,374,013 per second


 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
next() version A.
forward:
 ct=2147483648
./bin 32 0  3.92s user 0.00s system 99% cpu 3.925 total
 time ./bin 32 1
 ==> 2147483648/3.92 == 547,827,461 per second

arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
prev() version A.
backward:
 ct=2147483648
./bin 32 1  3.87s user 0.00s system 99% cpu 3.868 total
 ==> 2147483648/3.87 == 554,905,335 per second


implementation version B (in next() and previous()):


 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
next() version B.
forward:
 ct=2147483648
./bin 32 0  3.02s user 0.00s system 99% cpu 3.025 total
 ==> 2147483648/3.02 == 711,087,300 per second

 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
prev() version B.
backward:
 ct=2147483648
./bin 32 1  4.31s user 0.00s system 99% cpu 4.308 total
 ==> 2147483648/4.31 == 498,256,066 per second

 time ./bin 32 0
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
next() version B.
forward:
 ct=2147483648
./bin 32 0  3.90s user 0.00s system 99% cpu 3.907 total
 ==> 2147483648/3.90 == 550,636,832 per second

 time ./bin 32 1
arg 1: 32 == n  [compositions of n]  default=7
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS defined.
prev() version B.
backward:
 ct=2147483648
./bin 32 1  3.78s user 0.00s system 99% cpu 3.786 total
 ==> 2147483648/3.78 == 568,117,367 per second

*/

/*
BENCHARGS=32 0
BENCHARGS=32 1
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-subset-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-subset-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

