/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   LICENSE_md;
    const int            LICENSE_mdSize = 1317;

    extern const char*   README_md;
    const int            README_mdSize = 3462;

    extern const char*   Doxyfile;
    const int            DoxyfileSize = 64946;

    extern const char*   mkbuild_sh;
    const int            mkbuild_shSize = 1986;

    extern const char*   README_txt;
    const int            README_txtSize = 3902;

    extern const char*   LICENSE_txt;
    const int            LICENSE_txtSize = 1318;

    extern const char*   README_md2;
    const int            README_md2Size = 12165;

    extern const char*   iconpfm2Ed_PNG;
    const int            iconpfm2Ed_PNGSize = 13966;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 8;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
