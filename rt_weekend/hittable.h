#pragma once
// Gonna create an abstract class for anything a ray can hit, that'll let us use the same interface for many different types of objects

class material;

class hit_record {
public:
    point3 p;
    vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face; // normal will always point out, so use this flag to know whether this hit record is for the back side, or the front side. Then at color time, we can invert the normal vector if its the back face

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector to always point out
        // NOTE: assume outward_normal has unit length

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};


// when we wanna check if an object got hit, we use the hittable class and override the hit method for each type of object. the hit method will count a hit and update the hit record iff tmin <= t <= tmax.
class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0; // Different types of objects inherit this class and must provide an implementation for this method, the "= 0;" enforces this so we don't forget
};
