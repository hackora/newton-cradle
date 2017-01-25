#include "simulator.h"

/*void SimulationController::add(DynSphere * const sphere)
{
    _dspheres.push_back(sphere);

}

void SimulationController::add(Plane * const plane)
{
    _planes.push_back(plane);

}

void SimulationController::localSimulate(double dt)
{


}*/

Simulator::Simulator(GMlib::Scene& scene) : _scene{scene}
{

}

void Simulator::setupSimulator()
{

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (1.0f, 10.0f, 0.0f);

   /*_planes.push_back(
      std::make_unique<Plane> (    GMlib::Point<float, 3> (-10.0f, -10.0f, 5.0f),
                                   GMlib::Vector<float, 3> (20.0f, 0.0f, 0.0f),
                                   GMlib::Vector<float, 3> (0.0f, 0.0f, -5.0f)));

    _planes.push_back(
      std::make_unique<Plane> (    GMlib::Point<float, 3> (10.0f, -10.0f, 5.0f),
                                   GMlib::Vector<float, 3> (0.0f, 20.0f, 0.0f),
                                   GMlib::Vector<float, 3> (10.0f, 0.0f, -5.0f)));

    _planes.push_back(
      std::make_unique<Plane> (    GMlib::Point<float, 3> (10.0f, 10.0f, 5.0f),
                                   GMlib::Vector<float, 3> (-20.0f, 0.0f, 0.0f),
                                   GMlib::Vector<float, 3> (0.0f, 0.0f, -5.0f)));

    _planes.push_back(
      std::make_unique<Plane> (    GMlib::Point<float, 3> (-10.0f, 10.0f, 5.0f),
                                   GMlib::Vector<float, 3> (0.0f, -20.0f, 0.0f),
                                   GMlib::Vector<float, 3> (0.0f, 0.0f, -5.0f)));*/

   /* _planes.push_back(std::make_unique<Plane> (    GMlib::Point<float, 3> (10.0f, 10.0f, 5.0f),
                                                   GMlib::Vector<float, 3> (-20.0f, -10.0f, -10.0f),
                                                   GMlib::Vector<float, 3> (0.0f, -10.0f, -5.0f)));*/



    for (auto& sphere: _dspheres)
        prepareAndInsert(sphere, 10, 10, 1,1);

    for (auto& plane: _planes)
        prepareAndInsert(plane, 10, 10, 1,1);

   // auto  controller = std::make_unique<collision::MyController> ();

    _scene.insert(&_controller);
}
