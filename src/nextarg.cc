// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "nextarg.h"

int nextarg_act = 0;

void
next_float_arg(double &v, const char *vname, const char *what,
               int argc, char **argv)
{
    const double def = v;
    ++nextarg_act;

    if ( argc > nextarg_act )
    {
        // "." for default, but do parse .123
        if ( (argv[nextarg_act][0] != '.') && (argv[nextarg_act][1] != 0) )
            v = strtod(argv[nextarg_act], nullptr);
    }

#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << v << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << def;
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
    (void)def;
#endif
}
// -------------------------

void
next_string_arg(char *&v, const char *vname, const char *what,
                int argc, char **argv,
                char *def)  // need explicit default with strings
{
//    cout << " :: String" << endl;

    ++nextarg_act;
    if ( argc > nextarg_act )  v = argv[nextarg_act];
    else  v = def;

#ifndef FXT_SILENT_NXARG
#ifdef FXT_PREF_NXARG
    cout << FXT_PREF_NXARG;
#endif
    cout << "arg " << nextarg_act << ": ";
    cout << '"' << v << '"' << " == " << vname;
    cout << "  [" << what << "]";
    cout << "  default=" << '"' << def << '"';
    cout << endl;
#else
    // supress warnings about unused parameters:
    (void)what;
    (void)vname;
#endif
}
// -------------------------
