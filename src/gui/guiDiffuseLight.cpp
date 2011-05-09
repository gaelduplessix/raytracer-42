//
// guiDiffuseLight.cpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Mon May  9 14:08:52 2011 franck lavisse
// Last update Mon May  9 14:41:38 2011 franck lavisse
//
#include "gui.hpp"

bool	Gui::getDiffuseLightBool(void) const
{
  return (_diffuseLight->checkState());
}

void	Gui::diffuseLight(void)
{
  _diffuseLight = new QCheckBox("Lumiere diffuse");

  _Grid->addWidget(_diffuseLight,13,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
