//
// Created by void on 6/3/20.
//

#include "particle.h"

particle::particle(int x, int y) {
    this->position.x = x;
    this->position.y = y;
    this->velocity.x = 0.0f;
    this->velocity.y = 0.0f;
    this->force.x = 0.0f;
    this->force.y = 0.0f;
    this->density = 0.0f;
    this->pressure = 0.0f;
}
