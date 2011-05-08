/*
** gui.c for  in /home/laviss_f//raytracer-42
** 
** Made by franck lavisse
** Login   <laviss_f@epitech.net>
** 
** Started on  Tue Apr 26 15:13:06 2011 franck lavisse
// Last update Sun May  8 13:29:37 2011 samuel olivier
*/
#include <QPixmap>
#include <QPushButton>
#include <QPen>
#include <QBrush>
#include <iostream>
#include <QLabel>
#include <QIcon>
#include <QFrame>
#include <QTimer>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SDL/SDL.h>
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
#include "../Plan.hpp"
#include "../Triangle.hpp"
#include "../Parallelogram.hpp"
#include "../Torus.hpp"
#include "../CubeTroue.hpp"
#include "../PerlinNoise.hpp"
#include "../CubeMap.hpp"

using namespace std;

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
  // primitives.push_back(new CubeTroue(NULL, Point(23, 5, 0),
  //                                    Rotation(0.3, 0.5, 0), reflection));
  // primitives.push_back(new Torus(NULL, Point(23, -5, 0),
  //                                Rotation(0.3, 0.5, 0), reflection, 3, 0.8));
  primitives.push_back(new Sphere(NULL, Point(30, 0, 0),            
                             Rotation(0, 0, 0), reflection, 1.0));           
  Material special = refraction;
  PerlinNoise *perlin = new PerlinNoise();//new Texture("heightmap.png");  //perlin->setMarbleProperties();                                              
  //special.setHeightmap(perlin);                                               
  special.setTransmissionCoeff(0);
  special.setTexture(perlin);
  // primitives.push_back(new Sphere(NULL, Point(20, -4, 0),
  //Rotation(0, 0, 0), special, 3));              
  // primitives.push_back(new Sphere(NULL, Point(18, 4, 0),
  //                              Rotation(0, 0, 0), reflection, 3));           
  //primitives.push_back(new Triangle(NULL, Point(7.5, -1.5, -1), Rotation(0, 0,0),                                                                            
//                                special, Point(5, 1.5, -1),                 
//                                Point(7.5, 0, 0)));                         
  refraction.setTransmissionCoeff(0.9);
  refraction.setRefractionIndex(1.5);
//  primitives.push_back(new Plan(NULL, Point(0, 0, -5),                      
//                            Rotation(0, 0, 0), matFloor));                  
vector<Object*> obj;
obj.push_back(new Object(primitives, Rotation(0, 0, 0), Point(0, 0, 0),
			 true));

vector<Light*> light;
//light.push_back(new ParrallelLight(Point(0, -3, -3), Color(255, 255, 255)))\
;                                                                               
//light.push_back(new Spot(Point(10, 5, 2), Color(255, 255, 255)));           
//light.push_back(new Spot(Point(20, 10, 0), Color(255, 255, 255)));          

Scene         *res = new Scene(cam, obj, light);
return (res);
}

RenderingConfiguration  *createConfig()
{
  RenderingConfiguration *res = new RenderingConfiguration();

  res->setWidth(853);
  res->setHeight(480);
  res->setAntialiasing(4);
  res->setExposure(2);
  res->setDiffuseLighting(true);
  res->setDirectLighting(true);
  res->setDirectLightingCoeff(1);
  res->setSpecularLighting(true);
  res->setReflection(true);
  res->setTransparency(true);
  res->setAmbientOcclusionEnabled(false);
  res->setDiffuseShadingEnabled(false);
  res->setFieldDepthEnabled(false);
  // res->setAdditiveAmbiantLighting(0->1);                                       
  // res->setMinimalAmbiantLighting(0->1);                                        
  res->setRenderingSamplingMethod(RSM_LINEAR_HORIZONTAL);
  res->setCubeMap(new CubeMap("cubemaps/Tantolunden6"));  
  return (res);
}

void	raytracer(Gui *rt)
{
  RenderingConfiguration	*config = createConfig();

  config->setWidth(1100);
  config->setHeight(700);
  config->setAntialiasing(rt->getAliasing());
  config->setDirectLighting(rt->getDirectLight());
  config->setReflectionEnabled(rt->getReflectionBool());
  config->setReflectionDiffusedSampling(rt->getReflectionSampling());
  config->setReflectionMaxDepth(rt->getReflectionProfondeur());
  config->setTransparency(rt->getTransparenceBool(),
			 rt->getTransparenceInt(),
			 rt->getTransparenceDiffusion());
  config->setAmbientOcclusionEnabled(rt->getAmbiantOcclusionBool());
  config->setAmbientOcclusionSampling(rt->getAmbiantOcclusionInt());
  config->setPhotonMappingEnabled(rt->getPhotonMappingBool());
  config->setPhotonMappingSampling(rt->getPhotonMappingInt());
  config->setRenderingSamplingMethod(renderingSamplingMethod(rt->getSamplingMethod()));
  Scene *scene = createScene();

  rt->_raytracer.setScene(*scene);
  rt->_raytracer.setRenderingConfiguration(config);
  rt->_raytracer.setRenderingInterface(rt);
  rt->_raytracer.launchRendering();
}

void	Gui::launch_raytracer(void)

{ 
  cout << "test" << endl;
  raytracer(this);
}

void	Gui::putPixelSlot(int x, int y)
{
  QPainter painter(_pixmap);

  painter.setPen(QPen(QColor(255, 0, 0, 255)));
  painter.drawPoint(x, y);
  if (y == 0)
    _label->setPixmap(*_pixmap);
}

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void	Gui::init_dock(void)
{
  _widget = new QWidget();
  _Grid = new QGridLayout();
  _Dock = new QDockWidget();
  QPushButton *Rendu = new QPushButton("Rendu", _Dock);

  _Dock->setAllowedAreas(Qt::LeftDockWidgetArea |
			 Qt::RightDockWidgetArea);
  Rendu->setCursor(Qt::PointingHandCursor);
  // QObject::connect(this, SIGNAL(perso()), this, SLOT(repaint()));
   QObject::connect(Rendu, SIGNAL(clicked()), this, SLOT(launch_raytracer()));
  _Grid->addWidget(Rendu, 250, 0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
  addDockWidget(Qt::LeftDockWidgetArea, _Dock);
  _widget->setMaximumHeight(550);
}

void	Gui::paintEvent(QPaintEvent*) {
  *_pixmap = _pixmap->fromImage(*_image);
  _pixlabel->setPixmap(*_pixmap);
}

Gui::Gui() : QMainWindow()
{
  QTimer timer;
  Color	pixelColor;

  resize(1400, 800);
  _image = new QImage(1130, 720, QImage::Format_ARGB32);
  _pixlabel = new QLabel();
  setCentralWidget(_pixlabel);
  _pixmap = new QPixmap(1130, 720);
  pixelColor.setR(0);
  pixelColor.setG(255);
  pixelColor.setB(0);
  timer.setInterval(10000000);
  QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
  _pixmap->fill(Qt::black);
}

void	Gui::rendu(void){}

Gui::~Gui() {}

int	gui(int argc, char **argv)
{
  QApplication	app(argc, argv);
  Gui		rt_gui;
  
  rt_gui.init_dock();
  rt_gui.samplingMethod();
  rt_gui.aliasing();
  rt_gui.reflection();
  rt_gui.directLight();
  rt_gui.ambiantOcclusion();
  rt_gui.photonMapping();
  rt_gui.lumiereDiffuse();
  rt_gui.flou();
  rt_gui.transparence();
  rt_gui.menuBar();
  rt_gui.show();
  return (app.exec());
}

//int	main(int argc, char **argv) {gui(argc,argv);return(0);}
