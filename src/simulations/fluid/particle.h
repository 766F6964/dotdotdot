//
// Created by void on 6/3/20.
//

#ifndef DOTS_PARTICLE_H
#define DOTS_PARTICLE_H

// References:
// https://www.youtube.com/watch?v=NJBz8rMJ0ZU


#include "vec2d.h"

// https://www.lucasschuermann.com/writing/implementing-sph-in-2d

class particle {
public:

    particle(int x, int y);

    vec2d position;
    vec2d velocity;
    vec2d force;

    float pressure{};
    float density{};

private:

};


#endif //DOTS_PARTICLE_H
