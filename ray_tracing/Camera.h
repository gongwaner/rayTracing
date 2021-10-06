#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Ray.h"


class Camera
{
private:
    Vec3 origin;
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;

public:
    Camera(double verticalFov, float aspectRatio);
    Ray GetRay(double u, double v) const;
};


#endif //CAMERA_H
