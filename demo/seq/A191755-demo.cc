
#include "comb/combination-colex.h"
#include "comb/ruler-func.h"
#include "ds/bitarray.h"

#include "fxtio.h"
#include "bits/print-bin.h"
#include "bits/bitcount.h"
#include "nextarg.h"
#include "jjassert.h"

#include "fxttypes.h"

//% OEIS sequence A191755:
//% Binary self-shuffle words.


//#define TIMING  // uncomment to disable printing

static inline void complement(const ulong *x, ulong n, ulong *c)
// Write complement of combination C(2*n,n) given in x[] to c[].
{
    ulong p = 0;
    ulong i = 0;
    for (ulong j=0; j<n; ++j)
    {
        while ( x[j] > p )
        {
            c[i] = p;
            ++i;
            ++p;
        }
//        jjassert( p == x[j] );
        ++p;
    }

    while ( p < 2*n )
    {
//        cout << "2 : " << p << endl;
        c[i] = p;
        ++i;
        ++p;
    }

//    jjassert( i == n );
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 3;
    NXARG(n, "Length 2*n words:  n>0");
    const ulong n2 = 2*n;

    combination_colex C(n2, n);
    C.first();
    const ulong *x = C.data();

    ruler_func R(n);

    const ulong N = 1UL << (2*n);
    bitarray B(N);  //  2 ** (2*n) bits
    B.clear_all();

    ulong *c = new ulong[n];
    ulong *xw = new ulong[n];
    do  // for all shuffles
    {
        complement(x, n, c);
        for (ulong j=0; j<n; ++j)
        {
//            jjassert( c[j] != x[j] );
            xw[j] = (1UL << x[j]);
            xw[j] ^= (1UL << c[j]);
            jjassert( xw[j] != 0 );
        }

        R.first();
        ulong w = 0;
        B.set(w);
        ulong s;
        while ( (s=R.next()) != n )  // for all words
        {
            w ^= xw[s];
//            jjassert( w < N );
            B.set(w);
        }
    }
    while ( n != C.next() );  // xxx could stop when last element changes


#ifndef TIMING
    cout << "Shuffle-words:" << endl;
    for (ulong j=0; j<N; ++j)
    {
        if ( 1UL & bit_count(j) )  continue;  // never a shuffle-word
        print_bin("  ",j,n2);
        cout << ( 0!=B.test(j) ? "  yes" : "  NO");
        cout << endl;
    }
#endif

    ulong ct = B.count_ones();
    cout << " ct=" << ct << endl;

    delete [] c;
    delete [] xw;

    return 0;
}
// -------------------------



//  for n in $(seq 0 10); do ./bin $n 0; done | grep ct=


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A191755-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A191755-demo.cc DEMOFLAGS=-DTIMING"
/// End:
