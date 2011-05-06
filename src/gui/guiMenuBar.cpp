//
// guiMenuBar.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:30:28 2011 franck lavisse
// Last update Thu May  5 15:01:01 2011 franck lavisse
//
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QString>
#include <iostream>
#include "gui.hpp"

using namespace std;

void	Gui::menuBar(void)
{
  QMenuBar	*menu = new QMenuBar();
  QMenu		*file = menu->addMenu("&Fichier");  
  QAction	*openScene = new QAction("&Charger une scene", this);
  QAction	*quitter = new QAction("&Quitter", this);
  QAction	*saveConfig = new QAction("&Sauvegarder la configuration de la scene", this);
  QAction	*newScene = new QAction("&Nouvelle scene", this);

  QObject::connect(quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
  file->addAction(newScene);
  file->addAction(openScene);
  file->addAction(saveConfig);
  file->addAction(quitter);
  setMenuBar(menu);
  //_DockBar->setAllowedAreas(Qt::TopDockWidgetArea);
  //  _DockBar->setFeatures(0);  
  //_DockBar->setTitleBarWidget(0);
  //box->addWidget(menu);
  //_widgetBar->setLayout(box);
  //_DockBar->setWidget(_widgetBar);
  //addDockWidget(Qt::TopDockWidgetArea, _DockBar);
}
