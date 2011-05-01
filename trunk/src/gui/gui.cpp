/*
** gui.c for  in /home/laviss_f//raytracer-42
** 
** Made by franck lavisse
** Login   <laviss_f@epitech.net>
** 
** Started on  Tue Apr 26 15:13:06 2011 franck lavisse
// Last update Sun May  1 15:49:43 2011 loick michard
*/
#include <QPixmap>
#include <QPushButton>
#include <QPen>
#include <QBrush>
#include <iostream>
#include <QLabel>
#include <QIcon>
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

using namespace std;

Scene           *createScene()
{
  Material      mat("bleu");
  mat.setColor(Color(255, 155, 55, 0));
  mat.setSpecularCoeff(0.3);
  mat.setSpecularPow(50);
  mat.setReflectionCoeff(0.5);
  mat.setTransmissionCoeff(0.5);
  mat.setRefractionIndex(0.5);
  Material      mat2 = mat;
  mat2.setName("rouge");
  mat2.setColor(Color(255, 255, 255));

  vector<Camera*> cam;
  cam.push_back(new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0)));

  vector<ObjectPrimitive*> sphere;
  sphere.push_back(new Sphere(NULL, Point(30, 0, -5),
                              Rotation(0, 0, 10), mat, 5));
  sphere.push_back(new Sphere(NULL, Point(30, 4, 2),
                              Rotation(0, 0, 0), mat, 2));
  sphere.push_back(new Sphere(NULL, Point(30, -4, 2),
			      Rotation(0, 0, 0), mat, 2));
  sphere.push_back(new Plan(NULL, Point(0, 0, -5),
                            Rotation(0, 0, 0), mat2));
  vector<Object*> obj;
  obj.push_back(new Object(sphere, Rotation(0, 0, 0), Point(0, 0, 0), true));

  vector<Light*> light;
  light.push_back(new Spot(Point(20, -50, 4), Color(255, 0, 0)));
  light.push_back(new Spot(Point(20, 50, 4), Color(0, 255, 0)));
  light.push_back(new Spot(Point(50, 0, 20), Color(255, 255, 255)));

  Scene         *res = new Scene(cam, obj, light);
  return (res);
}

RenderingConfiguration  *createConfig()
{
  RenderingConfiguration *res = new RenderingConfiguration();

  res->setWidth(853);
  res->setHeight(480);
  res->setAntialiasing(1);
  res->setDirectLighting(true);
  res->setReflection(true);
  res->setTransparency(true);
  res->setAmbientOcclusionEnabled(false);
  res->setDiffuseLightingEnabled(false);
  res->setFieldDepthEnabled(false);
  res->setRenderingSamplingMethod(RSM_LINEAR_VERTICAL);
  return (res);
}

void	raytracer(Gui *rt)
{
  RenderingConfiguration	*config = createConfig();

  /*config.setWidth(1100);
  config.setHeight(700);
  config.setAntialiasing(rt->getAliasing());
  config.setDirectLighting(rt->getDirectLight());
  config.setReflectionEnabled(rt->getReflectionBool());
  config.setReflectionDiffusedSampling(rt->getReflectionSampling());
  config.setReflectionMaxDepth(rt->getReflectionProfondeur());
  config.setTransparency(rt->getTransparenceBool(),
			 rt->getTransparenceInt(),
			 rt->getTransparenceDiffusion());
  config.setAmbientOcclusionEnabled(rt->getAmbiantOcclusionBool());
  config.setAmbientOcclusionSampling(rt->getAmbiantOcclusionInt());
  config.setPhotonMappingEnabled(rt->getPhotonMappingBool());
  config.setPhotonMappingSampling(rt->getPhotonMappingInt());
  config.setRenderingSamplingMethod(renderingSamplingMethod(rt->getSamplingMethod()));*/
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
#include <iostream>
void	Gui::putPixelSlot(int x, int y)
{
  QPainter painter(_pixmap);

  painter.setPen(QPen(QColor(255, 0, 0, 255)));
  painter.drawPoint(x, y);
  if (y == 0)
    _label->setPixmap(*_pixmap);
}

void	Gui::init_dock(void)
{
  _widget = new QWidget();
  _Grid = new QGridLayout();
  _Dock = new QDockWidget();
  QPushButton *Rendu = new QPushButton("Rendu", _Dock);

  _Dock->setAllowedAreas(Qt::LeftDockWidgetArea |
			 Qt::RightDockWidgetArea);
  Rendu->setCursor(Qt::PointingHandCursor);
  QObject::connect(Rendu, SIGNAL(clicked()), this, SLOT(launch_raytracer()));
  _Grid->addWidget(Rendu, 250, 0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
  addDockWidget(Qt::LeftDockWidgetArea, _Dock);
  _widget->setMaximumHeight(550);
}

Gui::Gui() : QMainWindow()
{
  resize(1400, 800);
  _label = new QLabel();

  //_image = new QImage(853, 480, QImage::Format_ARGB32);

  //_pixmap->fill(QColor(255, 255, 255, 255));
  _pixmap = new QPixmap(853, 480);//QPixmap::fromImage(*_image);
  _label->setPixmap(*_pixmap);
  setCentralWidget(_label);

  putPixel(Color(255, 0, 0), 10, 10);
  //_Scene = new QGraphicsScene();
  //QPen	 Pen(Qt::black, 0, Qt::SolidLine);
  //QBrush Brush(Qt::black);
  //QPolygon* Polygon = new QPolygon();
  //*Polygon << QPoint(0, 0) << QPoint(1100, 0)
  //	   << QPoint(1100, 700) << QPoint(0, 700);
  //_Scene->addPolygon(*Polygon, Pen, Brush);
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
