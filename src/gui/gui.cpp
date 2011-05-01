/*
** gui.c for  in /home/laviss_f//raytracer-42
** 
** Made by franck lavisse
** Login   <laviss_f@epitech.net>
** 
** Started on  Tue Apr 26 15:13:06 2011 franck lavisse
// Last update Sun May  1 11:54:33 2011 franck lavisse
*/
#include <QPushButton>
#include <QPen>
#include <QBrush>
#include <iostream>
#include <QIcon>
#include "gui.hpp"
#include "../RenderingConfiguration.hpp"
#include "../Color.hpp"

using namespace std;

void	raytracer(Gui *rt)
{
  RenderingConfiguration	config;

  config.setWidth(1100);
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
  config.setRenderingSamplingMethod(renderingSamplingMethod(rt->getSamplingMethod()));
}

void	Gui::launch_raytracer(void)
{
  cout << "test" << endl;
  raytracer(this);
}

void	Gui::init_dock(void)
{
  _widget = new QWidget();
  _Grid = new QGridLayout();
  _Dock = new QDockWidget();
  QPushButton *Rendu = new QPushButton("Rendu", _Dock); 
  setCentralWidget(_View);
  _Dock->setAllowedAreas(Qt::LeftDockWidgetArea|
			 Qt::RightDockWidgetArea);
  Rendu->setCursor(Qt::PointingHandCursor);
  QObject::connect(Rendu, SIGNAL(clicked()), this, SLOT(launch_raytracer()));
  _Grid->addWidget(Rendu, 250, 0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
  addDockWidget(Qt::LeftDockWidgetArea, _Dock);
  _widget->setMaximumHeight(520);
}

Gui::Gui() : QMainWindow()
{
  QColor	Color;

  setFixedSize(1400, 800);
  _Scene = new QGraphicsScene();
  QPen	 Pen(Qt::black, 0, Qt::SolidLine);
  QBrush Brush(Qt::black);
  QPolygon Polygon;
  Polygon << QPoint(0, 0) << QPoint(1100, 0)
	  << QPoint(1100, 700) << QPoint(0, 700);
  _Item = _Scene->addPolygon(Polygon, Pen, Brush);
  _View = new QGraphicsView(_Scene);
}

void	Gui::rendu(void){}

Gui::~Gui() {}

int	gui(int argc, char **argv)
{
  QApplication	app(argc, argv);
  Gui		rt_gui;

  rt_gui.show();
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
  return (app.exec());
}

//int	main(int argc, char **argv) {gui(argc,argv);return(0);}
