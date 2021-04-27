#include "Plane.h"

Plane::Plane() {
    p.x = 0;
    p.y = 0;
    p.z = 0;
    p.w = 0;
}
Plane::Plane(const vec3& P1, const vec3& P2, const vec3& P3) {
    normal = glm::normalize(cross(P2 - P1, P3 - P1));

    vec3 normalizedNormal = normalize(normal);

    p.x = normalizedNormal.x;
    p.y = normalizedNormal.y;
    p.z = normalizedNormal.z;
    p.w = -dot(P1, normalizedNormal);
 }

Plane Plane::CreatePlaneFrom3Points(const vec3& P1, const vec3& P2, const vec3& P3)
{
    normal = glm::normalize(cross(P2 - P1, P3 - P1));
    
    vec3 normalizedNormal = normalize(normal);
    
    Plane result;
   result.p.x = normalizedNormal.x;
   result.p.y = normalizedNormal.y;
   result.p.z = normalizedNormal.z;
   result.p.w = -dot(P1, normalizedNormal);
   result.normal = normal;
   return result;
}

float Plane::SignedDistance(const vec3& p_)
{
    return (normal.x * p_.x + normal.y * p_.y + normal.z * p_.z + p.w);
}
