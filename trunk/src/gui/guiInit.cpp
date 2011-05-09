//
// guiInit.cpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Mon May  9 13:53:53 2011 franck lavisse
// Last update Mon May  9 17:54:30 2011 franck lavisse
//
#include <QPushButton>
#include <QTimer>
#include "gui.hpp"

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
  _widget->setMaximumHeight(650);
}

void	Gui::paintEvent(QPaintEvent*)
{
  *_pixmap = _pixmap->fromImage(*_image);
  _pixlabel->setPixmap(*_pixmap);
}

Gui::Gui() : QMainWindow()
{
  Color	pixelColor;

  _timer = new QTimer();
  isRendering = 0;
  resize(1400, 800);
  _image = new QImage(1130, 720, QImage::Format_ARGB32);
  _pixlabel = new QLabel();
  setCentralWidget(_pixlabel);
  _pixmap = new QPixmap(1130, 720);
  pixelColor.setR(0);
  pixelColor.setG(255);
  pixelColor.setB(0);
  _timer->setInterval(10000000);
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(repaint()));
  _pixmap->fill(Qt::black);
  init_dock();
  samplingMethod();
  aliasing();
  reflection();
  directLight();
  ambiantOcclusion();
  photonMapping();
  flou();
  transparence();
  exposure();
  specularLight();
  diffuseLight();
  diffuseShading();
  menuBar();
  show();
}
