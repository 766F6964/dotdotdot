//
// Created by void on 6/4/20.
//

#ifndef MY_SOLUTION_PARTICLESOLVER_H
#define MY_SOLUTION_PARTICLESOLVER_H

// Order of computations

//clearForces();
//updateGrid();
//computeDensityPressure();
//computePressureForce();
//computeViscousForce();
//computeRepulsion();
//computeGravityForce();
//step(dt);

#include <vector>
#include "particle.h"

class particlesolver {
public:

    void initSPH();

    void integrate();

    void compute_density_pressure();

    void compute_pressure_force();

    void compute_viscous_force();

    void compute_repulsion();

    void compute_gravity_force();

    void update();

private:

    std::vector<particle> particles;

};


#endif //MY_SOLUTION_PARTICLESOLVER_H
