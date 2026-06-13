#ifndef DThreeVector_H
#define DThreeVector_H

#include <vector>
#include <math.h>
#include <iostream>
#include <string>

class DThreeVector
{
public:
    DThreeVector();
    DThreeVector(double fx, double fy, double fz);
    DThreeVector(const DThreeVector *fOrg);
    ~DThreeVector();
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    double Mag2() const;
    double Mag() const;

    DThreeVector Norm() const;
    std::string Print() const;

    DThreeVector GetMultiply(double fM) const;
    DThreeVector GetDevision(double fD) const;
    DThreeVector GetAdd(const DThreeVector *fSecond) const;
    DThreeVector GetSub(const DThreeVector *fSecond) const;

    // manipulate methods
    void Unit();
    void Add(const DThreeVector &fVec);
    void Add(double fx, double fy, double fz);
    void Mul(double fM);
    void Set(double fx, double fy, double fz);

    // static methods
    static DThreeVector Add(const DThreeVector &fVec1, const DThreeVector &fVec2);
    static DThreeVector Sub(const DThreeVector &fVec1, const DThreeVector &fVec2);
    static double Distance(const DThreeVector &fVec1, const DThreeVector &fVec2);
    static DThreeVector MidPoint(const DThreeVector &fVec1, const DThreeVector &fVec2);

private:
    double x, y, z;
};

#endif