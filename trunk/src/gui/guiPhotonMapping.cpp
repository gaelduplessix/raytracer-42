//
// guiPhotonMapping.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:00:00 2011 franck lavisse
// Last update Sat Apr 30 18:22:44 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QSpinBox>
#include "gui.hpp"

bool	Gui::getPhotonMappingBool(void) const
{
  return (_photonMapping->checkState());
}

int	Gui::getPhotonMappingInt(void) const
{
  return (_photonMappingBox->value());
}

void	Gui::photonMapping(void)
{
  _photonMapping = new QCheckBox("Photon mapping");
  _photonMappingBox = new QSpinBox();
  QGridLayout	*PMGrid = new QGridLayout();

  PMGrid->addWidget(_photonMapping,1,0);
  PMGrid->addWidget(_photonMappingBox,1,1);
  _Grid->addLayout(PMGrid,5,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
