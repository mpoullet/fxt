// This file is part of the FXT library.
// Copyright (C) 2014, 2015, 2017, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/string-subst.h"

#include "fxtio.h"
#include "fxttypes.h"  // ulong, uchar

#include <cstring>  // strlen()
//#include <cstdlib>  // strtoul()


static const char * const err_msg_head = "Error in string_subst:";


bool
string_subst::add_map(uchar c, const uchar * const str)
{
    if ( c == '\0')
    {
        cerr << err_msg_head
             << " add_map(): char == 0 forbidden." << endl;
        return false;
    }

    if ( map_start_[(ulong)c] != NULL )
    {
        cerr << err_msg_head
             << " add_map(): map for "
             << "char = [" << c << "] already set." << endl;
        return false;
    }
    map_start_[(ulong)c] = end_map_ptr_;

    ulong j = 0;
    uchar r;
    do  // can only fail with invalid call from within class
    {
        r = (uchar)str[j];  // jjcast
        ++j;
        if ( end_map_ptr_ >= maps_ + maxrlen_  )
        {
            cerr << err_msg_head
                 << " add_map(): internal error:"
                 << " out of space for maps." << endl;
            return false;
        }
        *end_map_ptr_ = r;
        ++end_map_ptr_;
    }
    while ( r != '\0' );
    return true;
}
// -------------------------

bool
string_subst::add_map(const uchar * const c, const uchar * const str)
{
    if ( c[0] == '\0')
    {
        cerr << err_msg_head
             << " add_map(): char == 0 forbidden." << endl;
        return false;
    }

    if ( c[1] != '\0' )
    {
        cerr << err_msg_head
             << " add_map(): left side more than one symbol." << endl;
        return false;
    }
    return  add_map(c[0], str);
}
// -------------------------


bool
string_subst::set_axiom(const char * const ax)
{
    if ( axiom_ != NULL )  // can/should we avoid this?
    {
        cerr << err_msg_head << " set_axiom(): axiom already set." << endl;
        return false;
    }
    ulong e = 0;
    while ( ax[e] != '\0' )  { ++e; }

    if ( e == 0 )  // we could allow this
    {
        cerr << err_msg_head << " set_axiom(): empty axiom forbidden." << endl;
        return false;
    }

    axiom_ = new uchar[e+1];
    for (ulong j=0; j<=e; ++j)  axiom_[j] = (uchar)ax[j];  // jjcast
    return true;
}
// -------------------------


bool
string_subst::set_all_maps(const char * const maps[], ulong nr)
{
    if ( end_map_ptr_ != maps_ )  // can/should we avoid this?
    {
        cerr << err_msg_head << " set_all_maps():"
             << " some maps already set." << endl;
        return false;
    }

    if ( (nr & 1) == 1 )
    {
        cerr << err_msg_head << " set_all_maps():"
             << " need an even number of strings." << endl;
        return false;
    }

    ulong rsz = 0;  // sum of sizes of all images
    for (ulong j=1; j<nr; j+=j)
        rsz += strlen(maps[j]) + 1;

    if ( rsz > maxrlen_ )  // need to resize maps_[]
    {
        maxrlen_ = rsz;
        delete [] maps_;
        maps_ = new uchar[maxrlen_];
        end_map_ptr_ = maps_;
    }


    for (ulong j=0; j<nr; j+=2)
    {
//        cout << " :: adding map ";
//        cout << " [" << maps[j] << "]  -->";
//        cout << " [" << maps[j+1] << "]";
//        cout << endl;
        if ( ! add_map( (uchar*)maps[j], (uchar*)maps[j+1]) )  // jjcast
            return false;
    }
    return true;
}
// -------------------------

void
string_subst::print_maps()  const
{
    cout << "Axiom: " << axiom_ << endl;
    cout << "Maps:" << endl;
    for (ulong j=0; j<NCHAR; ++j)
    {
        uchar *c = map_start_[j];
        if ( c == NULL )  continue;  // no entry

        cout << "  " << (char)j << " |--> ";
        uchar s;
        while ( (s = *c) != '\0' )
        {
            cout << s;
            ++c;
        }
        cout << endl;
    }
}
// -------------------------


void
string_subst::print_internal_state()  const
{
    print_maps();
    for (ulong lev=0; lev <= nlev_; ++lev)
        cout << " lev " << lev << ": [" << current(lev) << "]" << endl;
}
// -------------------------

ulong
string_subst::num_maps()  const
{
    ulong ct = 0;
    for (ulong j=0; j<NCHAR; ++j)  ct += (map_start_[j] != NULL);
    return ct;
}
// -------------------------

bool
string_subst::OK()  const
// Shall be called only after set_axiom() and set_maps() are called.
{
    if ( axiom_ == NULL )
    {
        cerr << err_msg_head << " axiom not set." << endl;
        return false;
    }

    if ( end_map_ptr_ == maps_ )
    {
        cerr << err_msg_head << " no maps set." << endl;
        return false;
    }

    if ( *(end_map_ptr_ - 1) != '\0' )
    {
        cerr << err_msg_head
             << " internal error: [*(end_map_ptr_ - 1) != null_char]." << endl;
        return false;
    }

    // have maps for all symbols?
    for (ulong j=1; j<NCHAR; ++j)  // symbols in maps_[]
    {
        uchar * p = map_start_[j];
        if ( p == NULL )  continue;

        uchar c0 = (uchar)j;
        while ( *p != '\0' )
        {
            if ( map_start_[*p] == NULL )
            {
                cerr << err_msg_head
                     << "  char == '" << *p << "'"
                     << " in rhs. of map for '" << c0 << "'"
                     << " has no map." << endl;
                return false;
            }
            ++p;
        }
    }
    for (uchar *p=axiom_; *p != '\0'; ++p)  // symbols in axiom_[]
    {
        if ( map_start_[*p] == NULL )
        {
            cerr << err_msg_head
                 << "  char == '" << *p << "'"
                 << " in axiom has no map." << endl;
            return false;
        }
    }
    return true;
}
// -------------------------

