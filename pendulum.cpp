#include "pendulum.h"


Pendulum::Pendulum(int r) : DynSphere(r){
    Pendulum(r, 0.0);
    this->state = collision::states::Still;
}

Pendulum::Pendulum(int r, double a) : DynSphere(r){
    angle = a;
    length =14.0;
    pivotPoint = GMlib::Point<float,3>(0.0,0.0,15.0);
    angularVelocity =0.0;
    angularAcceleration = 0.0;
    updatePosition();
    this->state = collision::states::Free;
}

void Pendulum::setAngle(double a){
    angle = a;

}

void Pendulum::setLength(double l){
    length =l;

}

void Pendulum::setPivotPoint(GMlib::Point<float,3> point){
    pivotPoint = point;

}

void Pendulum::updatePosition(){
    //position of the sphere relative to the pivot point

   auto relativePos = GMlib::Vector<float, 3> (length*std::sin(angle), 0.0, -length*std::cos(angle));

   auto pos = relativePos +pivotPoint;
   auto dir = GMlib::Vector<float,3> (std::cos(angle),0.0f,std::sin(angle));

    set(pos,dir,  -relativePos.getNormalized());
    this->velocity = GMlib::Vector<double,3> (length* angularVelocity* std::cos(angle),0.0f,length*angularVelocity* std::sin(angle));

}


void Pendulum::localSimulate(double dt) {

    //friction = 0.1

    angularAcceleration = (-9.81 /length ) * std::sin(angle) - 0.1* angularVelocity ;
    angle +=angularVelocity*dt + 0.5 * angularAcceleration * dt *dt;
    angularVelocity += dt *angularAcceleration;
    updatePosition();
}
