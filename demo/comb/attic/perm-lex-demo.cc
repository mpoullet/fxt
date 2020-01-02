
#include "comb/perm-lex.h"

#include "comb/fact2perm.h"
#include "perm/perminvert.h"
#include "perm/permcomplement.h"

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "nextarg.h"
#include "jjassert.h"


//% Generate all permutations in lexicographic order.

//#define TIMING  // uncomment to disable printing

// Cf. comb/perm-lex2-demo.cc for a faster algorithm
// Cf. comb/perm-lex-inv-demo.cc for a faster algorithm also giving inverse permutations

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Permutations of n elements (n>=1).");
    jjassert( n>=1 );
    ulong q = 3;
    NXARG(q, "Amount of output: q<=3");

    perm_lex P(n);

#ifdef TIMING
#ifdef PERM_LEX_OPT
    cout << "PERM_LEX_OPT is defined." << endl;
#endif
    while ( P.next() )  {;}
#else

    bool dfz= true;  // whether to print dots for zeros
    const ulong *x = P.data();
    ulong *t1 = new ulong[n];  // aux
    ulong *t2 = new ulong[n];  // aux

    cout << "         permutation         inv. perm.";
//    cout << "     compl. inv. perm.    reversed perm.      fact." << endl;
    cout << "     compl. inv. perm.    reversed perm." << endl;

    ulong ct = 0;
    do
    {
        if ( q>=1 ) cout << setw(4) << ct << ":";
        ++ct;

        P.print("    ", dfz);

        if ( q>=2 )
        {
            make_inverse(x, t1, n);
            print_perm("        ", t1, n, dfz);

            if ( q>=3 )
            {
                make_complement(t1, t2, n);
                print_perm("        ", t2, n, dfz);

                make_inverse(t2, t1, n);
                print_perm("        ", t1, n, dfz);

//                perm2ffact(x, n, t1);
//                print_mixedradix("        ", t1, n-1, dfz);
            }
        }
        cout << endl;
    }
    while ( P.next() );

    delete [] t1;
    delete [] t2;
#endif

    return 0;
}
// -------------------------

/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)

GCC 8.3.0

time ./bin 13
arg 1: 13 == n  [Permutations of n elements (n>=1).]  default=4
arg 2: 3 == q  [Amount of output: q<=3]  default=3
PERM_LEX_OPT is defined.
./bin 13  11.59s user 0.00s system 99% cpu 11.587 total
 ==> 13!/11.59 == 537,275,306 per second

time ./bin 13
arg 1: 13 == n  [Permutations of n elements (n>=1).]  default=4
arg 2: 3 == q  [Amount of output: q<=3]  default=3
./bin 13  19.20s user 0.00s system 99% cpu 19.204 total
 ==> 13!/19.20 == 324,324,000 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12
./bin 12  2.96s user 0.00s system 99% cpu 2.961 total
 ==> 12!/2.96 == 161,824,864 per second
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

