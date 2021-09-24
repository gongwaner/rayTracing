#include <cmath>
#include <limits>
#include <assert.h>

#include "Vec3.h"
#include "CommonUtil.h"


//static variables
Vec3 Vec3::Zero = Vec3(0, 0, 0);


//constructors
Vec3::Vec3() : x(0), y(0), z(0)
{
}

Vec3::Vec3(double inX, double inY, double inZ) : x(inX), y(inY), z(inZ)
{
}

Vec3::Vec3(const Vec3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}


//setters
void Vec3::SetX(double inX)
{
    x = inX;
}

void Vec3::SetY(double inY)
{
    y = inY;
}

void Vec3::SetZ(double inZ)
{
    z = inZ;
}


//operator overloading
Vec3 Vec3::operator-() const
{
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator+(const Vec3& v) const
{
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(double t) const
{
    return Vec3(x * t, y * t, z * t);
}

Vec3 Vec3::operator*(const Vec3& v) const
{
    return Vec3(x * v.x, y * v.y, z * v.z);
}

Vec3 Vec3::operator/(double t) const
{
    assert(!isnan(t) && "ERROR:t is NAN");
    assert((abs(t) > std::numeric_limits<double>::epsilon()) && "ERROR:t is almost 0");

    return operator*(1 / t);
}

Vec3& Vec3::operator+=(const Vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vec3& Vec3::operator*=(double t)
{
    x *= t;
    y *= t;
    z *= t;

    return *this;
}

Vec3& Vec3::operator/=(double t)
{
    //For IEEE floats, division of a finite nonzero float by 0 is
    //well-defined and results in +infinity (if the value was >zero)
    //or -infinity (if the value was less than zero).
    //The result of 0.0/0.0 is NaN.
    //If you use integers, the behaviour is undefined.
    assert(!isnan(t) && "ERROR:t is NAN");
    assert((abs(t) > std::numeric_limits<double>::epsilon()) && "ERROR:t is almost 0");

    return *this *= 1 / t;
}


//utility functions
double Vec3::Dot(const Vec3& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

double Vec3::Dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

Vec3 Vec3::Cross(const Vec3& v) const
{
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Vec3::LengthSquared() const
{
    return x * x + y * y + z * z;
}

double Vec3::Length() const
{
    return std::sqrt(LengthSquared());
}

void Vec3::Normalize()
{
    if(Length() > std::numeric_limits<double>::epsilon())
    {
        double scale = 1.0 / Length();

        x *= scale;
        y *= scale;
        z *= scale;
    }
}

Vec3 Vec3::GetUnitVector() const
{
    assert(!isnan(Length()) && "ERROR:Length() is NAN");
    assert((Length() > std::numeric_limits<double>::epsilon()) && "ERROR:Length() is almost 0");

    double scale = 1.0 / Length();
    return Vec3(x * scale, y * scale, z * scale);
}

double Vec3::DistanceSquared(const Vec3& v) const
{
    double dx = v.x - x;
    double dy = v.y - y;
    double dz = v.z - z;

    return dx * dx + dy * dy + dz * dz;
}

double Vec3::Distance(const Vec3& v) const
{
    return std::sqrt(DistanceSquared(v));
}

bool Vec3::EpsilonEqual(const Vec3& v, double epsilon) const
{
    return (abs(x - v.x) <= epsilon &&
            abs(y - v.y) <= epsilon &&
            abs(z - v.z) <= epsilon);
}

Vec3 Vec3::GetRandomVector()
{
    return Vec3(GetRandomDouble(), GetRandomDouble(), GetRandomDouble());
}

Vec3 Vec3::GetRandomVector(double min, double max)
{
    return Vec3(GetRandomDouble(min, max), GetRandomDouble(min, max), GetRandomDouble(min, max));
}