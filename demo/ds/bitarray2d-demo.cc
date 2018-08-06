
#define  BITARRAY2D_ASSERTS   // define to catch access beyond size

#include "ds/bitarray2d.h"
#include "ds/bitarray.h"

#include "fxttypes.h"
#include "jjassert.h"
#include "fxtio.h"

//% Demo of the 2-dimensional bitarray data structure.


int
main()
{
    bitarray2d B(7,5);
    B.clear_all();
    jjassert( B.all_clear_q() );
    B.dump_bits();  cout << endl;


    B.set(1,1);
    B.set(2,1);
    B.set(3,1);
    B.set(4,2);
    B.set(5,3);
//    B.set(10,10);  // out of range
    B.dump_bits();  cout << endl;
    jjassert( ! B.all_clear_q() );
    jjassert( ! B.all_set_q() );
    cout << "Number of set bits = " << B.count_ones() << endl;
    jjassert( B.num_bits() == B.count_ones() + B.count_zeros() );


    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/bitarray2d-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/bitarray2d-demo.cc DEMOFLAGS=-DTIMING"
/// End:

