#ifndef __MATTE_GLOSSY_MATERIAL_H__
#define __MATTE_GLOSSY_MATERIAL_H__

#include <glm/glm.hpp>

#include "MaterialBase.h"

class MatteGlossyMaterial : public MaterialBase {
   public:
    glm::vec3 albedo;
    float shininess;

    explicit MatteGlossyMaterial(glm::vec3 albedo, float shiny)
        : albedo(SRGBToLinear(glm::clamp(albedo, glm::vec3(0.0f), glm::vec3(1.0f)))), shininess(shiny) {}

    Ray sample_ray_and_update_radiance(Ray &ray, Intersection &intersection) override;
    glm::vec3 color_of_last_bounce(Ray &ray, Intersection &intersection, Scene const &scene) override;

   private:
    glm::vec3 get_direct_lighting(Intersection const &intersection, Scene const &scene) const;
};

#endif
