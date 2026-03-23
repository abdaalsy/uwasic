#pragma once

#include "hittable.h"

class sphere : public hittable {
public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override { 
        vec3 oc{center - r.origin()};
        auto a{r.direction().length_squared()};
        auto h{dot(r.direction(), oc)};
        auto c{oc.length_squared() - radius*radius};
        auto discriminant{h*h - a*c};

        if (discriminant < 0) { return false; }
        
        auto sqrtd{std::sqrt(discriminant)};

        auto root{(h - sqrtd) / a};
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        } 
        // By the time we get here, root will be whatever root actually is valid

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal{(rec.p - center) / radius}; // normalized [-1, 1]
        rec.set_face_normal(r, outward_normal); // Set front_face flag and normal vector to point out.
        
        return true;
    }
private:
    point3 center;
    double radius;
    // Making these private bc after initialization there's no reason to alter these
};
