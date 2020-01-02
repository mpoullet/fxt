
#include "comb/mset-perm-lex.h"
#include "comb/mset-kperm-lex.h"

//#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"

#include <cstdlib>  // strtoul()


//% All k-permutations of a multiset in lexicographic order.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong plen = 4;   // length of prefix
    NXARG( plen, "length of prefix")
    ulong k;   // number of sorts of elements
    ulong *r;  // element i is repeated r[i] times

    cout << "args: multiplicities of elements" << endl;
    if ( argc<=2 )
    {
        ulong t[]={3, 2, 1, 0};  // proper multisets  ct=30
//        ulong t[]={1, 1, 1, 1, 0};  // permutations  ct = 24
//        ulong t[]={6, 2, 0};  // combinations  ct=28
        k=0;  while ( t[k] )  { ++k; }
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)  r[j] = t[j];
    }
    else
    {
        k = (ulong)argc - 2;
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)
        {
            ulong t = strtoul(argv[j+2], nullptr, 10);
            r[j] = t;
        }
    }

    mset_kperm_lex P(r, k, plen);
    const ulong n = P.num_parts();

    cout << "multiplicities: ( ";
    for (ulong i=0; i<k; ++i)
        cout << P.multiplicities()[i] << (i<k-1?", ":" ");
    cout << ")";
//    cout << "  k=" << P.k_ << "  n=" << P.n_;
    cout << "  k=" << P.num_sorts() << "  n=" << P.num_parts();
    cout << endl;

    jjassert( plen <= n );

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( n != P.next() );

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros
    ulong j = plen;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("  ", dfz);
        P.print_suffix("  ", dfz);
        cout << setw(4) << j;
        cout << endl;
    }
    while ( n != (j=P.next()) );

#endif  // TIMING

    delete [] r;



    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel Xeon CPU E3-1275 V2 @ 3.50GHz)

GCC 6.3.0


 time  ./bin 12 1 1 1 1 1 1 1 1 1 1 1 1  ## all permutations of 12
arg 1: 12 == plen  [length of prefix]  default=4
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
 ct=479001600
./bin 12 1 1 1 1 1 1 1 1 1 1 1 1  2.18s user 0.00s system 99% cpu 2.186 total
 ==> 479001600 / 2.18 == 219,725,504 per second

 time  ./bin 10 1 1 1 1 1 1 1 1 1 1 1 1  ## 10-prefixes of permutations of 12
arg 1: 10 == plen  [length of prefix]  default=4
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
 ct=239500800
./bin 10 1 1 1 1 1 1 1 1 1 1 1 1  1.26s user 0.00s system 99% cpu 1.263 total
 ==> 239500800 / 1.26 == 190,080,000 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-kperm-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-kperm-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
