#ifndef COLORF_H
#define COLORF_H


class Colorf
{
private:
    float r;
    float g;
    float b;
    float a;

public:
    //constructors
    Colorf(float inR, float inG, float inB, float inA = 1.0f);
    Colorf(int inR, int inG, int inB, int inA = 255);
    Colorf(float rgba[4]);
    Colorf(float greyscale, float inA = 1.0f);


    //getter and setters
    float GetR() const      { return r; }
    float GetG() const      { return g; }
    float GetB() const      { return b; }
    float GetA() const      { return a; }

    void SetRGB(float inR, float inG, float inB);
    void SetRGBA(float inR, float inG, float inB, float inA);
    void SetR(float inR);
    void SetG(float inG);
    void SetB(float inB);
    void SetA(float inA);


    //operator overloading
    Colorf operator+(const Colorf& c) const;
    Colorf operator-(const Colorf& c) const;
    Colorf operator*(float f) const;
    Colorf operator/(float f) const;
    Colorf& operator+=(const Colorf& c);
    Colorf& operator*=(float f);
    bool operator==(const Colorf& c) const;


    //utility functions
    Colorf Lerp(const Colorf& c, float t) const;
    float Luminance() const;


    //static variables
    static Colorf Black;
    static Colorf White;
    static Colorf Red;
    static Colorf Green;
    static Colorf Blue;
    static Colorf SkyBlue;
    static Colorf Yellow;
    static Colorf Cyan;
    static Colorf Magenta;
    static Colorf Purple;
    static Colorf Navy;
    static Colorf Orange;
};

inline Colorf operator*(double t, const Colorf& v)
{
    return v * t;
}

#endif //COLORF_H
