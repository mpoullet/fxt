// This file is part of the FXT library.
// Copyright (C) 2017, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/lindenmayer-system.h"

#include "fxttypes.h"  // ulong


static const char * const err_msg_head = "Error in lindenmayer_system:";


bool
lindenmayer_system::set_all_maps(const std::vector<std::string> & maps)
{
    ulong nr = maps.size();
    if ( (nr & 1) == 1 )
    {
        cerr << err_msg_head << " set_all_maps():"
             << " need an even number of strings." << endl;
        return false;
    }

    for (ulong j=0; j<nr; j+=2)
    {
        // letter lt and word wd for map:
        uchar * lt = (uchar*)maps[j].c_str();  // jjcast
        uchar * wd = (uchar*)maps[j+1].c_str();  // jjcast

        bool q = string_subst::add_map( lt, wd );
        if ( ! q )  return false;
    }

    return true;
}
// -------------------------


std::vector<std::string>
lindenmayer_system::str_all_maps(ulong z/*=0*/)  const
// z != 0 excludes all maps with length < z.
{
    std::vector<std::string> R;
    for (ulong j=0; j<num_maps_; ++j)
    {
        const std::string & M = word_vec_.at(j);
        if ( M.size() >= z )
        {
            R.push_back( letter_vec_.at(j) );
            R.push_back( M );
        }
    }
    return R;
}
// -------------------------

void
lindenmayer_system::print_all_maps(ulong z/*=0*/)  const
// Return number of maps printed.
// z != 0 excludes all maps with length < z.
{
    for (ulong j=0; j<num_maps_; ++j)
    {
        const std::string & M = word_vec_.at(j);
        if ( M.size() >= z )
            std::cout << str_letter_at(j) << " |--> " << M << std::endl;
    }
}
// -------------------------

