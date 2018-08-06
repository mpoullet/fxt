
# --- optimization and CPU type:
OFLAGS :=
#
#### disabled the following, fails on BSD (should be obsolete anyway):
## only use -march= if CPUTYPE is set:
#ifeq ($(strip $(CPUTYPE)),) # CPUTYPE not set:
##CPU := $(shell uname -m)
##CPU := athlon
#else # CPUTYPE is set:
#ARCHFLAG := -march=$(CPUTYPE) -mtune=$(CPUTYPE)
##  -mtune=CPU  optimize for CPU
##  -march=CPU  Generate code for given CPU
##  deprecated: -mcpu=   Schedule code for given CPU
#OFLAGS += $(ARCHFLAG)
#endif # CPUTYPE
#### end "disabled ..."

## see https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
OFLAGS += -O2
#OFLAGS += -O3
OFLAGS += -fomit-frame-pointer
OFLAGS += -fstrict-aliasing # Assume strict aliasing rules apply
#OFLAGS += -fno-exceptions # already in (main) makefile
OFLAGS += -ffast-math
OFLAGS += -fno-math-errno
#OFLAGS += -finite-math-only
OFLAGS += -fno-signed-zeros
#OFLAGS += -fcx-limited-range
#OFLAGS += -ftree-loop-if-convert
#OFLAGS += -fsched-spec
#OFLAGS += -finline-functions
#OFLAGS += -fif-conversion
#OFLAGS += -fhoist-adjacent-loads
#OFLAGS += -fexpensive-optimizations
#OFLAGS += -ftree-vectorize -ftree-vectorizer-verbose=1
#OFLAGS += -funsafe-math-optimizations # set by -ffast-math
#OFLAGS += -faggressive-loop-optimizations
#OFLAGS += -fcrossjumping
#OFLAGS += -fif-conversion
#OFLAGS += -fhoist-adjacent-loads
#OFLAGS += -fwhole-program
#OFLAGS += -mbranch-cost=5 # 1..5
#OFLAGS += --param max-unrolled-insns=256
#OFLAGS += --param l2-cache-size=512 ## in kilobytes
#OFLAGS += --param l1-cache-size=64 ## in kilobytes
#OFLAGS += --param l1-cache-line-size=64 ## in bytes
#OFLAGS += -fprefetch-loop-arrays # Generate prefetch instructions, if available, for arrays in loops
#OFLAGS += -freorder-blocks # Reorder basic blocks to improve code placement
#OFLAGS += -freorder-blocks-and-partition # Reorder basic blocks and partition into hot and cold sections
#OFLAGS += -fwhole-program # Perform whole program optimizations
#OFLAGS += -fwpa # Run the link-time optimizer in whole program analysis (WPA) mode. (not for C++ ?)
#OFLAGS += -flto-report # Report various link-time optimization statistics

## Optimize disregarding exact standards compliance:
#OFLAGS += -Ofast
#OFLAGS += -Ofast -march=auto # for Open64 compiler
#OFLAGS += -fsched-spec-load-dangerous
#OFLAGS += -funsafe-loop-optimizations
#OFLAGS += -funsafe-math-optimizations

# Control whether or not the compiler uses IEEE floating point
# comparisons.  These handle correctly the case where the result of a
# comparison is unordered.:
#OFLAGS += -mno-ieee-fp # only for i386 and x86-64
#
# Do not set ERRNO after calling math functions that are executed
# with a single instruction, e.g., sqrt.:
#OFLAGS += -fno-math-errno
#OFLAGS += -finline-limit=200
#OFLAGS += -mfancy-math-387 # Generate sin, cos, sqrt for FPU
#OFLAGS += -msse
#OFLAGS += -msse2
#OFLAGS += -foptimize-sibling-calls # Optimize sibling and tail recursive calls.
#OFLAGS += -fdelete-null-pointer-checks # Delete useless null pointer checks
#OFLAGS += -fschedule-insns2
#OFLAGS += -finline
#OFLAGS += -finline-functions
#OFLAGS += -fimplicit-templates


# --- warnings:
WFLAGS :=
#
WFLAGS += -Wundef
WFLAGS += -Wall
#WFLAGS += -Wuseless-cast
#WFLAGS += -pedantic -Wno-long-long  # do not warn about using 'long long'
WFLAGS += -Wextra
WFLAGS += -Wconversion  # gives many warnings when llvm/clang is used
#WFLAGS += -Wno-conversion
WFLAGS += -Wsign-promo
WFLAGS += -Wsign-compare
WFLAGS += -Wunused
WFLAGS += -Wshadow
#WFLAGS += -Waddress
#WFLAGS += -Wsurprising # Fortran only
#WFLAGS += -Wstrict-overflow
WFLAGS += -Wstrict-aliasing # Warn about code which might break strict aliasing
#WFLAGS += -Wsuggest-attribute=const # todo: many opportunities
#WFLAGS += -Wsuggest-attribute=pure
#WFLAGS += -Wsuggest-attribute=noreturn
## Warn about C++ constructs whose meaning differs between ISO C++ 1998 and ISO C++ 2011:
#WFLAGS += -Wc++11-compat
#WFLAGS += -Wold-style-cast # _only_ old-style casts are used
#WFLAGS += -Winline
#WFLAGS += -Wnested-externs
#WFLAGS += -Weffc++
WFLAGS += -Wzero-as-null-pointer-constant


# --- debuging:
GFLAGS = -g -fno-omit-frame-pointer
#GFLAGS += -fno-inline -fno-default-inline


# --- profiling:
PFLAGS = -pg -fno-omit-frame-pointer


#######
## for clang++:
## export LD_LIBRARY_PATH="/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64:"
CLANG_FLAGS=
#
CLANG_FLAGS += -Weverything
## ... except for:
CLANG_FLAGS += -Wno-reserved-id-macro # bug in clang++
CLANG_FLAGS += -Wno-c++98-compat-pedantic # 'long long'
CLANG_FLAGS += -Wno-old-style-cast # using only these
#
CLANG_FLAGS += -Wno-missing-variable-declarations # nope
CLANG_FLAGS += -Wno-missing-prototypes # nope
#
CLANG_FLAGS += -Wno-documentation # nope
#
CLANG_FLAGS += -Wno-global-constructors -Wno-exit-time-destructors #
CLANG_FLAGS += -Wno-padded # padding is OK
CLANG_FLAGS += -Wno-date-time # "format of __DATE__ and  __TIME__ not reproducible"
CLANG_FLAGS += -Wno-cast-align # src/aux1/bytescan.cc: "cast increases required alignment"
CLANG_FLAGS += -Wno-double-promotion # 'double' to 'long double'
#
#CLANG_FLAGS += -Wno- #
#CLANG_FLAGS += -Wno- #
#
#
#######

#######
## for GCC >= 4.9.0:
#FXT_CXXFLAGS += -fsanitize=address # broken as in clang++
#FXT_CXXFLAGS += -fsanitize=undefined
#FXT_CXXFLAGS += -fsanitize=shift
#FXT_CXXFLAGS += -fdiagnostics-color=auto
#FXT_CXXFLAGS += -fsanitize=undefined,shift,integer-divide-by-zero,unreachable,null,return,signed-integer-overflow
#######


# Emacs:
# Local Variables:
# frame-title-format: "FXT flags"
# End:
