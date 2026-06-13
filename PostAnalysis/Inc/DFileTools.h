#ifndef DFileTools
#define DFileTools

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<float> RowT;

class CSVFileReader
{
public:
    CSVFileReader(string fAddress);
    ~CSVFileReader();
    vector<string> GetColumnTitle();
    vector<float> GetRow(int fRowInd);
    vector<float> GetColumn(int fColumnInd);
    int GetNRows();
    int GetNColumns();
    bool IsZombie();

private:
    vector<string> pColumnTitle;
    vector<RowT> pContent;
    int pNRow, pNColumn;
    bool pZombie;
    vector<string> SplitIntoWords(string fLine);
    vector<float> ConvertValues(vector<string> fValues);
};
#endif