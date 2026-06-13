#include "DFileTools.h"

CSVFileReader::CSVFileReader(string fAddress)
{
    pZombie = true;
    ifstream file(fAddress.c_str());

    if (file.is_open() == false)
    {
        cout << "Cannot open the input file (" << fAddress << ")" << endl;
        return;
    }

    string line;
    int lineCounter = 0;
    while (getline(file, line))
    {
        if (line == "")
        {
            continue;
        }

        vector<string> words = SplitIntoWords(line);

        if (words.size() == 0)
        {
            continue;
        }

        if (lineCounter == 0)
        { // this is title line
            lineCounter++;
            pColumnTitle = words;
            continue;
        }

        lineCounter++;
        vector<float> row = ConvertValues(words);
        pContent.push_back(row);
    }

    pZombie = false;
    pNColumn = pColumnTitle.size();
    pNRow = lineCounter - 1;
    file.close();
}

vector<float> CSVFileReader::ConvertValues(vector<string> fValues)
{
    vector<float> values;
    for (int i = 0; i < fValues.size(); i++)
    {
        float val = atof(fValues[i].c_str());
        values.push_back(val);
    }
    return values;
}

vector<string> CSVFileReader::SplitIntoWords(string fLine)
{
    string w;
    vector<string> words;
    std::istringstream ss(fLine);
    while (ss >> w)
    {
        string cw;
        for (int i = 0; i < w.size(); i++)
        {
            if (w[i] == ',' || w[i] == ' ')
            {
                if (cw.size() > 0)
                {
                    words.push_back(cw);
                }
                cw = "";
            }
            else
            {
                cw.push_back(w[i]);
            }
        }

        if (cw.size() > 0)
        {
            words.push_back(cw);
        }
        cw = "";
    }

    return words;
}

CSVFileReader::~CSVFileReader()
{
}

vector<string> CSVFileReader::GetColumnTitle()
{
    return pColumnTitle;
}

vector<float> CSVFileReader::GetRow(int fRowInd)
{
    if (fRowInd < pNRow)
    {
        return pContent[fRowInd];
    }
    vector<float> empty;
    return empty;
}

vector<float> CSVFileReader::GetColumn(int fColumnInd)
{
    vector<float> vec;
    if (fColumnInd >= pNColumn)
    {
        return vec;
    }
    for (int i = 0; i < pNRow; i++)
    {
        vector<float> row = pContent[i];
        vec.push_back(row[fColumnInd]);
    }
    return vec;
}

int CSVFileReader::GetNRows()
{
    return pNRow;
}

int CSVFileReader::GetNColumns()
{
    return pNColumn;
}

bool CSVFileReader::IsZombie()
{
    return pZombie;
}