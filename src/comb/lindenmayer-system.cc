// This file is part of the FXT library.
// Copyright (C) 2017 Joerg Arndt
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
        bool q =
            string_subst::add_map(
                                  (uchar*)maps[j].c_str(),  // jjcast
                                  (uchar*)maps[j+1].c_str()  // jjcast
                                  );

        if ( ! q )  return false;
    }

    return true;
}
// -------------------------

const std::string &
lindenmayer_system::str_letter_at(ulong j)  const
// Valid j are 0, 2, ..., num_maps_ - 1
{
    return letter_str_.at( j );
}
// -------------------------

const std::string &
lindenmayer_system::str_map_at(ulong j)  const
// Valid j are 0, 2, ..., num_maps_ - 1
{
    return map_str_.at( j );
}
// -------------------------


//    std::string str_map(ulong j)  const
//    // image of character j
//    {
//        if ( j >= NCHAR )  return "";  // j out of range
//        if ( map_start_[j] == NULL )  return "";  // no map for j
//        const uchar *c = map_start_[j];
//        return std::string( (const char*)c );
//    }


std::vector<std::string>
lindenmayer_system::str_all_maps(ulong z/*=0*/)  const
// z != 0 excludes all maps with length < z.
{
    std::vector<std::string> R;
    for (ulong j=0; j<num_maps_; ++j)
    {
        const std::string & M = map_str_.at(j);
        if ( M.size() >= z )
        {
            R.push_back( letter_str_.at(j) );  // jjcast
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
        const std::string & M = map_str_.at(j);
        if ( M.size() >= z )
            std::cout << str_letter_at(j) << " |--> " << M << std::endl;
    }
}
// -------------------------

