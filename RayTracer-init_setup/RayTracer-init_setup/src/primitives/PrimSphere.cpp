#include "PrimSphere.h"

#include <iostream>
#include <utility>

#include "Intersection.h"
#include "Ray.h"

bool PrimSphere::intersect(const Ray& ray, Intersection& out_hit) const {
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */
    using namespace glm;
    constexpr float kEpsilon = 1e-6f;

    /**
     * TODO(Task 2.1):
     * Implement ray-sphere intersection and write the nearest valid hit to `out_hit`.
     *
     * Suggested steps:
     * 1) Build quadratic coefficients for sphere equation.
     * 2) Compute discriminant and reject invalid cases.
     * 3) Pick nearest positive t (front-facing hit only).
     * 4) Compute hit point and unit normal.
     *
     * Once you compute a valid intersection, populate `out_hit` as:
     * out_hit = {t, point, normal, const_cast<PrimSphere *>(this), nullptr};
     *
     * Note:
     * - Model pointer should remain nullptr here; ModelBase assigns it later.
     * - Only accept intersections with t > kEpsilon.
     */
    //slide 62
    float discriminant = sqrt(pow(dot(ray.dir,ray.p0-center),2.0f)-pow(length(ray.p0-center),2.0f)+pow(radius,2.0f));
    if (discriminant < 0.0f) {
        return false;
    }
    float t;
    vec3 q;
    vec3 normal;
    if (discriminant == 0.0f) { //might need to use the kEpsilon to account for floating point error
        t = dot(-ray.dir, ray.p0 - center);
        q = ray.p0 + t * ray.dir;
        normal = normalize(q - center);
        out_hit = { t, q, normal, const_cast<PrimSphere*>(this), nullptr };
    }
    if (discriminant > 0.0f) {
        float positiveSqrtSolutionT = dot(-ray.dir, ray.p0 - center) + discriminant;
        float negativeSqrtSolutionT = dot(-ray.dir, ray.p0 - center) - discriminant;
        t = min(positiveSqrtSolutionT, negativeSqrtSolutionT);
        q = ray.p0 + t * ray.dir;
        normal = normalize(q - center);
        out_hit = { t, q, normal, const_cast<PrimSphere*>(this), nullptr };
    }

    return true;  // Return `true` if intersection happened, otherwise return `false`.
}