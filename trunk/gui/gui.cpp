/*
** gui.c for  in /home/laviss_f//raytracer-42
** 
** Made by franck lavisse
** Login   <laviss_f@epitech.net>
** 
** Started on  Tue Apr 26 15:13:06 2011 franck lavisse
// Last update Fri Apr 29 18:05:56 2011 franck lavisse
*/
#include <iostream>
#include "gui.hpp"

using namespace std;

void	raytracer(Gui *rt) {rt = rt;}

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
  _Rendu = new QPushButton("Rendu", _Dock); 
  setCentralWidget(_View);
  _Dock->setAllowedAreas(Qt::LeftDockWidgetArea|
			 Qt::RightDockWidgetArea);
  _Rendu->setCursor(Qt::PointingHandCursor);
  QObject::connect(_Rendu, SIGNAL(clicked()), this, SLOT(launch_raytracer()));
  _Grid->addWidget(_Rendu,250,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
  addDockWidget(Qt::LeftDockWidgetArea, _Dock);
}

Gui::Gui() : QMainWindow()
{
  QColor	Color;

  setFixedSize(1200,800);
  _Scene = new QGraphicsScene();
  Color.setRgb(0,0,0,255);
  QPen	 Pen(Color, 0, Qt::SolidLine);
  QBrush Brush(Color);
  QPolygon Polygon;
  Polygon << QPoint(0,0) << QPoint(1100,0) << QPoint(1100,700) << QPoint(0,700);
  _Item = _Scene->addPolygon(Polygon, Pen, Brush);
  _View = new QGraphicsView(_Scene);
}

void	Gui::rendu(void){}

Gui::~Gui()
{
  delete _Rendu;
  delete _Grid;
  delete _Dock;
  delete _Scene;
  delete _Item;
  delete _View;
}

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
  rt_gui.show();
  return app.exec();
}
