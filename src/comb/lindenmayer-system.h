#if !defined  HAVE_LINDENMAYER_SYSTEM_H__
#define       HAVE_LINDENMAYER_SYSTEM_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2019 Joerg Arndt
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
    // the following two are such that
    // map j is the map  letter_vec_[j] |--> word_vec_[j]
    std::vector<std::string> letter_vec_;
    std::vector<std::string> word_vec_;

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
            letter_vec_.push_back( maps.at( 2*j ) );
            word_vec_.push_back( maps.at( 2*j + 1) );
        }
        // ...then may use jjassert( OK() )
    }

protected:
    bool set_all_maps(const std::vector<std::string> & maps);

public:
    std::string axiom_str()  const  { return axiom_str_; }
//    std::string letter_str()  const
//    {
//        std::string L;
//        for (auto s : letter_vec_)
//            L += s[0];
//        return L;
//    }

    ulong num_maps()  const  { return num_maps_; };

    const std::string & str_letter_at(ulong j)  const
    // Valid j are 0, 1, 2, ..., num_maps_ - 1
    {
        return letter_vec_.at( j );
    }

    const std::string & str_word_at(ulong j)  const
    // Valid j are 0, 1, 2, ..., num_maps_ - 1
    {
        return word_vec_.at( j );
    }

//    ulong idx_for_letter(const std::string & L)  const
//    // Return index (0, 1, ..., num_maps_ - 1) for letter L,
//    // return -1UL if there is no map for L.
//    {
//        for (ulong i=0; i<num_maps() - 1; ++i)
//            if ( L == str_letter_at(i) )
//                return i;
//        return -1UL;
//    }

    std::vector<std::string> str_all_maps(ulong z=0)  const;
    // z != 0 excludes all maps with length < z.

    void print_all_maps(ulong z=0)  const;
    // z != 0 excludes all maps with length < z.

    // From string_subst:
//    char current()  const;
//    bool next();
//    bool first();
//    bool OK()  const;
};
// -------------------------


#endif // !defined HAVE_LINDENMAYER_SYSTEM_H__
