#ifndef VEC3_H
#define VEC3_H

class Vec3
{
private:
    double x;
    double y;
    double z;

public:
    static Vec3 Zero;

    //constructors
    Vec3();
    Vec3(double inX, double inY, double inZ);

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
};

#endif //VEC3_H
