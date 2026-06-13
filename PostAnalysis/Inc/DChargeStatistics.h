#ifndef DChargeStatistics_h
#define DChargeStatistics_h

#include <iostream>
#include <cmath>
#include <vector>
#include "DPairVector.h"
#include "DThreeVector.h"

using namespace std;

enum DType
{
    Electron = 0,
    Hole = 1,
    PositiveIon = 2,
    NegativeIon = 3,
    Unknown = 4
};

struct DCharge
{
    DThreeVector Position;
    float Scale;
    DType Type;
};

class DChargeStatistics
{
public:
    DChargeStatistics(std::string fName, std::string fAddress);
    ~DChargeStatistics();
    bool ReadChargeFromRoot(std::string fAddress);
    std::string GetName();
    bool IsValid();
    vector<float> GetRadialDistribution();
    vector<float> GetRaddi();
    void ComputeRadialDistribution(std::vector<float> fRaddi, DType fType, DThreeVector fAxisStart, DThreeVector fAxisEnd);

private:
    vector<DCharge> pChargeList;
    std::string pName;
    bool pValidFlag;
    vector<float> pRadialDistribution;
    vector<float> pRadii;
};

#endif