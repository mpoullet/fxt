

#include "comb/lyndon-factorization.h"
#include "comb/mixedradix-rev.h"

#include "comb/comb-print.h"


#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"


//% Standard (Chen, Fox, Lyndon)-factorization of the word W.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of words");

    ulong r = 2;
    NXARG(r, "Number of letters ( r >= 2 )");

    ulong ct = 0;

    mixedradix_rev M(n, r);

    const ulong * W = M.data();
    ulong F[64];
//    ulong S[64];  for (ulong j=0; j<64; ++j)  S[j] = 0;
    do
    {
        ulong m = lyndon_factorization( W, n, F );
//        S[m] += 1;

#ifndef TIMING
        cout << " " << setw(4) << ct << ":";
        M.print("  ", true );

        cout << "   m = " << m ;  // number of factors
        cout << "   F = ";  // list of ends of factors
        for (ulong j=0; j<m; ++j)   cout << F[j] << ":";
        cout << endl;

        jjassert( F[0] == max_lyndon_prefix_len(W, n) );
#endif  // TIMING

        ++ct;
    }
    while ( M.next() );

    // A269456: "...degree n monic polynomials in GF(2)[x] with exactly k factors..."
//    for (ulong j=0; j<=n; ++j)  cout << S[j] << ", ";
//    cout << endl;

//    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/lyndon-factorization-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/lyndon-factorization-demo.cc DEMOFLAGS=-DTIMING"
/// End:
