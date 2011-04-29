/*
** gui.c for  in /home/laviss_f//raytracer-42
** 
** Made by franck lavisse
** Login   <laviss_f@epitech.net>
** 
** Started on  Tue Apr 26 15:13:06 2011 franck lavisse
// Last update Fri Apr 29 14:55:25 2011 franck lavisse
*/
#include <iostream>
#include "gui.hpp"

using namespace std;

void	Gui::putPixel(unsigned char color[3], int x, int y)
{
  QPolygon	Pixel;
  QGraphicsItem	*Item;
  QColor	Color;

  Color.setRgb((int)color[0], (int)color[1], (int)color[2], 255);
  QPen		PixelPen(Color, 0, Qt::SolidLine);
  QBrush	PixelBrush(Color);
  Item = _Scene->addRect(x,y,1,1,PixelPen,PixelBrush);
}

void	Gui::onglet(void)
{
  _Tab = new QTabWidget();
  _Tab->setGeometry(30,20,240,160);

  QWidget	*aliasing = new QWidget();
  QWidget	*ambiantocclusion = new QWidget();

  QGridLayout	*Layout1 = new QGridLayout();
  QGroupBox	*Group1 = new QGroupBox();
  QCheckBox	*bouton1 = new QCheckBox("x4");
  QCheckBox	*bouton2 = new QCheckBox("x8");
  // bouton1->setCheckable(true);
  //  bouton2->setCheckable(true);
  //  Group1->addItem(bouton1);
  //  Group1->addItem(bouton2);
  Layout1->addWidget(bouton1);
  Layout1->addWidget(bouton2);
  Group1->setLayout(Layout1);
  //  Layout1->addWidget(bouton1,0,0);
  //  Layout1->addWidget(bouton2,0,1);
  aliasing->setLayout(Layout1);

  QGridLayout	*Layout2 = new QGridLayout();
  QGroupBox	*Group2 = new QGroupBox();
  QCheckBox	*bouton21 = new QCheckBox("On");
  QCheckBox	*bouton22 = new QCheckBox("Off");
  //  bouton21->setCheckable(true);
  //  bouton22->setCheckable(true);
  //  Group2->addItem(bouton21);
  //  Group2->addItem(bouton22);
  Layout2->addWidget(bouton21);
  Layout2->addWidget(bouton22);
  Group2->setLayout(Layout2);
  //  Layout2->addWidget(bouton21,0,0);
  //  Layout2->addWidget(bouton22,0,1);
  ambiantocclusion->setLayout(Layout2);

  _Tab->addTab(aliasing, "Aliasing");
  _Tab->addTab(ambiantocclusion, "Ambiant Occlusion");
  _Grid->addWidget(_Tab,1,0);
  widget->setLayout(_Grid);
  _Dock->setWidget(widget);
  addDockWidget(Qt::LeftDockWidgetArea, _Dock);
}

void	raytracer(Gui *rt) {rt = rt;}

void	Gui::launch_raytracer(void)
{
  cout << "test" << endl;
  raytracer(this);
}

void	Gui::layout(void)
{
  _Grid = new QGridLayout();
  _Dock = new QDockWidget();
  widget = new QWidget();
  _Rendu = new QPushButton("Rendu", _Dock); 
  setCentralWidget(_View);
  _Dock->setAllowedAreas(Qt::LeftDockWidgetArea|
			 Qt::RightDockWidgetArea|
			 Qt::TopDockWidgetArea|
			 Qt::BottomDockWidgetArea);
  _Rendu->setCursor(Qt::PointingHandCursor);
  /*  _Box = new QComboBox();
  _Box->addItem("Aliasing");
  _Box->addItem("AmbiantOcclusion");
  _Box->addItem("DirectLight");*/
  QObject::connect(_Rendu, SIGNAL(clicked()), this, SLOT(launch_raytracer()));
  //  _Grid->addWidget(_Box,0,0);
  _Grid->addWidget(_Rendu,2,0);
  //  widget->setLayout(_Grid);
  //  _Dock->setWidget(widget);
  //  addDockWidget(Qt::LeftDockWidgetArea, _Dock);
}

Gui::Gui() : QMainWindow()
{
  setFixedSize(1200,800);
  _Scene = new QGraphicsScene();
  QColor	Color;
  Color.setRgb(0,0,0,255);
  _Polygon = new QPolygon;
  *_Polygon << QPoint(0,0) << QPoint(1100,0) << QPoint(1100,700) << QPoint(0,700);
  _Pen = new QPen(Color, 1, Qt::SolidLine);
  _Brush = new QBrush(Color);
  _Item = _Scene->addPolygon(*_Polygon, *_Pen, *_Brush);
  _View = new QGraphicsView(_Scene);
}

void	Gui::rendu(void){}

Gui::~Gui()
{
  delete widget;
  delete _Tab;
  delete _Box;
  delete _Grid;
  delete _Dock;
  delete _Pen;
  delete _Brush;
  delete _Rendu;
  delete _Scene;
  delete _Item;
  delete _View;
  delete _Polygon;
}

int	gui(int argc, char **argv)
{
  QApplication	app(argc, argv);
  Gui		rt_gui;

  rt_gui.layout();
  rt_gui.onglet();
  rt_gui.show();
  return app.exec();
}
