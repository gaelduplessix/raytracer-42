//
// guiDirectLight.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:52:40 2011 franck lavisse
// Last update Tue May 10 13:34:50 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "gui.hpp"

bool	Gui::getDirectLight(void) const
{
  return (_directLight->checkState());
}

int	Gui::getDirectLightInt(void) const
{
  return (_directLightBox->value());
}

void	Gui::directLight(void)
{
  _directLight = new QCheckBox("Lumiere directe");
  _directLightBox = new QSpinBox();
  QGridLayout	*DLGrid = new QGridLayout();

  DLGrid->addWidget(_directLight,0,0);
  DLGrid->addWidget(_directLightBox,0,1);
  _directLight->setChecked(true);
  _directLightBox->setValue(10);
  _Grid->addLayout(DLGrid,3,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
