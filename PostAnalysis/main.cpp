#include <iostream>
#include <fstream>
#include <cmath>
#include "TApplication.h"
#include "DChargeView.h"
#include "DFileTools.h"
#include "DSignal.h"
#include "DSignalTools.h"
#include "DTools.h"
#include "DChargeStatistics.h"

#include "Benchmark_1.h"
#include "Benchmark_2.h"
#include "Benchmark_3.h"

using namespace std;

void PlotSignal(string fAddress);

int main(int argc, char *argv[])
{
  
  string BaseDir = "../../Benchmarks/";

  TApplication app("app", &argc, argv);

  DBenchmark_1 bench1(BaseDir);
  bench1.View();

  DBenchmark_2 bench2(BaseDir);
  bench2.View();

  // DBenchmark_3 bench3(BaseDir);
  // bench3.View();

  // string Address = BaseDir + "DetA/Alpha/OutputDir/Signal.csv";
  // string Address = BaseDir + "DetD/Carbon-80MeV/OutputDir/Signal.csv";
  // string Address = BaseDir + "DetE/Calcium/760MeV/OhmicContact/Signal_SIP.csv";
  // PlotSignal(Address);

  app.Run();
  return 0;
}

void PlotSignal(string fAddress)
{
  DSignal signal = DSignal::ReadSignalFromCSVFile(fAddress, 3, "Simulated");
  // signal = DSignalTools::Extend(signal, 100, true);
  signal = DSignalTools::MovingAverage(signal, 3);
  // signal = DSignalTools::IdealIntegrate(signal);
  // signal = DSignalTools::Normalize(signal);

  DViewResults view("Time (ns)", "Charge signal (a.u.)", "Simple plot");
  view.SetXRange(0, 200);
  view.ViewSignal(signal);
}
