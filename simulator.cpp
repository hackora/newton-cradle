#include "simulator.h"
#include "testtorus.h"

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

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 2.0f, 0.0f);

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 2.0f, 3.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{5.0f,3.0f,3.0f});

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 2.0f, 3.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-5.0f,3.0f,3.0f});

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, -2.0f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,0.0f,5.0f});

//   _planes.push_back(
//      std::make_unique<Plane> (    GMlib::Point<float, 3> (-10.0f, -10.0f, 5.0f),
//                                   GMlib::Vector<float, 3> (20.0f, 0.0f, 0.0f),
//                                   GMlib::Vector<float, 3> (0.0f, 0.0f, -5.0f)));

//    _planes.push_back(
//      std::make_unique<Plane> (    GMlib::Point<float, 3> (10.0f, -10.0f, 5.0f),
//                                   GMlib::Vector<float, 3> (0.0f, 20.0f, 0.0f),
//                                   GMlib::Vector<float, 3> (10.0f, 0.0f, -5.0f)));

//    _planes.push_back(
//      std::make_unique<Plane> (    GMlib::Point<float, 3> (10.0f, 10.0f, 5.0f),
//                                   GMlib::Vector<float, 3> (-20.0f, 0.0f, 0.0f),
//                                   GMlib::Vector<float, 3> (0.0f, 0.0f, -5.0f)));

    _planes.push_back(
      std::make_unique<Plane> (    GMlib::Point<float, 3> (-10.0f, 0.0f, 0.0f),
                                   GMlib::Vector<float, 3> (10.0f, -10.0f, 0.0f),
                                   GMlib::Vector<float, 3> (10.0f, 10.0f, 0.0f)));
    _planes.back()->setMaterial(GMlib::GMmaterial::polishedSilver());

//    _planes.push_back(std::make_unique<Plane> (    GMlib::Point<float, 3> (10.0f, 10.0f, 5.0f),
//                                                   GMlib::Vector<float, 3> (-20.0f, -20.0f, -10.0f),
//                                                   GMlib::Vector<float, 3> (0.0f, -10.0f, 5.0f)));

//     _dspheres.push_back(std::make_unique<DynSphere> ());
//     _dspheres.back()->velocity = GMlib::Vector<double, 3>{0.0, 2.1, 0.0};
//     _dspheres.back()->translate(GMlib::Vector<float,3>{1.0f,-3.0f,0.0f});

//     _dspheres.push_back(std::make_unique<DynSphere> ());
//     _dspheres.back()->velocity = GMlib::Vector<double, 3>{0.0, -2.1, 0.0};;
//     _dspheres.back()->translate(GMlib::Vector<float,3>{1.0f,3.0f,0.0f});


//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 5.0f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{5.0f,2.0f,3.0f});

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-6.0f,5.0f,4.0f});  //checkpoint

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, -5.0f, -4.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,5.0f,5.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

   _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (-2.0f, 0.0f, 0.0f); //crash
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,5.0f,4.0f});
   _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (-2.0f, 0.0f, 0.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,0.0f,5.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (-3.0f, 0.0f, 0.0f); //crash
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-5.0f,5.0f,7.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, -0.5f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{2.0f,7.0f,3.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (1.0f, 1.0f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{2.0f,3.0f,5.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (-3.0f, -3.0f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{3.0f,2.0f,5.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (5.0f, 5.0f, 2.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-2.0f,-1.0f,6.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());



//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (-2.0f, -2.0f, 7.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,2.0f,6.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (4.0f, 0.0f, 9.0f); //crash
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-6.0f,3.0f,2.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, -2.0f, 0.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{3.0f,2.3f,5.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (3.0f, 2.0f, 2.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{1.0f,-1.0f,5.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

//    _dspheres.push_back(std::make_unique<DynSphere> ());
//    _dspheres.back()->velocity = GMlib::Vector<double,3> (-3.0f, 3.0f, 2.0f);
//    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{5.0f,3.0f,5.0f});
//    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (5.0f, 5.0f, 2.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,-4.0f,5.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());


    //box

    _planes.push_back(std::make_unique<Plane>(
                           GMlib::Point<float,3>(-10.0f, -10.0f, 5.0f),
                           GMlib::Vector<float,3>(20.0f, 0.0f, 0.0f),
                           GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f) ));

    _planes.back()->setMaterial(GMlib::GMmaterial::sapphire());

    _planes.push_back(std::make_unique<Plane>(
                           GMlib::Point<float,3>(10.0f, -10.0f, 5.0f),
                           GMlib::Vector<float,3>(0.0f, 20.0f, 0.0f),
                           GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f) ));

     _planes.back()->setMaterial(GMlib::GMmaterial::sapphire());

    _planes.push_back(std::make_unique<Plane>(
                           GMlib::Point<float,3>(-10.0f, 10.0f, 5.0f),
                           GMlib::Vector<float,3>(0.0f, -20.0f, 0.0f),
                           GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f) ));

     _planes.back()->setMaterial(GMlib::GMmaterial::sapphire());

    _planes.push_back(std::make_unique<Plane>(
                           GMlib::Point<float,3>(10.0f, 10.0f, 5.0f),
                           GMlib::Vector<float,3>(-20.0f, 0.0f, 0.0f),
                           GMlib::Vector<float,3>(0.0f, 0.0f, -5.0f) ));

     _planes.back()->setMaterial(GMlib::GMmaterial::sapphire());


    //bug

        _dspheres.push_back(std::make_unique<DynSphere> ());
        _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f,-1.0f,0.0f);
        _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-3.0f,3.0f,5.0f});
        _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());


        _dspheres.push_back(std::make_unique<DynSphere> ());
        _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, -1.0f, 0.0f);
        _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{5.0f,3.0f,5.0f});
        _dspheres.back()->setMaterial(GMlib::GMmaterial::polishedRed());


