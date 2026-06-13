#ifndef DTOOLS_H_INCLUDED
#define DTOOLS_H_INCLUDED

#include <vector>
using namespace std;

namespace DUnitSystem
{
    // try to be compatible to Garfield Unit system

    // coordinate //
    static const double centimeter = 1.;
    static const double millimeter = 0.1;
    static const double micrometer = 0.001 * millimeter;
    static const double nanometer = 0.001 * micrometer;
    static const double picometer = 0.001 * nanometer;

    static const double cm = centimeter;
    static const double mm = millimeter;
    static const double um = micrometer;
    static const double nm = nanometer;
    static const double pm = picometer;

    // time //
    static const double nanosecond = 1.;
    static const double picosecond = 0.001 * nanosecond;
    static const double femtosecond = 0.001 * picosecond;
    static const double microsecond = 1000. * nanosecond;
    static const double millisecond = 1000. * microsecond;
    static const double second = 1000. * millisecond;

    static const double ns = nanosecond;
    static const double fs = femtosecond;
    static const double ps = picosecond;
    static const double us = microsecond;
    static const double ms = millisecond;

}

namespace DConstants
{

}

namespace DTools
{
    vector<float> BuildLinVec(float fMin, float fMax, float fStep);
    vector<float> BuildLogVec(float fMin, float fMax, float fCoff);
    vector<float> MultiplyVec(vector<float>, float fMul);
    void PrintVec(vector<float> fVec);
    float FindMax(vector<float> fVec);
}

#endif
