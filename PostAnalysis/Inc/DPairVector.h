#ifndef DPairVector_h
#define DPairVector_h

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class DPairVector
{
public:
    DPairVector();
    DPairVector(vector<float> fXVec, vector<float> fYVec, string fTitle = "");
    ~DPairVector();
    const vector<float> &GetXVec();
    const vector<float> &GetYVec();
    int GetLength();
    bool IsZombie();

    bool IsEquispaced();
    string GetTitle();
    void SetTitle(string fTitle);
    static DPairVector ReadFromCSVFile(string fAddress, int fColumnIndex, string fTitle);

private:
    bool pZombie;
    bool pEquispaced;
    string pTitle;
    vector<string> pColumns;
    vector<float> pX;
    vector<float> pY;
    int pLength;
    bool CheckLength();
    bool CheckEquiSpace();
};
#endif