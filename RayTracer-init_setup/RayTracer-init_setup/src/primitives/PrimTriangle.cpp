#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include "PrimTriangle.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Intersection.h"
#include "Ray.h"

PrimTriangle::PrimTriangle(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals) {
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

bool PrimTriangle::intersect(const Ray& ray, Intersection& out_hit) const {
    using namespace glm;
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */
    constexpr float kEpsilon = 1e-6f;

    /**
     * TODO(Task 2.2):
     * Implement nearest valid ray-triangle intersection (Moller-Trumbore).
     *
     * Suggested steps:
     * 1) Compute triangle edges.
     * 2) Compute determinant and reject near-parallel rays.
     * 3) Solve barycentric coordinates u, v (inside-triangle checks).
     * 4) Solve t and keep only front-facing hits (t > kEpsilon).
     * 5) Interpolate smooth normal and write `out_hit`.
     *
     * Once valid:
     * out_hit = {t, point, normal, const_cast<PrimTriangle *>(this), nullptr};
     */
    //slide 57
    mat4 pointsAndDir = mat4(vertices[0].x, vertices[0].y, vertices[0].z, 1.0f, vertices[1].x, vertices[1].y, vertices[1].z, 1.0f, vertices[2].x, vertices[2].y, vertices[2].z, 1.0f, -1.0f * ray.dir.x, -1.0f * ray.dir.y, -1.0f * ray.dir.z, 0.0f);
    mat4 pointsAndDirInverse = inverse(pointsAndDir);
    vec4 p0Vector = vec4(ray.p0.x, ray.p0.y, ray.p0.z, 1.0f);
    vec4 lambdasAndT = pointsAndDirInverse * p0Vector;
    if (lambdasAndT.x < 0.0f || lambdasAndT.y < 0.0f || lambdasAndT.z < 0.0f || lambdasAndT.w < 1.0f * kEpsilon) {
        return false;
    }
    vec3 q = lambdasAndT.x * vertices[0] + lambdasAndT.y * vertices[1] + lambdasAndT.z * vertices[2];
    vec3 n = normalize(lambdasAndT.x * normals[0] + lambdasAndT.y * normals[1] + lambdasAndT.z * normals[2]);
    out_hit = { lambdasAndT.w, q, n, const_cast<PrimTriangle*>(this), nullptr };

    return true;  // Return `true` if intersection happened, otherwise return `false`.
}