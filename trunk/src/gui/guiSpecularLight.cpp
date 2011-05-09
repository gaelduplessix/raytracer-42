//
// guiSpecularLight.cpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Mon May  9 14:00:04 2011 franck lavisse
// Last update Mon May  9 14:07:02 2011 franck lavisse
//
#include "gui.hpp"

bool	Gui::getSpecularLightBool(void) const
{
  return (_specularLight->checkState());
}

int	Gui::getSpecularLightValue(void) const
{
  return (_specularLightBox->value());
}

void	Gui::specularLight(void)
{
  _specularLight = new QCheckBox("Lumiere speculaire");
  _specularLightBox = new QSpinBox();
  QGridLayout	*SGrid = new QGridLayout();

  SGrid->addWidget(_specularLight,1,0);
  SGrid->addWidget(_specularLightBox,1,1);
  _Grid->addLayout(SGrid,11,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
