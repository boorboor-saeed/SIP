#include "DThreeVector.h"

DThreeVector::DThreeVector()
{
    x = 0;
    y = 0;
    z = 0;
}

DThreeVector::DThreeVector(double fx, double fy, double fz)
{
    x = fx;
    y = fy;
    z = fz;
}

DThreeVector::DThreeVector(const DThreeVector *fOrg)
{
    x = fOrg->GetX();
    y = fOrg->GetY();
    z = fOrg->GetZ();
}

DThreeVector::~DThreeVector()
{
}

double DThreeVector::GetX() const
{
    return x;
}

double DThreeVector::GetY() const
{
    return y;
}

double DThreeVector::GetZ() const
{
    return z;
}

double DThreeVector::Mag2() const
{
    double mag = x * x + y * y + z * z;
    return mag;
}

double DThreeVector::Mag() const
{
    double mag = std::sqrt(x * x + y * y + z * z);
    return mag;
}

DThreeVector DThreeVector::Norm() const
{
    double mag = sqrt(x * x + y * y + z * z);
    DThreeVector norm = {x / mag, y / mag, z / mag};
    return norm;
}

std::string DThreeVector::Print() const
{
    std::string str = "x: " + std::to_string(x) + "\t y: " + std::to_string(y) + "\t z: " + std::to_string(z);
    return str;
}

DThreeVector DThreeVector::GetMultiply(double fM) const
{
    return DThreeVector(x * fM, y * fM, z * fM);
}
DThreeVector DThreeVector::GetDevision(double fD) const
{
    return DThreeVector(x / fD, y / fD, z / fD);
}
DThreeVector DThreeVector::GetAdd(const DThreeVector *fSecond) const
{
    return DThreeVector(x + fSecond->GetX(), y + fSecond->GetY(), z + fSecond->GetZ());
}
DThreeVector DThreeVector::GetSub(const DThreeVector *fSecond) const
{
    return DThreeVector(x - fSecond->GetX(), y - fSecond->GetY(), z - fSecond->GetZ());
}

// --------------------------  manipulate methods ---------------------- //
void DThreeVector::Add(const DThreeVector &fVec)
{
    x += fVec.x;
    y += fVec.y;
    z += fVec.z;
}

void DThreeVector::Add(double fx, double fy, double fz)
{
    x += fx;
    y += fy;
    z += fz;
}

void DThreeVector::Mul(double fM)
{
    x *= fM;
    y *= fM;
    z *= fM;
}

void DThreeVector::Unit()
{
    double mag = sqrt(x * x + y * y + z * z);
    x /= mag;
    y /= mag;
    z /= mag;
}

// DThreeVector DThreeVector::GetUnit()
// {
//     double mag = sqrt(x * x + y * y + z * z);
//     double dx = x / mag;
//     double dy = y / mag;
//     double dz = z / mag;
//     DThreeVector Unit(dx,dy,dz);
//     return Unit;
// }

void DThreeVector::Set(double fx, double fy, double fz)
{
    x = fx;
    y = fy;
    z = fz;
}

// ------------------- static methods --------------------------- //
DThreeVector DThreeVector::Add(const DThreeVector &fVec1, const DThreeVector &fVec2)
{
    double x = fVec1.x + fVec2.x;
    double y = fVec1.y + fVec2.y;
    double z = fVec1.z + fVec2.z;
    DThreeVector Vec(x, y, z);
    return Vec;
}

DThreeVector DThreeVector::Sub(const DThreeVector &fVec1, const DThreeVector &fVec2)
{
    double x = fVec1.x - fVec2.x;
    double y = fVec1.y - fVec2.y;
    double z = fVec1.z - fVec2.z;
    DThreeVector Vec(x, y, z);
    return Vec;
}
double DThreeVector::Distance(const DThreeVector &fVec1, const DThreeVector &fVec2)
{
    double x = fVec1.x - fVec2.x;
    double y = fVec1.y - fVec2.y;
    double z = fVec1.z - fVec2.z;
    double mag = sqrt(x * x + y * y + z * z);
    return mag;
}
DThreeVector DThreeVector::MidPoint(const DThreeVector &fVec1, const DThreeVector &fVec2)
{
    double x = (fVec1.x + fVec2.x) / 2.0;
    double y = (fVec1.y + fVec2.y) / 2.0;
    double z = (fVec1.z + fVec2.z) / 2.0;
    return DThreeVector(x, y, z);
}