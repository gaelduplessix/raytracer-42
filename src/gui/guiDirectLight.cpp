//
// guiDirectLight.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:52:40 2011 franck lavisse
// Last update Sat Apr 30 18:15:35 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "gui.hpp"

bool	Gui::getDirectLight(void) const
{
  return (_directLight->checkState());
}

void	Gui::directLight(void)
{
  _directLight = new QCheckBox("Lumiere directe");
  
  _Grid->addWidget(_directLight,3,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
