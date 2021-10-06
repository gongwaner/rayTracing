#include "Camera.h"
#include "CommonUtil.h"


Camera::Camera(double verticalFov, float aspectRatio)
{
    double theta = DegreesToRadius(verticalFov);
    double h = tan(theta / 2.0);

    float viewport_height = 2.0 * h;
    float viewport_width = aspectRatio * viewport_height;

    float focal_length = 1.0f;

    origin = Vec3(0.0, 0.0, 0.0);
    horizontal = Vec3(viewport_width, 0.0, 0.0);
    vertical = Vec3(0.0, viewport_height, 0.0);
    lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3(0, 0, focal_length);
}

Ray Camera::GetRay(double u, double v) const
{
    Vec3 direction = lowerLeftCorner + (u * horizontal) + (v * vertical) - origin;
    return Ray(origin, direction);
}
