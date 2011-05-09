//
// guiDiffuseShading.cpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Mon May  9 14:23:02 2011 franck lavisse
// Last update Mon May  9 14:26:55 2011 franck lavisse
//
#include "gui.hpp"

bool	Gui::getDiffuseShading(void) const
{
  return (_diffuseShading->checkState());
}

void	Gui::diffuseShading(void)
{
  _diffuseShading = new QCheckBox("Ombres diffuses");

  _Grid->addWidget(_diffuseShading,14,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
