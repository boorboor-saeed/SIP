#include "DSignalTools.h"

#include <TCanvas.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TApplication.h>
#include <TH1D.h>
#include <TF1.h>
#include <TF2.h>
#include "TApplication.h"
#include "TCanvas.h"
#include "TRootCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TStyle.h"
#include "TGaxis.h"

// DSignal DSignalTools::ReadSignalFromCSVFile(string fAddress, int fColumnIndex, string fTitle)
// {
//     DSignal signal;
//     CSVFileReader file(fAddress);
//     if (file.IsZombie() == true)
//     {
//         return signal;
//     }

//     if (fColumnIndex < 0 || fColumnIndex >= file.GetNColumns())
//     {
//         return signal;
//     }

//     vector<float> time = file.GetColumn(0);
//     vector<float> value = file.GetColumn(fColumnIndex);
//     signal = DSignal(time, value, fTitle);
//     return signal;
// }

float DSignalTools::ComputeRiseTime(DSignal fChargeSignal, float fWindowBottom, float fWindowUp)
{
    float Tbottom = FindTimeAt(fChargeSignal, fWindowBottom);
    float Tup = FindTimeAt(fChargeSignal, fWindowUp);
    float RiseTime = Tup - Tbottom;
    return RiseTime;
}

DSignal DSignalTools::DownSampleSignal(DSignal fSigIn, float fdt)
{
    vector<float> time, value;
    float lastT = 0;
    for (int i = 0; i < fSigIn.GetLength(); i++)
    {
        if ((fSigIn.GetTimeVec()[i] - lastT) > fdt)
        {
            lastT = fSigIn.GetTimeVec()[i];
            value.push_back(fSigIn.GetValueVec()[i]);
            time.push_back(lastT);
        }
    }
    string Title = fSigIn.GetTitle() + string("_DownSampled");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::UpSampleSignal(DSignal fSigIn, float fDt)
{
    vector<float> time, value;
    int len = fSigIn.GetTimeVec().back() / fDt;
    for (int i = 0; i < len; i++)
    {
        float tIp = i * fDt;
        float vIp = LinLinInterpolate(fSigIn, tIp);
        time.push_back(tIp);
        value.push_back(vIp);
    }
    string Title = fSigIn.GetTitle() + string("_UpSampled");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

float DSignalTools::LinLinInterpolate(DSignal &fSigIn, float fTime)
{
    int len = fSigIn.GetLength();
    int i;

    for (i = 0; i < len; i++)
    {
        if (fSigIn.GetTimeVec()[i] > fTime)
        {
            break;
        }
    }

    float xmin, xmax, ymin, ymax;
    if (i == 0)
    {
        xmin = 0;
        ymin = 0;
        xmax = fSigIn.GetTimeVec()[0];
        ymax = fSigIn.GetValueVec()[0];
    }
    else if (i == len)
    {
        xmin = fSigIn.GetTimeVec()[i - 2];
        ymin = fSigIn.GetValueVec()[i - 2];
        xmax = fSigIn.GetTimeVec()[i - 1];
        ymax = fSigIn.GetValueVec()[i - 1];
    }
    else
    {
        xmin = fSigIn.GetTimeVec()[i - 1];
        ymin = fSigIn.GetValueVec()[i - 1];
        xmax = fSigIn.GetTimeVec()[i];
        ymax = fSigIn.GetValueVec()[i];
    }

    float m = (ymax - ymin) / (xmax - xmin);
    float y = ymin + m * (fTime - xmin);
    return y;
}

DSignal DSignalTools::IdealIntegrate(DSignal &fSigIn)
{
    vector<float> time, value;
    time.push_back(fSigIn.GetTimeVec()[0]);
    value.push_back(0);
    for (int i = 1; i < fSigIn.GetLength(); i++)
    {
        float dt = fSigIn.GetTimeVec()[i] - fSigIn.GetTimeVec()[i - 1];
        float ave = (fSigIn.GetValueVec()[i] + fSigIn.GetValueVec()[i - 1]) / 2;
        float area = dt * ave;
        time.push_back(fSigIn.GetTimeVec()[i]);
        value.push_back(area + value[i - 1]);
    }
    string Title = fSigIn.GetTitle() + string("_Integrated");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::IdealDifferentiate(DSignal &fSigIn)
{
    vector<float> time, value;

    for (int i = 1; i < fSigIn.GetLength(); i++)
    {
        float dt = fSigIn.GetTimeVec()[i] - fSigIn.GetTimeVec()[i - 1];
        float dv = (fSigIn.GetValueVec()[i] - fSigIn.GetValueVec()[i - 1]);
        float diff = dv / dt;
        time.push_back(fSigIn.GetTimeVec()[i]);
        value.push_back(diff);
    }
    string Title = fSigIn.GetTitle() + string("_Differentiated");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::Normalize(DSignal &fSigIn)
{
    float max = FindMax(fSigIn);
    DSignal SigOut = Scale(fSigIn, (1.0 / max));
    return SigOut;
}

DSignal DSignalTools::Extend(DSignal &fSigIn, float fDuration, bool fExtrapolateToZero)
{
    vector<float> time, value;

    for (int i = 1; i < fSigIn.GetLength(); i++)
    {
        float t = fSigIn.GetTimeVec()[i];
        float v = (fSigIn.GetValueVec()[i]);
        if (t <= fDuration)
        {
            time.push_back(t);
            value.push_back(v);
        }
        else
        {
            break;
        }
    }

    float dt = time[time.size() - 1] - time[time.size() - 2];

    if (fExtrapolateToZero == false)
    {
        while (time.back() < fDuration)
        {
            time.push_back(dt + time.back());
            value.push_back(value.back());
        }
    }
    if (fExtrapolateToZero == true)
    {
        while (time.back() < fDuration)
        {
            time.push_back(dt + time.back());
            value.push_back(0);
        }
    }

    string Title = fSigIn.GetTitle() + string("_Extended");
    DSignal SigOut(time, value, Title);
    return SigOut;
}
float DSignalTools::FindMax(DSignal &fSigIn)
{
    float max = -FLT_MAX;

    for (int i = 1; i < fSigIn.GetLength(); i++)
    {
        float v = fSigIn.GetValueVec()[i];
        if (v > max)
        {
            max = v;
        }
    }

    return max;
}

float DSignalTools::FindTimeAt(DSignal &fSigIn, float fValue)
{
    float max = fSigIn.GetValueVec().back();
    float vt = max * fValue;

    int i;
    for (i = 0; i < fSigIn.GetLength(); i++)
    {
        if (fSigIn.GetValueVec()[i] >= vt)
        {
            break;
        }
    }

    float tmin = fSigIn.GetTimeVec()[i - 1];
    float tmax = fSigIn.GetTimeVec()[i];
    float vmin = fSigIn.GetValueVec()[i - 1];
    float vmax = fSigIn.GetValueVec()[i];
    float m = (vmax - vmin) / (tmax - tmin);
    float t = tmin + (vt - vmin) / m;
    return t;
}

DSignal DSignalTools::ShiftTime(DSignal &fSigIn, float fShift)
{
    vector<float> time, value;
    for (int i = 0; i < fSigIn.GetLength(); i++)
    {
        time.push_back(fSigIn.GetTimeVec()[i] + fShift);
        value.push_back(fSigIn.GetValueVec()[i]);
    }
    string Title = fSigIn.GetTitle() + string("_Shifted");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::Scale(DSignal &fSigIn, float fScale)
{
    vector<float> time, value;
    for (int i = 0; i < fSigIn.GetLength(); i++)
    {
        time.push_back(fSigIn.GetTimeVec()[i]);
        value.push_back(fSigIn.GetValueVec()[i] * fScale);
    }
    string Title = fSigIn.GetTitle() + string("_Shifted");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::MovingAverage(DSignal &fSigIn, float fAveTime)
{
    vector<float> time, value;
    value.push_back(0);
    time.push_back(0);

    DSignal In = fSigIn;

    if (In.IsEquispaced() == false)
    {
        In = UpSampleSignal(In, 0.01);
    }

    float dt = In.GetTimeVec()[1] - In.GetTimeVec()[0];
    int AveLen = fAveTime / dt;
    int AveLenSide = AveLen / 2;
    float Sum = 0;

    for (int i = 0; i < In.GetLength(); i++)
    {
        Sum = 0;
        int LW = i - AveLen;
        int HW = i;

        for (int wi = LW; wi < HW; wi++)
        {
            float value = 0;
            if (wi < 0)
            {
                value = 0; // In.GetValueVec()[0];
            }
            else if (wi >= In.GetLength())
            {
                value = 0; // In.GetValueVec()[In.GetLength() - 1];
            }
            else
            {
                value = In.GetValueVec()[wi];
            }

            Sum += value;
        }

        float window = HW - LW;
        float t = In.GetTimeVec()[i];
        float ave = Sum / window;
        value.push_back(ave);
        time.push_back(t);
    }

    string Title = fSigIn.GetTitle() + string("_Averaged");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::ApplySlewRate(DSignal &fSigIn, float fRiseFallTime)
{
    DSignal In = fSigIn;
    vector<float> time, value;
    value.push_back(0);
    time.push_back(0);

    if (In.IsEquispaced() == false)
    {
        In = UpSampleSignal(In, 0.01);
    }

    float dt = In.GetTimeVec()[1] - In.GetTimeVec()[0];
    int Rn = fRiseFallTime / dt;

    for (int i = 0; i < In.GetLength(); i++)
    {
        time.push_back(In.GetTimeVec()[i]);
        value.push_back(0);
    }

    for (int i = 0; i < In.GetLength(); i++)
    {

        int IndStart = i;
        int IndEnd = i + Rn;
        float dy = In.GetValueVec()[IndStart];

        if (IndStart > 0)
        {
            dy = dy - In.GetValueVec()[IndStart - 1];
        }

        if (IndEnd >= In.GetLength())
        {
            IndEnd = In.GetLength() - 1;
            break;
        }

        for (int j = IndStart; j < IndEnd; j++)
        {
            float tt = dt * float(j - IndStart);
            float vv = (dy / fRiseFallTime) * tt;
            value[j] += vv;
        }

        for (int j = IndEnd; j < In.GetLength(); j++)
        {
            value[j] += dy;
        }
    }

    string Title = fSigIn.GetTitle() + string("_Slew");
    DSignal SigOut(time, value, Title);
    return SigOut;
}

DSignal DSignalTools::BuildStep(float fAmplitude, float fPulse, float fPeriod, float fDelay)
{
    vector<float> time, value;

    float dt = 0.001; // 1 ps
    int n = fPeriod / dt;
    int np = (fPulse + fDelay) / dt;
    int nd = fDelay / dt;

    for (int i = 0; i < n; i++)
    {
        float v = 0;
        float t = i;
        t *= dt;
        if (i < np && i > nd)
        {
            v = fAmplitude;
        }
        time.push_back(t);
        value.push_back(v);
    }

    string Title = "Step";
    DSignal SigOut(time, value, Title);
    return SigOut;
}