
#include "comb/partition-asc.h"

#include "comb/partition-conj.h"
#include "comb/print-partition-conj.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Integer partitions as weakly ascending list of parts.
//% Lexicographic order.
//% Cf. OEIS sequence A000041.

// Cf. comb/partition-desc-demo.cc for partitions as weakly descending lists
// Cf. comb/partition-asc-subset-lex-demo.cc for partitions in subset-lex order
// Cf. comb/partition-dist-asc-demo.cc for partitions into distinct parts
// Cf. comb/partition-odd-asc-demo.cc for partitions into odd parts
// Cf. comb/mpartition-demo.cc for partitions into m parts
// Cf. comb/partition-demo.cc for partitions given as multiplicities of parts
// Cf. comb/composition-nz-demo.cc for all compositions as list of parts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 11;
    NXARG(n, "integer partitions of n");

    partition_asc P(n);

    ulong ct = 0;

#ifdef TIMING
#ifdef PARTITION_ASC_FIXARRAYS
    cout << "PARTITION_ASC_FIXARRAYS is defined" << endl;
#endif
    bool bq = false;
    NXARG(bq, "With benchmark: whether to generate in backward order");
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
    do
    {
        ++ct;

#if 1  // allow/suppress printing

        cout << setw(4) << ct << ": ";

//        { ulong j=m; do { --j; cout << " " << x[j]; } while (j); }  // weakly descending list
        cout << " [" << setw(2) << m << "] ";
//        cout << " d=" << setw(2) << P.durfee_n() << " ";

//        cout << " [" << setw(2) << n-m << "] ";  // A218829 (recycled)
//        cout << " [" << setw(2) << P.data()[m-1] << "] ";  // A218735 (recycled)

        P.print("  ");

//        print_partition_asc_conj("    ", P.data(), m);

        if ( aa )  // ASCII art
        {
            P.print_aa();
//            P.print_conj_aa();
            cout << endl;
            cout << endl;
        }

        cout << endl;

        jjassert( P.OK() );
#endif  // allow/suppress printing
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

time ./bin 115 0
arg 1: 115 == n  [integer partitions of n]  default=11
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=1064144451
./bin 115 0  2.45s user 0.00s system 99% cpu 2.449 total
 ==> 1064144451 / 2.45 == 434,344,673 per second

time ./bin 115 1
arg 1: 115 == n  [integer partitions of n]  default=11
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=1064144451
./bin 115 1  2.48s user 0.00s system 99% cpu 2.478 total
 ==> 1064144451 / 2.48 == 429,090,504 per second

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.5.0:
 time ./bin 110
arg 1: 110 == n  [integer partitions of n]  default=10
  ct=607163746
./bin 110  3.39s user 0.00s system 99% cpu 3.389 total
 ==> 607163746/3.39 == 179,104,349 per second


GCC 4.8.0:

 time ./bin 110 0
arg 1: 110 == n  [integer partitions of n]  default=10
arg 2: 0 == bq  [With benchmark: whether to generate in backward order]  default=0
forward:
 ct=607163746
./bin 110  2.80s user 0.00s system 99% cpu 2.805 total
 ==> 607163746/2.80 == 216,844,195 per second

 time ./bin 110 1
arg 1: 110 == n  [integer partitions of n]  default=10
arg 2: 1 == bq  [With benchmark: whether to generate in backward order]  default=0
backward:
 ct=607163746
./bin 110 1  2.90s user 0.00s system 99% cpu 2.903 total
 ==> 607163746/2.90 == 209,366,808 per second

*/

/*
BENCHARGS=110
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-asc-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-asc-demo.cc DEMOFLAGS=-DTIMING"
/// End:

