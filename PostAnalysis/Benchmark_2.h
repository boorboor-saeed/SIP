#ifndef Benchmark_2_h
#define Benchmark_2_h

// (2004) Charge and current-sensitive preampliﬁers for pulse shape
// discrimination techniques with silicon detectors

#include "DBenchmarkBase.h"

class DBenchmark_2 : DBenchmarkBase
{
public:
    DBenchmark_2(string fBaseDir) : DBenchmarkBase(fBaseDir)
    {
        SetThisWorkName("SIP++");
    }
    ~DBenchmark_2()
    {
    }

    virtual void View(string fBenchmark = "")
    {
        compare_current("DetD/Carbon-80MeV/", 4, 0, 50);
        compare_charge("DetD/Carbon-80MeV/", 4, 0, 50);
    }

private:
    void compare_current(string fCase, float fAveTime, float fShift, float fTotalTime)
    {
        vector<DSignal> Signals;
        // experiment
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Exp" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 1, "Measured");
            signal = DSignalTools::Scale(signal, -1);
            signal = DSignalTools::ShiftTime(signal, fShift);
            signal = DSignalTools::Normalize(signal);
            signal.SetTitle("Experiment");
            Signals.push_back(signal);
        }

        // simulation
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Gar" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::MovingAverage(signal, 1);
            signal = DSignalTools::Normalize(signal);
            signal.SetTitle("Garfield++");
            Signals.push_back(signal);
        }

        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_SIP" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::MovingAverage(signal, fAveTime);
            signal = DSignalTools::Normalize(signal);
            signal.SetTitle(GetThisWorkName());
            Signals.push_back(signal);
        }

        string title = "Compare_current_" + fCase;
        DViewResults view("Time (ns)", "Current signal (a.u.)", title);
        view.ViewSignals(Signals);
    }

    void compare_charge(string fCase, float fAveTime, float fShift, float fTotalTime)
    {
        float WindowBottom = 0.1; // 10%
        float WindowUp = 0.9;     // 90%

        vector<DSignal> Signals;
        map<string, float> RiseTimes;

        float SimulationRiseTime, MeasurementRiseTime;

        // experiment
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Exp" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 1, "Measured");
            signal = DSignalTools::Scale(signal, -1);
            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Extend(signal, fTotalTime);
            signal = DSignalTools::ShiftTime(signal, 0.1);
            signal = DSignalTools::Normalize(signal);
            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle("Experiment");
            Signals.push_back(signal);
            MeasurementRiseTime = riseTime;
            RiseTimes["Experiment"] = riseTime;
        }

        // simulation static --> using standard Garfield
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Gar" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::MovingAverage(signal, fAveTime);
            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Extend(signal, fTotalTime);
            signal = DSignalTools::Normalize(signal);
            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle("Garfield++");
            Signals.push_back(signal);
            SimulationRiseTime = riseTime;
            RiseTimes["Garfield++"] = riseTime;
        }

        // simulation --> dynamic field is on
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_SIP" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::MovingAverage(signal, fAveTime);
            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Extend(signal, fTotalTime);
            signal = DSignalTools::Normalize(signal);
            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle(GetThisWorkName());
            Signals.push_back(signal);
            SimulationRiseTime = riseTime;
            RiseTimes[GetThisWorkName()] = riseTime;
        }

        string title = "Compare_charge_" + fCase;
        DViewResults view("Time (ns)", "Charge signal (a.u.)", title);
        view.ViewSignals(Signals);
    }
};

#endif
