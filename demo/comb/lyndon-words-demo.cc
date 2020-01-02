
#include "comb/lyndon-words.h"

#include "comb/cyclic-words.h"

#include "fxtio.h"
#include "jjassert.h"
#include "fxttypes.h"
#include "nextarg.h"

//% All Lyndon words up to length n.  Duval's algorithm.

// Cf. comb/lyndon-words-restrpref-demo.cc

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
    ulong q = 0;
    NXARG(q, "0 ==> show all, 1 ==> only necklaces, 2 ==> only Lyndon words");

    lyndon_words L(n, a, z);
#ifdef TIMING
#else
    const ulong * x = L.data_1();  // one-based
#endif

    ulong ct = 0;
#ifdef TIMING
    do { ++ct; } while ( 0 != L.next() );

#else  // TIMING
    ulong i = L.first();
    do
    {
        if ( ( q >= 2 ) && ! L.is_lyndon_word() )  continue;
        if ( ( q == 1 ) && ! L.is_necklace() )  continue;

        ++ct;
        cout << setw(4) << ct << ":  ";
        for (ulong j=1; j<=i; ++j)
        {
            cout << x[j];
            if ( j != i )  cout << " ";
        }
#if 0  // print trailing part as well:
        cout << ".";  // separator
        for (ulong j=i+1; j<=n; ++j)
        {
            cout << x[j];
            if ( j != n )  cout << " ";
        }
#endif
        cout << endl;

        jjassert( 0 == cyclic_lex_min_idx( L.data_0(), i ) );
    }
    while ( (i = L.next()) );
#endif  // TIMING

    cout << " ct = " << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)
GCC 8.3.0


time ./bin 35 0 1
 ct = 2025032004
./bin 35 0 1  2.97s user 0.00s system 99% cpu 2.973 total
 ==> 2025032004 / 2.97 == 681,828,957 per second

time ./bin 22 0 2
 ct = 2193322744
./bin 22 0 2  2.32s user 0.00s system 99% cpu 2.322 total
 ==> 2193322744 / 2.32 == 945,397,734 per second

time ./bin 15 0 4
 ct = 2590404239
./bin 15 0 4  2.42s user 0.00s system 99% cpu 2.422 total
 ==> 2590404239 / 2.42 == 1,070,414,974 per second


Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)
GCC 6.3.0:

 time ./bin 35 0 1
 ct = 2025032004
./bin 35 0 1  3.95s user 0.00s system 99% cpu 3.956 total
 ==> 2025032004 / 3.95 == 512,666,330 per second

 time ./bin 22 0 2
 ct = 2193322744
./bin 22 0 2  3.03s user 0.00s system 99% cpu 3.035 total
 ==> 2193322744 / 3.03 == 723,868,892 per second

 time ./bin 15 0 4
 ct = 2590404239
./bin 15 0 4  3.12s user 0.00s system 99% cpu 3.119 total
 ==> 2590404239 / 3.12 == 830,257,768 per second

*/

/*
BENCHARGS=35 0 1
BENCHARGS=22 0 2
BENCHARGS=15 0 4
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/lyndon-words-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/lyndon-words-demo.cc DEMOFLAGS=-DTIMING"
/// End:

