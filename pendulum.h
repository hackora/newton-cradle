#ifndef PENDULUM_H
#define PENDULUM_H

#include <parametrics/gmpsphere>

#include <memory.h>
#include<collision_library.h>

using DynSphere = collision::DynamicPhysObject<GMlib::PSphere<float>>;

class Pendulum : public DynSphere{
public:
    Pendulum(int r);
    Pendulum(int r, double a);
    void setAngle(double);
    void setLength(double);
    void setPivotPoint(GMlib::Point<float, 3>);


protected:
    void localSimulate(double dt) override;

private:

    GMlib::Point<float,3>  pivotPoint;
    double                              angle;
    double                              angularVelocity;
    double                              angularAcceleration;
    double                              length;

    void                                   updatePosition();


};

#endif // PENDULUM_H
