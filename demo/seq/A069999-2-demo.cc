
//% OEIS sequence A069999:
//% Number of possible dimensions for commutators of n X n matrices.
//% Computation using a convolution over sets.

// Cf. seq/A069999-demo.cc  for direct computation using the partitions


#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

#include <set>
#include <vector>


int
main(int argc, char **argv)
{
    ulong n = 17;
    NXARG(n, "partitions up to n");

    cout << "# A069999" << endl;

    typedef std::set<ulong> Set;

    std::vector<Set> V;  // V[j] contains distinct sums of squares for partitions of j

    V.push_back( Set{0} );  // V[0]
//    cout << 0 << " " << V[0].size() << endl;

    for (ulong j=1; j<=n; ++j)
    {
        Set Sj;  // will be V[j]
        Sj.insert( j * j );  // [0 , j]

        for (ulong a=1; a<j; ++a)
        {
            const Set & Sa = V[a];

            const ulong b = j - a;  // [ a, b ]  a + b == j  where a <= b
            if ( a > b )  break;
            const Set & Sb = V[b];

            for (ulong ea : Sa )
            {
                for (ulong eb : Sb )
                {
                    Sj.insert( ea + eb );
                }
            }
        }

        V.push_back( Sj );
        cout << j << " " << Sj.size() << endl;
    }
    return 0;
}
// -------------------------

/*

Timing: Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz
GCC 8.3.0

time ./bin 100
./bin 100  18.01s user 0.00s system 99% cpu 18.017 total

# but faster (than A069999-demo.cc) for n large:

time ./bin 153
./bin 153  266.05s user 0.00s system 99% cpu 4:26.05 total

time ./bin 246
./bin 246  5512.55s user 0.24s system 99% cpu 1:31:52.82 total

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A069999-2-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A069999-2-demo.cc DEMOFLAGS=-DTIMING"
/// End:

