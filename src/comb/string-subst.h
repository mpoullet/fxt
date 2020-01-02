#if !defined  HAVE_STRING_SUBST_H__
#define       HAVE_STRING_SUBST_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015, 2017, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"  // ulong, uchar
#include "fxtio.h"
//#include "jjassert.h"

#include <string>
#include <vector>

class string_subst
// String substitution engine (Lindenmayer system, or L-system).
// Note: the derived class lindenmayer_system is much easier to use.
{

public:
    static const ulong NCHAR = 128;
    ulong nlev_;  // that many levels (iterate of the L-system)
    uchar *axiom_;  // the axiom
    uchar *maps_;  // all maps (images of maps, each null terminated)
    uchar **lev_ptr_;  // position in levels: [nlev+1]
    // [0] points into axiom_[], [1, 2, ... , nlev_] into maps_[]
    uchar *map_start_[NCHAR];  // ASCII only, pointers into maps_[]

    // the following are only used during initialization
    ulong maxrlen_;  // max that many symbols in all maps combined
    uchar *end_map_ptr_;  // position in maps_[] after last map

    string_subst(const string_subst&) = delete;
    string_subst & operator = (const string_subst&) = delete;

protected:
    void ctor_core(ulong nlev, ulong maxrlen)
    {
        axiom_ = NULL;

        nlev_ = nlev;
        lev_ptr_ = new uchar *[nlev_+1];

        maps_ = new uchar[maxrlen];
        end_map_ptr_ = maps_;

        for (ulong j=0; j < NCHAR; ++j)  map_start_[j] = NULL;
        maxrlen_ = maxrlen;
        for (ulong j=0; j < maxrlen_; ++j)  maps_[j] = '\0';
    }

    void dtor_core()
    {
        delete [] lev_ptr_;
        delete [] maps_;
        delete [] axiom_;
    }

public:
    explicit string_subst(ulong nlev, ulong maxrlen=2048)
    {
        ctor_core(nlev, maxrlen);
    }

    ~string_subst()
    {
        dtor_core();
    }

protected:
    bool add_map(uchar c, const uchar * const str);
    bool add_map(const uchar *c, const uchar *str);
//    bool add_map(const std::string & c, const std::string & str)
//    { return add_map( c.c_str(), str.c_str() ); }

public:
    bool set_axiom(const char * const ax);
    bool set_all_maps(const char * const maps[], ulong nr);

public:
    char current()  const
    // Current char in lowest level.
    {
        return (char)*lev_ptr_[nlev_];  // jjcast
    }

protected:
    char current(ulong lev)  const
    // Current char in level lev.
    {
//        jjassert( lev <= nlev_ );
        return (char)*lev_ptr_[lev];  // jjcast
    }

protected:
    bool next(ulong lev)
    // Return whether new symbol could be computed.
    // Once false has been returned, further calls
    //  lead to undefinded behaviour (unless first()
    //  is called again and returns true).
    {
        ++lev_ptr_[lev];  // advance in lev

        if ( *(lev_ptr_[lev]) == '\0' )  // at end?
        {
            if ( lev==0 )  return false;  // current is last (reached end in axiom)

            uchar * c;
            do
            {
                if ( ! next(lev-1) )  return false;  // recursion

                uchar *pc = lev_ptr_[lev-1];
                c = map_start_[*pc];  // char in level above
            }
            while ( *c == '\0' );  // repeat for 'empty' maps

            lev_ptr_[lev] = c;
        }

        return true;
    }

public:
    bool next()  { return  next(nlev_); }

    bool first()
    {
        if ( ! OK() )  return false;

        lev_ptr_[0] = axiom_ - 1;
        for (ulong j=1; j<=nlev_; ++j)
            lev_ptr_[j] = end_map_ptr_ - 2;  // shall give '\0' after increment

        return next();
    }

    void print_maps()  const;
    void print_internal_state()  const;

    ulong num_maps()  const;

    bool OK()  const;
};
// -------------------------


#endif  // !defined HAVE_STRING_SUBST_H__
