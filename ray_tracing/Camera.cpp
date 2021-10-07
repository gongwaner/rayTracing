#include "Camera.h"
#include "CommonUtil.h"


Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up,
               double verticalFov, float aspectRatio)
{
    //assume z = -1. tan(theta/2)=h/z. hence h=tan(theta/2)
    double theta = DegreesToRadius(verticalFov);
    double h = tan(theta / 2.0);

    float viewport_height = 2.0 * h;
    float viewport_width = aspectRatio * viewport_height;

    Vec3 w = (lookFrom - lookAt).GetUnitVector();
    Vec3 u = Vec3::Cross(up, w);
    Vec3 v = Vec3::Cross(w, u);

    origin = lookFrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - w;
}

Ray Camera::GetRay(double u, double v) const
{
    Vec3 direction = lowerLeftCorner + (u * horizontal) + (v * vertical) - origin;
    return Ray(origin, direction);
}
