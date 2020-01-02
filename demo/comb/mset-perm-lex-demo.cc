
#include "comb/mset-perm-lex.h"

//#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% All multiset permutations in lexicographic order, iterative generation.
//% Same as: all strings with fixed content.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong k;   // number of sorts of elements
    ulong *r;  // element i is repeated r[i] times

    cout << "args: multiplicities of elements" << endl;
    if ( argc<=1 )
    {
        ulong t[]={2, 2, 1, 0};  // proper multisets  ct=30
//        ulong t[]={1, 1, 1, 1, 0};  // permutations  ct = 24
//        ulong t[]={6, 2, 0};  // combinations  ct=28
        k=0;  while ( t[k] )  { ++k; }
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)  r[j] = t[j];
    }
    else
    {
        k = (ulong)argc - 1;
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)
        {
            ulong t = strtoul(argv[j+1], nullptr, 10);
            r[j] = t;
        }
    }

    mset_perm_lex P(r, k);
    const ulong n = P.num_parts();

    cout << "multiplicities: ( ";
    for (ulong i=0; i<k; ++i)
        cout << P.multiplicities()[i] << (i<k-1?", ":" ");
    cout << ")";
//    cout << "  k=" << P.k_ << "  n=" << P.n_;
    cout << "  k=" << P.num_sorts() << "  n=" << P.num_parts();
    cout << endl;

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( n != P.next() );

#else  // TIMING

    const bool dfz = true;  // whether to print dots for zeros
    ulong j = n;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        P.print("  ", dfz);
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
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)
GCC 8.3.0

 time ./bin 2 2 2 3 3 3
args: multiplicities of elements
multiplicities: ( 2, 2, 2, 3, 3, 3 )  k=6  n=15
 ct=756756000
./bin 2 2 2 3 3 3  2.14s user 0.00s system 99% cpu 2.144 total
 ==> 756756000 / 2.14 == 353,624,299 per second

 time ./bin 3 3 3 2 2 2 ## reordered
args: multiplicities of elements
multiplicities: ( 3, 3, 3, 2, 2, 2 )  k=6  n=15
 ct=756756000
./bin 3 3 3 2 2 2  2.17s user 0.00s system 99% cpu 2.173 total
 ==> 756756000 / 2.17 == 348,735,483 per second

 time  ./bin 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
 ct=479001600
./bin 1 1 1 1 1 1 1 1 1 1 1 1  1.30s user 0.00s system 99% cpu 1.302 total
 ==> 479001600 / 1.30 == 368,462,769 per second

 time  ./bin 15 15  ## combination (30 choose 15)
./bin 15 15  0.58s user 0.00s system 99% cpu 0.583 total
 ==> 155117520 / 0.58  == 267,444,000 per second

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 2 2 2 3 3 3
args: multiplicities of elements
multiplicities: ( 2, 2, 2, 3, 3, 3 )  k=6  n=15
ct=756756000
./bin 2 2 2 3 3 3  4.43s user 0.00s system 99% cpu 4.433 total
 ==> 756756000/4.43 == 170,825,282 per second

 time ./bin 3 3 3 2 2 2 ## reordered
args: multiplicities of elements
multiplicities: ( 3, 3, 3, 2, 2, 2 )  k=6  n=15
ct=756756000
./bin 3 3 3 2 2 2  4.48s user 0.00s system 99% cpu 4.477 total
 ==> 756756000/4.48 == 168,918,750 per second

 time  ./bin 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
ct=479001600
./bin 1 1 1 1 1 1 1 1 1 1 1 1  2.40s user 0.00s system 99% cpu 2.405 total
 ==> 479001600/2.40 == 199,584,000 per second

 time  ./bin 15 15  ## combination (30 choose 15)
args: multiplicities of elements
multiplicities: ( 15, 15 )  k=2  n=30
ct=155117520
./bin 15 15  1.22s user 0.00s system 99% cpu 1.226 total
 ==> 155117520/1.22 == 127,145,508 per second
*/




/*
BENCHARGS= 2 2 2 3 3 3
BENCHARGS= 3 3 3 2 2 2 ## reordered
BENCHARGS= 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
BENCHARGS= 15 15  ## combinations (30 choose 15)
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-perm-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-perm-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:
