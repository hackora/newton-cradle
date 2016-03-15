#ifndef TESTTORUS_H
#define TESTTORUS_H


#include <parametrics/gmptorus>


class TestTorus : public GMlib::PTorus<float> {
  GM_SCENEOBJECT(TestTorus)
public:
  using PTorus::PTorus;

  ~TestTorus() override {

    if(_test01)
      remove(test_01_torus.get());
  }

  void test01() {

    GMlib::Vector<float,3> d = evaluate(0.0f,0.0f,0,0)[0][0];
    test_01_torus = std::make_shared<TestTorus,float,float,float>(1.5f,0.5f,0.5f);

    test_01_torus->translate(d + d.getNormalized()*2.0f);
    test_01_torus->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
    test_01_torus->toggleDefaultVisualizer();
    test_01_torus->replot(200,200,1,1);
    insert(test_01_torus.get());

    _test01 = true;
  }

  const GMlib::Angle&             getRotationSpeed() const { _rot_speed; }
  const GMlib::Vector<float,3>&   getRotationAxel() const { _rot_axel; }

protected:
  void localSimulate(double dt) override {

    rotate( GMlib::Angle(_rot_speed) * dt, _rot_axel );
  }

private:
  bool _test01 {false};
  std::shared_ptr<TestTorus> test_01_torus {nullptr};

  GMlib::Angle              _rot_speed {90};
  GMlib::Vector<float,3>    _rot_axel { 0.3f, 0.5f, 1.0f };

}; // END class TestTorus



#endif // TESTTORUS_H
