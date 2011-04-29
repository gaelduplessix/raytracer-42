//
// guiDirectLight.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:52:40 2011 franck lavisse
// Last update Fri Apr 29 23:45:42 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "gui.hpp"

void	Gui::directLight(void)
{
  QCheckBox	*light = new QCheckBox("Lumiere directe");
  
  _Grid->addWidget(light,3,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
