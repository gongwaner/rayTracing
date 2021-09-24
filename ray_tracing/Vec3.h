#ifndef VEC3_H
#define VEC3_H

#include <ostream>

class Vec3
{
private:
    double x;
    double y;
    double z;

public:
    //static variables
    static Vec3 Zero;


    //constructors
    Vec3();
    Vec3(double inX, double inY, double inZ);
    Vec3(const Vec3& v);


    //getter and setters
    double GetX() const     { return x; }
    double GetY() const     { return y; }
    double GetZ() const     { return z; }

    void SetX(double inX);
    void SetY(double inY);
    void SetZ(double inZ);


    //operator overloading
    Vec3 operator-() const;
    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(double t) const;
    Vec3 operator*(const Vec3& v) const;
    Vec3 operator/(double t) const;
    Vec3& operator+=(const Vec3& v);
    Vec3& operator-=(const Vec3& v);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);


    //utility functions
    double Dot(const Vec3& v) const;
    static double Dot(const Vec3& v1, const Vec3& v2);

    Vec3 Cross(const Vec3& v) const;
    static Vec3 Cross(const Vec3& v1, const Vec3& v2);

    double LengthSquared() const;
    double Length() const;

    void Normalize();
    Vec3 GetUnitVector() const;

    double DistanceSquared(const Vec3& v) const;
    double Distance(const Vec3& v) const;

    bool EpsilonEqual(const Vec3& v, double epsilon) const;

    static Vec3 GetRandomVector();
    static Vec3 GetRandomVector(double min, double max);
};


inline Vec3 operator*(double t, const Vec3& v)
{
    return v * t;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.GetX() << " " << v.GetY() << " " << v.GetZ() << std::endl;
}

/**
 * rejection method to pick a random point in unit sphere(r=1)
 * pick a random point in the unit cube where x, y, and z all range from −1 to +1.
 * Reject this point and try again if the point is outside the sphere.
 */
inline Vec3 GetRandomVectorInUnitSphere()
{
    while(true)
    {
        Vec3 p = Vec3::GetRandomVector(-1,1);
        if(p.LengthSquared() >= 1)
            continue;

        return p;
    }
}

#endif //VEC3_H
