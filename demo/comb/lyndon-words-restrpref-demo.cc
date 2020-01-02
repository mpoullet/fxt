
#include "comb/lyndon-words-restrpref.h"
#include "comb/lyndon-words.h"

#include "comb/cyclic-words.h"

#include "fxtio.h"
#include "jjassert.h"
#include "fxttypes.h"
#include "nextarg.h"

#include <cmath> // std::abs

//% Lyndon words up to length n with restricted prefixes.

// Cf. comb/lyndon-words-demo.cc

//#define TIMING  // uncomment to disable printing

static ulong NN;  // initialized in main()

bool cond_smooth( const ulong * a, ulong i )
// OEIS sequences:
// A215327: smooth necklaces with 3 colors.
// A215328: smooth Lyndon words with 3 colors.
// A215329: smooth necklaces, 4 colors.
// A215330: smooth Lyndon words, 4 colors.
// A215331: smooth necklaces, 5 colors.
// A215332: smooth Lyndon words, 5 colors.
// A215333: smooth necklaces, 7 colors.
// A215334: smooth Lyndon words, 7 colors.
{
    if ( i<=1 )  return true;
    const long a0 = (long)a[i];
    const long a1 = (long)a[i-1];
    const long dd = std::abs( a0 - a1 );
//    cout << " ::"
//         << "  i = " << i
//         << "  a0 = " << a0
//         << "  a1 = " << a1
//         << "  dd = " << dd
//         << endl;
    return ( dd <= 1L );
}
// -------------------------


bool cond_cycl_smooth( const ulong * a, ulong i )
// OEIS sequences:
// A208772: cyclically smooth necklaces, 3 colors.
// A208773: cyclically smooth necklaces, 4 colors.
// A208774: cyclically smooth necklaces, 5 colors.
// A208775: cyclically smooth necklaces, 6 colors.
// A208776: cyclically smooth necklaces, 7 colors.
// A208777: array (cyclically smooth necklaces of k colors as column k).
// A215335: cyclically smooth Lyndon words, 3 colors.
// A215336: cyclically smooth Lyndon words, 4 colors.
// A215337: cyclically smooth Lyndon words, 5 colors.
// A215338: cyclically smooth Lyndon words, 7 colors.
{
    if ( ! cond_smooth( a, i ) )  return false;

    if ( i == NN )
    {
        const long a0 = (long)a[NN];
        const long a1 = (long)a[1];
        const long dd = std::abs( a0 - a1 );
        return ( dd <= 1L );
    }

    return true;
}
// -------------------------

bool cond_noteq( const ulong * a, ulong i )
// OEIS sequences:
// Necklaces with n beads of k colors, no 2 adjacent beads the same color.
// A106365: k = 3 colors
// A106366: k = 4 colors
// A106367: k = 5 colors
// A106368: k = 6 colors
{
    if ( i<=1 )  return true;
    const long a0 = (long)a[i];
    const long a1 = (long)a[i-1];
    return ( a1 != a0 );
}
// -------------------------


bool cond_true( const ulong *, ulong )
{
    return true;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Lyndon words up to length n");
    NN = n;
    ulong a = 0;
    NXARG(a, "First letter in the alphabet");
    ulong z = 2;
    NXARG(z, "Last letter in the alphabet");
    ulong q = 1;
    NXARG(q, "0 ==> show all, 1 ==> only necklaces, 2 ==> only Lyndon words");

    lyndon_words_restrpref L(n, a, z);

    ulong ct = 0;

    ulong i = L.first( cond_smooth );
//    ulong i = L.first( cond_cycl_smooth );
//    ulong i = L.first( cond_noteq );
//    ulong i = L.first( cond_true );

#ifdef TIMING
    while ( i )
    {
        ++ct;
        i = L.next_any();
    }
#else

    const ulong * x = L.data_1();  // one-based

//    cout << " :: i = " << i << endl;
    while ( i )
    {
        if ( ( q >= 2 ) && ! L.is_lyndon_word() )  goto next;
        if ( ( q == 1 ) && ! L.is_necklace() )  goto next;

        ++ct;

        cout << setw(4) << ct << ":  ";
        for (ulong j=1; j<=i; ++j)
        {
            cout << x[j];
            if ( j != i )  cout << " ";
        }
#if 1  // print trailing part as well:
        cout << ".";  // separator
        for (ulong j=i+1; j<=n; ++j)
        {
            cout << x[j];
            if ( j != n )  cout << " ";
        }
#endif
        if ( i < n )  cout << " ";
        cout << "  [" << L.change_idx() << "]";
        cout << endl;

        jjassert( 0 == cyclic_lex_min_idx( L.data_0(), i ) );

    next:
        switch ( q )
        {
        case 0:  i = L.next_any();  break;
        case 1:  i = L.next_necklace();  break;
        default:  i = L.next_lyndon_word();  break;
        }
    }

#endif
    cout << " ct = " << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz)

GCC 8.3.0

time ./bin 21 0 2  ## cond_true
arg 1: 21 == n  [Lyndon words up to length n]  default=4
arg 2: 0 == a  [First letter in the alphabet]  default=1
arg 3: 2 == z  [Last letter in the alphabet]  default=3
 ct = 766918996
./bin 21 0 2  4.37s user 0.00s system 99% cpu 4.365 total
==> 766918996 / 4.37 == 175,496,337 per second

time ./bin 21 0 2  ## cond_smooth
time ./bin 25 0 2
arg 1: 25 == n  [Lyndon words up to length n]  default=4
arg 2: 0 == a  [First letter in the alphabet]  default=1
arg 3: 2 == z  [Last letter in the alphabet]  default=3
 ct = 382577362
./bin 25 0 2  3.31s user 0.00s system 99% cpu 3.313 total
==> 382577362 / 3.31 == 115,582,284 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/lyndon-words-restrpref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/lyndon-words-restrpref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

