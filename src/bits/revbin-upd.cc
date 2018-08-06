// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsperlong.h"
#include "fxttypes.h"


ulong revbin_upd_tab[BITS_PER_LONG];  // mask for updating bit-reversed values
// values written by make_revbin_upd_tab(), see bits/revbin-upd.h
