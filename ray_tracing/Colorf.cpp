#include <algorithm>//for std::clamp
#include "Colorf.h"


//static variables
Colorf Colorf::Black = Colorf(0, 0, 0, 255);
Colorf Colorf::White = Colorf(255, 255, 255, 255);
Colorf Colorf::Red = Colorf(255, 0, 0, 255);
Colorf Colorf::Green = Colorf(0, 255, 0, 255);
Colorf Colorf::Blue = Colorf(0, 0, 255, 255);
Colorf Colorf::SkyBlue = Colorf(128, 179, 255, 255);
Colorf Colorf::Yellow = Colorf(255, 255, 0, 255);
Colorf Colorf::Cyan = Colorf(0, 255, 255, 255);
Colorf Colorf::Magenta = Colorf(255, 0, 255, 255);
Colorf Colorf::Purple = Colorf(161, 16, 193, 255);
Colorf Colorf::Navy = Colorf(16, 16, 128, 255);
Colorf Colorf::Orange = Colorf(230, 73, 16, 255);


//constructors
Colorf::Colorf(float inR, float inG, float inB, float inA) : r(inR), g(inG), b(inB), a(inA)
{
}

Colorf::Colorf(int inR, int inG, int inB, int inA)
{
    const float scale = 1.0f / 255.0f;

    r = std::clamp((float) inR, 0.0f, 255.0f) * scale;
    g = std::clamp((float) inG, 0.0f, 255.0f) * scale;
    b = std::clamp((float) inB, 0.0f, 255.0f) * scale;
    a = std::clamp((float) inA, 0.0f, 255.0f) * scale;
}

Colorf::Colorf(float rgba[4])
{
    r = rgba[0];
    g = rgba[1];
    b = rgba[2];
    a = rgba[3];
}

Colorf::Colorf(float greyscale, float inA)
{
    r = greyscale;
    g = greyscale;
    b = greyscale;
    a = inA;
}


//getter and setters
void Colorf::SetRGB(float inR, float inG, float inB)
{
    r = inR;
    g = inG;
    b = inB;
}

void Colorf::SetRGBA(float inR, float inG, float inB, float inA)
{
    r = inR;
    g = inG;
    b = inB;
    a = inA;
}

void Colorf::SetR(float inR)
{
    r = inR;
}

void Colorf::SetG(float inG)
{
    g = inG;
}

void Colorf::SetB(float inB)
{
    b = inB;
}

void Colorf::SetA(float inA)
{
    a = inA;
}


//operator overloading
Colorf Colorf::operator+(const Colorf& c) const
{
    return Colorf(r + c.r, g + c.g, b + c.b, a + c.a);
}

Colorf Colorf::operator-(const Colorf& c) const
{
    return Colorf(r - c.r, g - c.g, b - c.b, a - c.a);
}

Colorf Colorf::operator*(float f) const
{
    return Colorf(r * f, g * f, b * f, a * f);
}

Colorf Colorf::operator/(float f) const
{
    return operator*(1 / f);
}

Colorf& Colorf::operator+=(const Colorf& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;

    return *this;
}

Colorf& Colorf::operator*=(float f)
{
    r *= f;
    g *= f;
    b *= f;
    a *= f;

    return *this;
}

bool Colorf::operator==(const Colorf& c) const
{
    return (r == c.r && g == c.g && b == c.b && a == c.a);
}


//utility functions
Colorf Colorf::Lerp(const Colorf& c, float t) const
{
    return Colorf(r * t + c.r * (1 - t), g * t + c.g * (1 - t), b * t + c.b * (1 - t), a * t + c.a * (1 - t));
}

float Colorf::Luminance() const
{
    return 0.299f * r + 0.587f * g + 0.114f * b;
}
