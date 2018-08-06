#if !defined  HAVE_LINDENMAYER_SYSTEM_H__
#define       HAVE_LINDENMAYER_SYSTEM_H__
// This file is part of the FXT library.
// Copyright (C) 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/string-subst.h"  // base class

#include "fxttypes.h"  // ulong
//#include "fxtio.h"
//#include "jjassert.h"

#include <string>
#include <vector>

class
lindenmayer_system : public string_subst
// Lindenmayer-system.
// This is much easier to use than the underlying class string_subst.
//.
// jj_end_autodoc
{
protected:
    ulong num_maps_;
    std::string axiom_str_;
    std::vector<std::string> letter_str_;
    std::vector<std::string> map_str_;

public:
    lindenmayer_system(ulong iter,
                       const std::string axiom,
                       const std::vector<std::string> maps,
                       ulong maxrlen=2048)
        : string_subst(iter, maxrlen)
    {
        set_axiom( axiom.c_str() );  // from string_subst
        set_all_maps( maps );        // from string_subst

        num_maps_ = string_subst::num_maps();

        axiom_str_ = axiom;
        for (ulong j=0; j<num_maps_; ++j)
        {
            letter_str_.push_back( maps.at( 2*j ) );
            map_str_.push_back( maps.at( 2*j + 1) );
        }
        // ...then may use jjassert( OK() )
    }

protected:
    bool set_all_maps(const std::vector<std::string> & maps);

public:
    std::string str_axiom()  const  { return std::string( (const char*)axiom_ ); }

    ulong num_maps()  const  { return num_maps_; };

    const std::string & str_letter_at(ulong j)  const;
    const std::string & str_map_at(ulong j)  const;

    std::vector<std::string> str_all_maps(ulong z=0)  const;
    // z != 0 excludes all maps with length < z.

    void print_all_maps(ulong z=0)  const;
    // Return number of maps printed.
    // z != 0 excludes all maps with length < z.

    // From string_subst:
//    char current()  const;
//    bool next();
//    bool first();
//    bool OK()  const;
};
// -------------------------


#endif // !defined HAVE_LINDENMAYER_SYSTEM_H__
