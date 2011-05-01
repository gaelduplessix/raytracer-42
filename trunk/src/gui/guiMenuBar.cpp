//
// guiMenuBar.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:30:28 2011 franck lavisse
// Last update Sun May  1 12:12:32 2011 franck lavisse
//
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QString>
#include "gui.hpp"

void	Gui::menuBar(void)
{
  QMenuBar	*menu = new QMenuBar();
  QMenu		*file = menu->addMenu("&Fichier");  
  _widgetBar =	new QWidget();
  _DockBar =	new QDockWidget();
  QHBoxLayout	*box = new QHBoxLayout();
  QAction	*openScene = new QAction("&Charger une scene", this);
  QAction	*quitter = new QAction("&Quitter", this);
  QAction	*saveConfig = new QAction("&Sauvegarder la configuration de la scene", this);
  QAction	*newScene = new QAction("&Nouvelle scene", this);

  QObject::connect(quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
  file->addAction(newScene);
  file->addAction(openScene);
  file->addAction(saveConfig);
  file->addAction(quitter);
  _DockBar->setAllowedAreas(Qt::TopDockWidgetArea);
  //  _DockBar->setFeatures(0);  
  _DockBar->setTitleBarWidget(0);
  box->addWidget(menu);
  _widgetBar->setLayout(box);
  _DockBar->setWidget(_widgetBar);
  addDockWidget(Qt::TopDockWidgetArea, _DockBar);
}
