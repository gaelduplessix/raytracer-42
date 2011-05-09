//
// guiExposure.cpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Mon May  9 13:45:31 2011 franck lavisse
// Last update Mon May  9 14:31:34 2011 franck lavisse
//
#include "gui.hpp"

bool	Gui::getExposureBool(void) const
{
  return (_exposure->checkState());
}

int	Gui::getExposureValue(void) const
{
  return (_exposureBox->value());
}

void	Gui::exposure(void)
{
  _exposure = new QCheckBox("Exposition");
  _exposureBox = new QSpinBox();
  QGridLayout	*EGrid = new QGridLayout();

  EGrid->addWidget(_exposure,1,0);
  EGrid->addWidget(_exposureBox,1,1);
  _Grid->addLayout(EGrid,9,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
