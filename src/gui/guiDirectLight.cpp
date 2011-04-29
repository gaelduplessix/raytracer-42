//
// guiDirectLight.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:52:40 2011 franck lavisse
// Last update Fri Apr 29 17:54:25 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::directLight(void)
{
  QCheckBox	*light = new QCheckBox("Lumiere directe");
  
  _Grid->addWidget(light,3,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
