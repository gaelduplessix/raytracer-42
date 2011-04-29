//
// guiMenuBar.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:30:28 2011 franck lavisse
// Last update Fri Apr 29 23:46:34 2011 franck lavisse
//
#include <QMenuBar>
#include <QHBoxLayout>
#include "gui.hpp"

void	Gui::menuBar(void)
{
  QMenuBar	*menu = new QMenuBar();
  QMenu		*file = menu->addMenu("&Fichier");
  _widgetBar =	new QWidget();
  _DockBar =	new QDockWidget();
  QHBoxLayout	*box = new QHBoxLayout();

  _DockBar->setAllowedAreas(Qt::TopDockWidgetArea);
  _DockBar->setFeatures(0);  
  box->addWidget(menu);
  _widgetBar->setLayout(box);
  _DockBar->setWidget(_widgetBar);
  addDockWidget(Qt::TopDockWidgetArea, _DockBar);
}
