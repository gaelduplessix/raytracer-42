//
// guiAmbiantOcclusion.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:56:20 2011 franck lavisse
// Last update Sat Apr 30 18:13:36 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "gui.hpp"

bool	Gui::getAmbiantOcclusionBool(void) const
{
  return (_ambiantOcclusion->checkState());
}

int	Gui::getAmbiantOcclusionInt(void) const
{
  return (_ambiantOcclusionBox->value());
}

void	Gui::ambiantOcclusion(void)
{
  _ambiantOcclusion = new QCheckBox("Occlusion ambiante");
  _ambiantOcclusionBox = new QSpinBox();
  QGridLayout	*AOGrid = new QGridLayout();
  
  AOGrid->addWidget(_ambiantOcclusion,1,0);
  AOGrid->addWidget(_ambiantOcclusionBox,1,1);
  _Grid->addLayout(AOGrid,4,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
