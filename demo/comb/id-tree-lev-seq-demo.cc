
#include "comb/id-tree-lev-seq.h"
#include "comb/tree-lev-seq-aux.h"


#include "comb/comb-print.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h" // NXARG()
#include "jjassert.h"

//% Level sequences for unordered rooted identity trees.
//% Cf. OEIS sequence A004111.

// Cf. comb/tree-lev-seq-demo.cc for all unordered trees
// Cf. comb/ordered-tree-lev-seq-demo.cc for ordered trees
// Cf. comb/ordered-tree-branching-seq-demo.cc branching sequences for ordered trees


//#define TIMING // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n,"Number of non-root nodes");

    bool aa = false;
    NXARG(aa,"Whether to render trees as ASCII art");

    id_tree_lev_seq T(n);
#ifdef TIMING
#endif

    ulong ct = 0;
    do
    {
        ++ct;

#ifndef TIMING

        cout << setw(4) << ct << ":";
        T.print("  ");

        if ( aa )
        {
            cout << endl;
            T.print_aa("");
            cout << endl;
        }

        cout << endl;

        jjassert( T.OK() );

#endif
    }
    while ( 0 != T.next() );

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin 28
arg 1: 28 == n  [Number of nodes, n>=1]  default=9
arg 2: 0 == aa  [Whether to render trees as ASCII art]  default=0
 ct=408310668
./bin 28  7.54s user 0.00s system 99% cpu 7.540 total
 ==> 408310668/7.54 == 54,152,608 per second


*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/id-tree-lev-seq-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/id-tree-lev-seq-demo.cc DEMOFLAGS=-DTIMING"
/// End:
