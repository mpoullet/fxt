#if !defined  HAVE_PERM2CCF_H__
#define       HAVE_PERM2CCF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"
#include "fxttypes.h"

// perm/perm2ccf.cc:
void perm2ccf(const ulong *p, ulong n, ulong *c, bitarray *tb=nullptr);
void ccf2perm(const ulong *c, ulong n, ulong *p, bitarray *tb=nullptr);
void print_ccf(const char *bla, const ulong *c, ulong n, bitarray *tb=nullptr);


#endif  // !defined HAVE_PERM2CCF_H__
