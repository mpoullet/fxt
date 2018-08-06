
#include "comb/lyndon-words.h"

#include "comb/cyclic-words.h"

#include "fxtio.h"
#include "jjassert.h"
#include "fxttypes.h"
#include "nextarg.h"

//% All Lyndon words up to length n.  Duval's algorithm.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Lyndon words up to length n");
    ulong a = 0;
    NXARG(a, "First letter in the alphabet");
    ulong z = 1;
    NXARG(z, "Last letter in the alphabet");

    lyndon_words L(n, a, z);
#ifndef TIMING
    const ulong * x = L.data();
#endif

    ulong ct = 0;
    ulong i = L.first();
    do
    {
        ++ct;
#ifndef TIMING
        cout << setw(4) << ct << ":  ";
        for (ulong j=0; j<i; ++j)
        {
            cout << x[j];
            if ( j != i-1 )  cout << " ";
        }
        cout << endl;

        jjassert( 0 == cyclic_lex_min_idx( x, i ) );
#endif

    }
    while ( (i = L.next()) );

    cout << " ct = " << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 6.3.0:

 time ./bin 35 0 1
arg 1: 35 == n  [Lyndon words up to length n]  default=7
arg 2: 0 == a  [First letter in the alphabet]  default=0
arg 3: 1 == z  [Last letter in the alphabet]  default=1
 ct = 2025032004
./bin 35 0 1  3.95s user 0.00s system 99% cpu 3.956 total
 ==> 2025032004 / 3.95 == 512,666,330 per second

 time ./bin 22 0 2
arg 1: 22 == n  [Lyndon words up to length n]  default=7
arg 2: 0 == a  [First letter in the alphabet]  default=0
arg 3: 2 == z  [Last letter in the alphabet]  default=1
 ct = 2193322744
./bin 22 0 2  3.03s user 0.00s system 99% cpu 3.035 total
 ==> 2193322744 / 3.03 == 723,868,892 per second

 time ./bin 15 0 4
arg 1: 15 == n  [Lyndon words up to length n]  default=7
arg 2: 0 == a  [First letter in the alphabet]  default=0
arg 3: 4 == z  [Last letter in the alphabet]  default=1
 ct = 2590404239
./bin 15 0 4  3.12s user 0.00s system 99% cpu 3.119 total
 ==> 2590404239 / 3.12 == 830,257,768 per second

*/

/*
BENCHARGS=35 0 1
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/lyndon-words-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/lyndon-words-demo.cc DEMOFLAGS=-DTIMING"
/// End:

