//
// gui.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May 11 18:57:40 2011 loick michard
// Last update Thu May 12 00:40:48 2011 loick michard
//

#include <QApplication>
#include <QtGui>
#include <sstream>
#include "gui.hpp"

#include "../RenderingConfiguration.hpp"
#include "../Color.hpp"
#include "../Raytracer.hpp"
#include "../CinemaCamera.hpp"
#include "../Point.hpp"
#include "../Vector.hpp"
#include "../Rotation.hpp"
#include "../ObjectPrimitive.hpp"
#include "../Sphere.hpp"
#include "../Spot.hpp"
#include "../Plane.hpp"
#include "../Triangle.hpp"
#include "../Parallelogram.hpp"
#include "../Torus.hpp"
#include "../CubeTroue.hpp"
#include "../PerlinNoise.hpp"
#include "../CubeMap.hpp"
#include "../Sett.hpp"

Scene           *createScene()
{
  Material      mat("base");
  mat.setColor(Color(255, 0, 0, 0));
  mat.setSpecularCoeff(0.2);
  mat.setSpecularPow(50);
  Material      reflection = mat;
  reflection.setReflectionCoeff(1);
  reflection.setTransmissionCoeff(0);
  reflection.setRefractionIndex(1.33);
  Material      refraction = mat;
  refraction.setTransmissionCoeff(0);
  refraction.setRefractionIndex(1.33);
  Material      matFloor("sol");
  matFloor.setReflectionCoeff(0);
  matFloor.setColor(Color(255, 255, 255));
  matFloor.setSpecularCoeff(0.5);
  matFloor.setSpecularPow(50);

  vector<Camera*> cam;
  cam.push_back(new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0)));

  vector<ObjectPrimitive*> primitives;
  primitives.push_back(new Sphere(NULL, Point(30, 0, 0),
				  Rotation(0, 0, 0), reflection, 3.0));
  Material special = refraction;
  PerlinNoise *perlin = new PerlinNoise();
  special.setTransmissionCoeff(0);
  special.setTexture(perlin);

  refraction.setTransmissionCoeff(0.9);
  refraction.setRefractionIndex(1.5);
  vector<Object*> obj;
  obj.push_back(new Object(primitives, Rotation(0, 0, 0), Point(0, 0, 0),
			   true));

  vector<Light*> light;
  //light.push_back(new Spot(Point(10, 5, 2), Color(255, 255, 255)));       
  //light.push_back(new Spot(Point(20, 10, 0), Color(255, 255, 255)));      

  Scene         *res = new Scene(cam, obj, light);
  return (res);
}

void RaytracerGUI::setConfiguration()
{
  _config->setWidth(_ui->_width->value());
  _config->setHeight(_ui->_height->value());
  _config->setCurrentCamera(0);
  _config->setAntialiasing(_ui->_antialiasing->value());
  _config->setFieldDepthSampling(_ui->_depthFieldSampling->value());
  _config->setFieldDepthEnabled(_ui->_depthField->isChecked());
  _config->setExposure(_ui->_exposure->value());
  _config->setDirectLightingCoeff(_ui->_directLightingIntensity->value());
  _config->setDirectLighting(_ui->_directLighting->isChecked());
  _config->setDiffuseLighting(_ui->_diffuseLighting->isChecked());
  _config->setSpecularLighting(_ui->_specularLighting->isChecked());
  _config->setDiffuseShadingSampling(_ui->_diffuseShadingSampling->value());
  _config->setDiffuseShadingEnabled(_ui->_diffuseShading->isChecked());
  _config->setReflection(_ui->_reflection->isChecked(),
			 _ui->_reflectionLimit->value(),
			 _ui->_diffuseReflection->isChecked(),
			 _ui->_diffuseReflectionSampling->value());
  _config->setTransparencyMaxDepth(_ui->_transparencyLimit->value());
  _config->setTransparency(_ui->_transparency->isChecked());
  
  if (_ui->_cubeMap->isChecked())
    {
      if (_cubeMap)
	delete _cubeMap;
      _cubeMap = new CubeMap(_ui->_cubeMapRepertory->text().toStdString());
      _config->setCubeMap(_cubeMap);
    }
  else
    _config->setCubeMap(NULL);
  _config->setBackgroundColor(Color((*_backgroundColor).rgba()));
  _config->setMinimalAmbiantLightingEnabled(_ui->
					    _ambiantLighting->isChecked());
  _config->setMinimalAmbiantLighting(_ui->_ambiantLightingCoeff->value());
  _config->setAdditiveAmbiantLighting((*_ambiantColor).rgba());
  _config->setAdditiveAmbiantLightingEnabled(_ui->_ambiantColor->isChecked());

  _config->setAmbientOcclusionSampling(_ui->
				       _ambientOcclusionSampling->value());
  _config->setAmbientOcclusionEnabled(_ui->_ambientOcclusion->isChecked());

  _config->setPhotonMappingSampling(_ui->
				    _photonMappingValue->value());
  _config->setPhotonMappingEnabled(_ui->_photonMapping->isChecked());
}

void	RaytracerGUI::selectCubeMap()
{
  QString file = 
    QFileDialog::getExistingDirectory(this, 
				      "Selectioner une CubeMap",
				      QString(),
				      QFileDialog::DontUseNativeDialog);
  _ui->_cubeMapRepertory->insert(file);
}

void	RaytracerGUI::selectBackgroundColor()
{
  QColor color = QColorDialog::getColor(*_backgroundColor, this,
					"Selectionner la couleur de fond",
					QColorDialog::ShowAlphaChannel | 
					QColorDialog::DontUseNativeDialog);
  if (color.isValid())
    {
      *_backgroundColor = color;
      ostringstream oss;
      
      oss << "background-color: rgb(" << _backgroundColor->red() <<
	"," << _backgroundColor->green() << "," <<
	_backgroundColor->blue() << ");";
      
      string style = oss.str();
      _ui->_backgroundColor->setStyleSheet(style.c_str());
    }
}

void    RaytracerGUI::selectAmbiantColor()
{
  QColor color = QColorDialog::getColor(*_ambiantColor, this,
                                        "Selectionner la couleur de fond",
                                        QColorDialog::ShowAlphaChannel |
					QColorDialog::DontUseNativeDialog);
  if (color.isValid())
    {
      *_ambiantColor = color;
      ostringstream oss;
      
      oss << "background-color: rgb(" << _ambiantColor->red() <<
	"," << _ambiantColor->green() << "," <<
	_ambiantColor->blue() << ");";
      
      string style = oss.str();
      _ui->_ambiantColorButton->setStyleSheet(style.c_str());
      _ui->_ambiantColor->setChecked(true);
    }
}
#include <iostream>
void	RaytracerGUI::startRender()
{
  setConfiguration();
  if (!_isRendering)
    {
      if (_image)
	delete _image;
      _image = new QImage(_ui->_width->value(),
			  _ui->_height->value(),
			  QImage::Format_ARGB32);
    }
  try
    {
      _raytracer->launchRendering();
      _isRendering = true;
    }
  catch(int error)
    {
      std::cout << "ERREUR" << error << std::endl;
    }
}

void RaytracerGUI::paintEvent(QPaintEvent*)
{
  if (_image)
    {
      *_pixmap = _pixmap->fromImage(*_image);
      _ui->_image->setPixmap(*_pixmap);
    }
}

RaytracerGUI::RaytracerGUI(QWidget *parent)
  : QMainWindow(parent), _ui(new Ui::MainWindow), 
    _config(new RenderingConfiguration()), _raytracer(new Raytracer()),
    _backgroundColor(new QColor(0, 0, 0)), 
    _ambiantColor(new QColor(255, 255, 255)), _cubeMap(NULL),
    _scene(NULL), _image(NULL), _pixmap(new QPixmap()),
    _isRendering(false)
{
  _ui->setupUi(this);
  _ui->_progressBar->setHidden(true);
  QObject::connect(_ui->_cubeMapButton, SIGNAL(clicked()),
  		   this, SLOT(selectCubeMap()));
  QObject::connect(_ui->_backgroundColor, SIGNAL(clicked()),
                   this, SLOT(selectBackgroundColor()));
  QObject::connect(_ui->_ambiantColorButton, SIGNAL(clicked()),
                   this, SLOT(selectAmbiantColor()));
  QObject::connect(_ui->action_Play, SIGNAL(triggered()),
                   this, SLOT(startRender()));
  QObject::connect(_ui->action_Pause, SIGNAL(triggered()),
                   this, SLOT(pauseRendering()));
  QObject::connect(_ui->action_Stop, SIGNAL(triggered()),
                   this, SLOT(stopRendering()));
  _scene = createScene();
  _raytracer->setScene(*_scene);
  _raytracer->setRenderingConfiguration(_config);
  _raytracer->setRenderingInterface(this);
  _timer = new QTimer();
  _timer->setInterval(200);
  _timer->start();
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(repaint()));
}

RaytracerGUI::~RaytracerGUI()
{
  delete _ui;
  delete _config;
  delete _raytracer;
  if (_cubeMap)
    delete _cubeMap;
  if (_scene)
    delete _scene;
  if (_image)
    delete _image;
  delete _pixmap;
}

void		gui(int ac, char **av)
{
  QApplication app(ac, av);

  RaytracerGUI gui;
  gui.show();
  app.exec();
}
