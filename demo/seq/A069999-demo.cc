
#include "comb/partition-asc-subset-lex.h"
#include "ds/bitarray.h"

//#define PART_DIST  // for A111212
#ifdef PART_DIST
#include "comb/partition-dist-asc-subset-lex.h"
#endif

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% OEIS sequence A069999:
//% Number of possible dimensions for commutators of n X n matrices.
//% Also sequence A111212.

// Cf. seq/A069999-2-demo.cc  for computation using convolutions of sets
// Cf. comb/partition-asc-subset-lex-demo.cc
// Cf. comb/partition-dist-asc-subset-lex-demo.cc

//#define TIMING  // uncomment to disable printing

class one_term
{
private:
#ifdef PART_DIST
    partition_dist_asc_subset_lex P;  // partitions
#else
    partition_asc_subset_lex P;  // partitions
#endif
    bitarray B;       // sums seen
    ulong *S;         // look up table for squares
    ulong *T;         // partial sums of squares

public:
    explicit one_term(ulong n)
        : P(n), B(n*n+1), S(new ulong[n+1]), T(new ulong[n+1])
    {
        for (ulong j=0; j<=n; ++j)  S[j] = j * j;
        for (ulong j=0; j<=n; ++j)  T[j] = 0;
    }

    ~one_term()
    {
        delete [] S;
        delete [] T;
    }

#ifdef TIMING
    void sum_sqr()
    // with subset-lex order, only the last two parts
    // differ from the previous partition.
    {
        const ulong *D = P.data() - 1;  // including D[0] = 0
        const ulong m = P.num_parts();

        jjassert( m >= 2 );
        ulong ss = T[m-2];

        ss += S[ D[m-1] ];
        T[m-1] = ss;

        ss += S[ D[m] ];
        T[m] = ss;

        B.set( ss );

//        P.print("");  cout << "  ==>  " << ss << endl;
    }
#else  // TIMING
    void sum_sqr()
    {
        const ulong *D = P.data();
        const ulong m = P.num_parts();
        P.print("");
        cout << "  ==>  ";
        ulong ss = 0;
        for (ulong j=0; j<m; ++j)
        {
            ulong s = S[ D[j] ];
            ss += s;
            cout << " " << s;
            if ( j < m - 1 )  cout << " +";
        }
        B.set( ss );
        cout << "  = " << ss << endl;
    }
#endif  // TIMING

    ulong count()
    {
        B.clear_all();
        ulong n = P.n_;
        B.set( n*n );  // subset-lex order, for first (skipped) partition
        P.first();
        // skip first partition (into one part)
        while ( P.next() )
        {
            sum_sqr();
        }

        return B.count_ones();
    }
};
// -------------------------



int
main(int argc, char **argv)
{
#ifdef TIMING
    ulong n1 = 0;
    ulong n2 = 13;
    NXARG(n1, "partitions into n parts starting from n1");
    NXARG(n2, "partitions into n parts up to n2");

    for (ulong j=n1; j<=n2; ++j)
    {
        one_term X(j);
        ulong ct = X.count();
        cout << j << " " << ct << endl;  // b-file format
        cout.flush();
    }

#else  // TIMING
    ulong n = 7;
    NXARG(n, "partitions of n");

    one_term X(n);
    ulong ct = X.count();
    cout << " ct = " << ct << endl;

#endif  // TIMING

    return 0;
}
// -------------------------

/*
  for n in $(seq 0 10); do ./bin $n | grep 'ct' ; done

Timing: Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz
GCC 8.3.0

time ./bin 0 100
./bin 0 100  5.83s user 0.00s system 99% cpu 5.834 total

  time ./bin 0 1000 > ~/b069999-in.txt
  ## up to n = 153:
  ./bin 1000 > ~/b069999-in.txt  2281.29s user 0.00s system 99% cpu 38:01.30 total
    N=153;x='x+O('x^(N+1)); Vec( 1/prod(k=1,N,1-x^k)/(1-x) )[N+1] ==> 573,169,704,246
    573169704246 / 2281.29 == 251,248,067 per second

  time ./bin 0 1000 > ~/b111212-in.txt
  ## up to n = 300:
  ./bin 0 1000 > ~/b111212-in.txt  7239.64s user 0.28s system 99% cpu 2:00:39.98 total
    N=300; x='x+O('x^(N+1)); Vec( prod(k=1,N,1+x^k)/(1-x) )[N+1] ==> 2,287,746,908,056
    2287746908056 / 7239.64  == 316,002,854 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A069999-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A069999-demo.cc DEMOFLAGS=-DTIMING"
/// End:

