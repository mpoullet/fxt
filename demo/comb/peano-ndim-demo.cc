
#include "comb/peano-ndim.h"
#include "comb/mixedradix-gray.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtio.h"
#include "jjassert.h"

//% n-dimensional Peano curve


//#define TIMING  // uncomment to disable printing


//#define DO_TEST
//
#ifdef DO_TEST
#include "ds/array3d.h"
#endif


int
main(int argc, char **argv)
{
    ulong nd = 2;
#ifdef DO_TEST
    nd = 3;
#else
    NXARG(nd, "Number of dimensions");
#endif

    ulong it = 2;
    NXARG(it, "Iterate");

    peano_ndim Peano( nd, it );

    const ulong dim = Peano.edge_length();
    cout << " edge_length = " << dim + 1 << endl;
    cout << " num_points = " << Peano.num_points() << endl;
#ifdef DO_TEST
    cerr << "## DO_TEST active" << endl;
    array3d<ulong> Arr( dim, dim, dim );
    Arr.null();
    cout << " n_elem = " << Arr.num_elem() << endl;

    long P0[3] = { 0, 0, 0 };
#endif

    ulong ct = 1;  // point zero is first
    ulong coord_idx = 0;
    long dir = 0;
    while ( Peano.next( coord_idx, dir ) )
    {
#ifdef TIMING
#else
//        if ( (ct+0)%27 != 0 )  { ++ct;  continue; };

        const long * Pnt = Peano.point();
        cout << " " << setw(4) << ct << ":  ";
        cout << " [";
        for (ulong j = 0; j < nd; ++j)  cout << " " << setw(2) << Pnt[j];
        cout << " ]";
        cout << setw(6) << "xyzrstuvw"[coord_idx];
        cout << " " << (dir<0?'-':'+');
//        cout << " " << (Peano.MR.dir()<0?'-':'+');
        Peano.MR.print("    ", true );
        cout << endl;
#endif  // TIMING

#ifdef DO_TEST

        const long * P = Peano.point();
        const long x = P[0], y = P[1], z = P[2];
        jjassert( ! Arr.is_off( x, y, z ) );
        const ulong act = Arr[x][y][z];
        if ( 0 != act )  cout << " :: act = " << act << endl;
        jjassert( 0 == act );
        Arr[x][y][z] = ct;
        jjassert( std::abs( P[0] - P0[0] ) <= 1L );
        jjassert( std::abs( P[1] - P0[1] ) <= 1L );
        jjassert( std::abs( P[2] - P0[2] ) <= 1L );
        P0[0] = P[0];
        P0[1] = P[1];
        P0[2] = P[2];
#endif

        ++ct;
    }


    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)

GCC 8.30


// with j_mod_nd[]:
time ./bin 3 6
arg 1: 3 == nd  [Number of dimensions]  default=2
arg 2: 6 == it  [Iterate]  default=2
 edge_length = 730
 num_points = 387420489
 ct=387420489
./bin 3 6  3.38s user 0.00s system 99% cpu 3.378 total
==> 387420489 / 3.38 == 114,621,446 points per second


// without j_mod_nd[]:
time ./bin 3 6
arg 1: 3 == nd  [Number of dimensions]  default=2
arg 2: 6 == it  [Iterate]  default=2
 edge_length = 730
 num_points = 387420489
 ct=387420489
./bin 3 6  6.23s user 0.00s system 99% cpu 6.233 total
==> 387420489 / 6.23 == 62,186,274 points per second


cf. class mixedradix_gray:
time ./bin 20 3
 ct=3486784401
./bin 20 3  5.25s user 0.00s system 99% cpu 5.254 total
 ==> 3486784401 / 5.25 == 664,149,409 numbers per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/peano-ndim-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/peano-ndim-demo.cc DEMOFLAGS=-DTIMING"
/// End:

