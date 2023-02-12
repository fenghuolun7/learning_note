current understanding:

only symbols which are actually used in binary files matter.
if libraries containes undefined reference, if it is not used by binaries, it is fine.

binaries files only record the most direct symbols.
if binaries files use a function which has a dependency of other lib A, and lib A is dependent to lib B. if you use 'nm' to checkout the symbols, lib B's symbol is not exist.