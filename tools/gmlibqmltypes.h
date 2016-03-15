#ifndef GMLIBQMLTYPES_H
#define GMLIBQMLTYPES_H


// GMlib
#include <core/gmcolor>
#include <scene/gmmaterial>


// Qt
#include <QColor>
#include <QObject>





class Color_GM : public GMlib::Color {
  Q_GADGET

  Q_PROPERTY( QColor qcolor READ toQColor WRITE setQColor )

public:
  Color_GM () {}
  Color_GM ( const GMlib::Color& copy ) : Color(copy) {}


  Q_INVOKABLE QColor        toQColor() const;
  void                      setQColor( const QColor& color );


  static GMlib::Color       convertToGMlibColor( const QColor& color );
  static QColor             convertToQColor( const GMlib::Color& color );
};
Q_DECLARE_METATYPE(Color_GM)


class Material_GM : public GMlib::Material {
  Q_GADGET

  Q_PROPERTY( QColor ambient   READ ambient      WRITE setAmbient )
  Q_PROPERTY( QColor diffuse   READ diffuse      WRITE setDiffuse )
  Q_PROPERTY( QColor specular  READ specular     WRITE setSpecular )
  Q_PROPERTY( float  shininess READ getShininess WRITE set )

public:
  Material_GM () {}
  Material_GM (const GMlib::Material& copy ) : Material(copy) {}

  QColor        ambient() const  { return Color_GM::convertToQColor(getAmb()); }
  QColor        diffuse() const  { return Color_GM::convertToQColor(getDif()); }
  QColor        specular() const { return Color_GM::convertToQColor(getSpc()); }

  void          setAmbient( const QColor& color ) { setAmb(Color_GM::convertToGMlibColor(color)); }
  void          setDiffuse( const QColor& color ) { setDif(Color_GM::convertToGMlibColor(color)); }
  void          setSpecular( const QColor& color ) { setSpc(Color_GM::convertToGMlibColor(color)); }



  void                      setQColor( const QColor& color );

};
Q_DECLARE_METATYPE(Material_GM)




void    registerGMlibQmlTypes();


#endif // GMLIBQMLTYPES_H
