#pragma once

#include "hittable.h"

// The material of some object decides two things
// 1. how a ray will be scattered
// 2. how much that scattered ray should matter in the final colour

// A mirror would have very small scattering, and should not absorb at all meaning that the next reflection maintains all its colour on the point of the mirror our ray hit
class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray&scattered) const {
        return false;
    }
};

class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};

class metal : public material {
public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected)  + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    color albedo;
    double fuzz;
};
