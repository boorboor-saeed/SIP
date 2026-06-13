#include "DTools.h"
#include <iostream>
#include <float.h>

namespace DTools
{
    vector<float> BuildLinVec(float fMin, float fMax, float fStep)
    {
        vector<float> out;
        float v = fMin;
        while (v < fMax)
        {
            out.push_back(v);
            v = v + fStep;
        }
        return out;
    }

    vector<float> BuildLogVec(float fMin, float fMax, float fCoff)
    {
        vector<float> out;
        float v = fMin;
        while (v < fMax)
        {
            out.push_back(v);
            v = v * fCoff;
        }
        return out;
    }

    void PrintVec(vector<float> fVec)
    {
        for (int i = 0; i < fVec.size(); i++)
            std::cout << fVec[i] << std::endl;
    }

    vector<float> MultiplyVec(vector<float> fVec, float fMul)
    {
        vector<float> out;
        for (int i = 0; i < fVec.size(); i++)
            out.push_back(fVec[i] * fMul);

        return out;
    }

    float FindMax(vector<float> fVec)
    {
        float max = -FLT_MAX;
        for (int i = 1; i < fVec.size(); i++)
        {
            float v = fVec[i];
            if (v > max)
            {
                max = v;
            }
        }

        return max;
    }
}
