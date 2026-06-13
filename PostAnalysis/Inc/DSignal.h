#ifndef DSignal_h
#define DSignal_h

#include <iostream>
#include <cmath>
#include <vector>
#include "DPairVector.h"

using namespace std;

class DSignal : public DPairVector
{
public:
    DSignal();
    DSignal(vector<float> fTimeVec, vector<float> fValueVec, string fTitle = "");
    ~DSignal();
    const vector<float> &GetTimeVec();
    const vector<float> &GetValueVec();
    bool IsValid();
    static DSignal ReadSignalFromCSVFile(string fAddress, int fColumnIndex, string fTitle);

private:
    bool CheckMonotonicTimeIncrease();
    bool pValid;
};

#endif