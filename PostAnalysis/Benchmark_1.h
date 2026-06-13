#ifndef Benchmark_1_h
#define Benchmark_1_h

// (1974) The plasma effect in silicon semiconductor radiation detectors

#include "DBenchmarkBase.h"

class DBenchmark_1 : DBenchmarkBase
{
public:
    DBenchmark_1(string fBaseDir) : DBenchmarkBase(fBaseDir)
    {
        SetThisWorkName("SIP++");
    }
    ~DBenchmark_1()
    {
    }

    virtual void View(string fBenchmark = "")
    {
        compare_current("DetA/Alpha/", 1.1, 1.6, 45);
        compare_current("DetB/Alpha/", 1.1, 1.5, 30);
        compare_current("DetC/Alpha/", 1.1, 1.5, 45);

        compare_charge("DetA/Alpha/", 1.1, 1.6, 45);
        compare_charge("DetB/Alpha/", 1.1, 1.5, 30);
        compare_charge("DetC/Alpha/", 1.1, 1.5, 45);
    }

private:
    void compare_current(string fCase, float fAveTime, float fShift, float fTotalTime)
    {

        vector<DSignal> Signals;
        float SimulationRiseTime, MeasurementRiseTime;

        // experiment
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Exp" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 1, "Measured");
            signal = DSignalTools::ShiftTime(signal, fShift);
            signal = DSignalTools::Normalize(signal);
            signal = DSignalTools::Extend(signal, fTotalTime, true);
            signal.SetTitle("Experiment");
            Signals.push_back(signal);
        }

        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Gar" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Gar");
            signal = DSignalTools::Extend(signal, fTotalTime, true);
            signal = DSignalTools::MovingAverage(signal, fAveTime);
            signal = DSignalTools::Normalize(signal);
            signal = DSignalTools::Scale(signal, 1);

            signal.SetTitle("Garfield++");
            Signals.push_back(signal);
        }

        // simulation
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_SIP" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::MovingAverage(signal, fAveTime);
            signal = DSignalTools::Extend(signal, fTotalTime, true);
            signal = DSignalTools::Normalize(signal);
            signal = DSignalTools::Scale(signal, 1);
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
        map<string, float> RiseTimes;

        vector<DSignal> Signals;

        // experiment
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Exp" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 1, "Measured");
            signal = DSignalTools::ShiftTime(signal, fShift);
            signal = DSignalTools::Extend(signal, fTotalTime, true);

            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Normalize(signal);

            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle("Experiment");
            Signals.push_back(signal);
            RiseTimes["Experiment"] = riseTime;
        }

        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_Gar" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::Extend(signal, fTotalTime, true);
            signal = DSignalTools::MovingAverage(signal, fAveTime);

            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Normalize(signal);

            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle("Garfield++");
            Signals.push_back(signal);
            RiseTimes["Garfield++"] = riseTime;
        }

        // simulation
        if (1)
        {
            string address = GetBaseDir() + fCase + "Signal_SIP" + ".csv";
            DSignal signal = DSignal::ReadSignalFromCSVFile(address, 3, "Simulated");
            signal = DSignalTools::MovingAverage(signal, fAveTime);
            signal = DSignalTools::Extend(signal, fTotalTime, true);

            signal = DSignalTools::IdealIntegrate(signal);
            signal = DSignalTools::Normalize(signal);

            float riseTime = DSignalTools::ComputeRiseTime(signal, WindowBottom, WindowUp);
            string str = to_string(riseTime);
            signal.SetTitle(GetThisWorkName());
            Signals.push_back(signal);
            RiseTimes[GetThisWorkName()] = riseTime;
        }

        string title = "Compare_charge_" + fCase;
        DViewResults view("Time (ns)", "Charge signal (a.u.)", title);
        view.ViewSignals(Signals);
    }
};

#endif
