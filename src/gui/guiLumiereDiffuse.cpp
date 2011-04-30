//
// guiLumiereDiffuse.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:03:22 2011 franck lavisse
// Last update Sat Apr 30 18:06:11 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include "gui.hpp"

bool	Gui::getLumiereDiffuseBool(void) const
{
  return (_lumiereDiffuse->checkState());
}

int	Gui::getLumiereDiffuseInt(void) const
{
  return (_lumiereDiffuseBox->value());
}

void	Gui::lumiereDiffuse(void)
{
  _lumiereDiffuse = new QCheckBox("Lumiere diffuse");
  _lumiereDiffuseBox = new QSpinBox();
  QGridLayout	*LDGrid = new QGridLayout();
  
  LDGrid->addWidget(_lumiereDiffuse,1,0);
  LDGrid->addWidget(_lumiereDiffuseBox,1,1);
  _Grid->addLayout(LDGrid,6,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