//        _dspheres.push_back(std::make_unique<DynSphere> ());
//        _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
//        _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-3.8f,2.0f,2.0f});
//        _dspheres.back()->setMaterial(GMlib::GMmaterial::plastic());

    for (auto& plane: _planes)
        prepareAndInsert(plane, 10, 10, 1,1);

    for (auto& sphere: _dspheres){
        sphere->sphereController = &_controller;
        prepareAndInsert(sphere, 10, 10, 1,1);
    }

    double dt = 0.016;
    _scene.enabledFixedDt ();
    _scene.setFixedDt (dt);

    _scene.insert(&_controller);


}

void Simulator::setupGame(){

    //Newton cradle

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,5.0f,2.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::pewter());

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{1.9f,5.0f,2.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::jade());

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-1.9f,5.0f,2.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::obsidian());

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{3.8f,5.0f,2.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::chrome());

    _dspheres.push_back(std::make_unique<DynSphere> ());
    _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
    _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-3.8f,5.0f,2.0f});
    _dspheres.back()->setMaterial(GMlib::GMmaterial::plastic());



    //Bézier surface

    GMlib::DMatrix<GMlib::Vector<float,3>> bs_cp(3,3);
    bs_cp[0][0] = { 0.0f,  0.0f,  0.0f};
    bs_cp[1][0] = { -5.0f,  0.0f,  0.0f};
    bs_cp[2][0] = {-10.0f,  0.0f,  0.0f};
    bs_cp[0][1] = { 0.0f,  -5.0f,  0.0f};
    bs_cp[1][1] = { -5.0f,  -5.0f, -10.0f};
    bs_cp[2][1] = {-10.0f,  -5.0f,  0.0f};
    bs_cp[0][2] = { 0.0f, -10.0f,  0.0f};
    bs_cp[1][2] = { -5.0f, -10.0f,  0.0f};
    bs_cp[2][2] = {-10.0f, -10.0f,  0.0f};

    _beziers.push_back(std::make_unique<Bezier>(bs_cp));
    _beziers.back()->translateGlobal(GMlib::Vector<float,3>{5.0f,0.0f,-4.0f});
    _beziers.back()->rotate( GMlib::Angle(-45) , GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
     _beziers.back()->setMaterial(GMlib::GMmaterial::sapphire());


     //Balls on surface

     _dspheres.push_back(std::make_unique<DynSphere> (0.5));
     _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
     _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{0.0f,-3.0f,-2.5f});
     _dspheres.back()->setMaterial(GMlib::GMmaterial::blackRubber());

     _dspheres.push_back(std::make_unique<DynSphere> (0.5));
     _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
     _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{1.0f,-3.0f,-2.5f});
     _dspheres.back()->setMaterial(GMlib::GMmaterial::blackRubber());

     _dspheres.push_back(std::make_unique<DynSphere> (0.5));
     _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
     _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-1.0f,-3.0f,-2.5f});
     _dspheres.back()->setMaterial(GMlib::GMmaterial::blackRubber());

     _dspheres.push_back(std::make_unique<DynSphere> (0.5));
     _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
     _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{2.0f,-3.0f,-2.5f});
     _dspheres.back()->setMaterial(GMlib::GMmaterial::blackRubber());

     _dspheres.push_back(std::make_unique<DynSphere> (0.5));
     _dspheres.back()->velocity = GMlib::Vector<double,3> (0.0f, 0.0f, 0.0f);
     _dspheres.back()->translateGlobal(GMlib::Vector<float,3>{-2.0f,-3.0f,-2.5f});
     _dspheres.back()->setMaterial(GMlib::GMmaterial::blackRubber());


    for (auto& bezier: _beziers)
        prepareAndInsert(bezier, 10, 10, 1,1);

    for (auto& sphere: _dspheres){
        sphere->sphereController = &_controller;
        prepareAndInsert(sphere, 10, 10, 1,1);
    }

     _scene.insert(&_controller);


}

