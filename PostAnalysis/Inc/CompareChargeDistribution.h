#ifndef CompareChargeDistribution_h
#define CompareChargeDistribution_h

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
#include "DViewResults.h"

void CompareInitialCharges()
{
    vector<float> Radii = DTools::BuildLinVec(0, 1 * DUnitSystem::um, 2 * DUnitSystem::nm);

    vector<DChargeStatistics> List;
    // List.push_back(DChargeStatistics("5.5 MeV Alpha", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_0.01000_ns.root"));
    List.push_back(DChargeStatistics("130 MeV Carbon", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Carbon/Full/Blocking_C130MeV/OutputDir/Con_0.01000_ns.root"));
    List.push_back(DChargeStatistics("200 MeV Oxygen", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Oxygen/Full/Blocking_O200MeV/OutputDir/Con_0.01000_ns.root"));
    List.push_back(DChargeStatistics("760 MeV Calcium", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Calcium/Full/Blocking_Ca760MeV/OutputDir/Con_0.01000_ns.root"));
    List.push_back(DChargeStatistics("910 MeV Thallium", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Talium/Full/Blocking_Tl910MeV/OutputDir/Con_0.01000_ns.root"));

    for (int i = 0; i < List.size(); i++)
    {
        List[i].ComputeRadialDistribution(Radii, DType::Electron, DThreeVector(0, 0, 20 * DUnitSystem::um), DThreeVector(0, 0, 30 * DUnitSystem::um));
    }

    DViewResults view("radius (#mum)", "density (##/#mum^{3})", "Radial Charge Distribution");
    view.ViewChargeRadialDistribution(List);
}

void CompareTimeCharges_Tl()
{
    vector<vector<float>> RadiiList;
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 0.5 * DUnitSystem::um, 0.5 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 1.5 * DUnitSystem::um, 5 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 2 * DUnitSystem::um, 10 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 5 * DUnitSystem::um, 20 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 5 * DUnitSystem::um, 50 * DUnitSystem::nm));

    vector<DChargeStatistics> List;
    List.push_back(DChargeStatistics("10 ps", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Talium/Full/Blocking_Tl910MeV/OutputDir/Con_0.01000_ns.root"));
    List.push_back(DChargeStatistics("50 ps", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Talium/Full/Blocking_Tl910MeV/OutputDir/Con_0.05821_ns.root"));
    List.push_back(DChargeStatistics("100 ps", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Talium/Full/Blocking_Tl910MeV/OutputDir/Con_0.10780_ns.root"));
    List.push_back(DChargeStatistics("1 ns", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Talium/Full/Blocking_Tl910MeV/OutputDir/Con_1.06962_ns.root"));
    List.push_back(DChargeStatistics("25 ns", "/media/saeed/share/FOCUS_benchmarks/Benchmark2/FBK_Si1_Talium/Full/Blocking_Tl910MeV/OutputDir/Con_24.64471_ns.root"));

    for (int i = 0; i < List.size(); i++)
    {
        List[i].ComputeRadialDistribution(RadiiList[i], DType::Hole, DThreeVector(0, 0, 100 * DUnitSystem::um), DThreeVector(0, 0, 150 * DUnitSystem::um));
    }

    // DViewResults view("radius (#mum)", "density (##/#mum^{3})", "Radial Charge Distribution");
    DViewResults view("radius (#mum)", "density (arbitrary)", "Radial Charge Distribution");
    view.SetXRange(0, 4.9);
    view.ViewChargeRadialDistribution(List);
}

void CompareTimeCharges_Alpha()
{
    vector<vector<float>> RadiiList;
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 1 * DUnitSystem::um, 0.5 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 1.5 * DUnitSystem::um, 5 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 5 * DUnitSystem::um, 10 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 6 * DUnitSystem::um, 25 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 6 * DUnitSystem::um, 50 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 6 * DUnitSystem::um, 100 * DUnitSystem::nm));
    RadiiList.push_back(DTools::BuildLinVec(10 * DUnitSystem::pm, 6 * DUnitSystem::um, 200 * DUnitSystem::nm));

    vector<DChargeStatistics> List;
    List.push_back(DChargeStatistics("10 ps", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_0.01000_ns.root"));
    List.push_back(DChargeStatistics("100 ps", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_0.05821_ns.root"));
    List.push_back(DChargeStatistics("500 ps", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_0.46459_ns.root"));
    List.push_back(DChargeStatistics("1 ns", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_0.96654_ns.root"));
    List.push_back(DChargeStatistics("5 ns", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_5.19370_ns.root"));
    List.push_back(DChargeStatistics("10 ns", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_10.64471_ns.root"));
    List.push_back(DChargeStatistics("17 ns", "/media/saeed/share/FOCUS_benchmarks/Benchmark1/Det1/Full/OutputDir/Con_16.64471_ns.root"));

    for (int i = 0; i < List.size(); i++)
    {
        // List[i].ComputeRadialDistribution(RadiiList[i], DType::Electron, DThreeVector(0, 0, 1 * DUnitSystem::um), DThreeVector(0, 0, 5 * DUnitSystem::um));
        List[i].ComputeRadialDistribution(RadiiList[i], DType::Electron, DThreeVector(0, 0, 10 * DUnitSystem::um), DThreeVector(0, 0, 30 * DUnitSystem::um));
    }

    DViewResults view("radius (#mum)", "density (##/#mum^{3})", "Radial Charge Distribution");
    // DViewResults view("radius (#mum)", "density (arbitrary)", "Radial Charge Distribution");
    view.SetXRange(0, 5.8);
    view.ViewChargeRadialDistribution(List);
}

#endif
