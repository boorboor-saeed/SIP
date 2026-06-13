#ifndef BenchmarkBase_h
#define BenchmarkBase_h
#include <iostream>
using namespace std;

#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <TApplication.h>
#include "DFileTools.h"
#include "DSignal.h"
#include "DPairVector.h"
#include "DSignalTools.h"
#include "DViewResults.h"

class DBenchmarkBase
{
public:
    DBenchmarkBase(string fBaseDir)
    {
        pBaseDir = fBaseDir;
    }
    ~DBenchmarkBase()
    {
        ;
    }

    string GetBaseDir()
    {
        return pBaseDir;
    }

    virtual void View(string fBenchmark = "")
    {
        cout << "This is DBenchmarkBase" << endl;
    }

    void ReportRelativeError(map<string, float> fQauntities, string fRefKey, string title = "")
    {
        std::cout << std::endl;
        std::cout << "------------------ Relative error for " << title << "------------------" << std::endl;
        for (const auto &pair : fQauntities)
        {

            std::cout << "Value of " << pair.first << " is " << pair.second << " ns." << std::endl;

            if (pair.first == fRefKey)
            {
                std::cout << std::endl;
                continue;
            }

            float error = 100.0 * (pair.second - fQauntities[fRefKey]) / fQauntities[fRefKey];
            std::cout << "Relative error to experiment: " << error << " %" << std::endl;
            std::cout << std::endl;
        }
    }

    string GetThisWorkName()
    {
        return pThisWorkName;
    }
    void SetThisWorkName(string fName)
    {
        pThisWorkName = fName;
    }

private:
    string pBaseDir;
    string pThisWorkName;
};

#endif