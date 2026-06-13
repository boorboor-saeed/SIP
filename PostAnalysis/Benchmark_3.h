#ifndef Benchmark_3_h
#define Benchmark_3_h

// (2012) Comparison of charged particle identification using pulseshape discrimination and ∆E–E methods
// between frontand rear side injection in silicon detectors

#include "DBenchmarkBase.h"

class DBenchmark_3 : DBenchmarkBase
{
public:
    DBenchmark_3(string fBaseDir) : DBenchmarkBase(fBaseDir)
    {
        SetThisWorkName("SIP++");
    }
    ~DBenchmark_3()
    {
    }

    virtual void View(string fBenchmark = "")
    {
        // // // // oxygen
        compare("DetE/Oxygen/160MeV/BlockingContact/", 70, 15, 20);
        compare("DetE/Oxygen/200MeV/BlockingContact/", 80, 15, 20);
        compare("DetE/Oxygen/160MeV/OhmicContact/", 70, 15, 25);
        compare("DetE/Oxygen/200MeV/OhmicContact/", 80, 15, 20);

        // // // // // calcium
        // compare("DetE/Calcium/590MeV/BlockingContact/", 100, 15, 25);
        // compare("DetE/Calcium/760MeV/BlockingContact/", 200, 15, 25);
        // compare("DetE/Calcium/590MeV/OhmicContact/", 200, 15, 30);
        // compare("DetE/Calcium/760MeV/OhmicContact/", 200, 15, 25);

        // Titanium
        // compare("DetE/Titanium/660MeV/BlockingContact/", 100, 15, 25);
        // compare("DetE/Titanium/910MeV/BlockingContact/", 191, 5, 10);
        // compare("DetE/Titanium/660MeV/OhmicContact/", 220, 15, 30);
        // compare("DetE/Titanium/910MeV/OhmicContact/", 250, 15, 30);
    }

private:
    void compare(string fCase, float fTotalTime, float fAve, float fShift)
    {
        float WindowBottom = 0.1; // 10%
        float WindowUp = 0.9;     // 90%

        vector<DSignal> Signals;
        map<string, float> RiseTimes;

        // experiment
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Exp" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 1, "Measured");
            signal = DSignalTools::Extend(signal, fTotalTime);
            signal = DSignalTools::ShiftTime(signal, fShift);
            signal = DSignalTools::Normalize(signal);
            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle("Measured - Rise time: " + str + " ns");
            Signals.push_back(signal);
            RiseTimes["Experiment"] = riseTime;
        }
        // simulation
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_SIP" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::Extend(signal, fTotalTime + 50, true);
            signal = DSignalTools::MovingAverage(signal, fAve);
            signal = DSignalTools::MovingAverage(signal, fAve);
            signal = DSignalTools::MovingAverage(signal, fAve);
            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Normalize(signal);
            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle("Simulated - Rise time: " + str + " ns");
            Signals.push_back(signal);
            RiseTimes[GetThisWorkName()] = riseTime;
        }

        string title = "Compare_charge_" + fCase;
        DViewResults view("Time (ns)", "Charge (#)", title);
        view.ViewSignals(Signals);
    }
};

#endif
