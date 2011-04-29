//
// guiPhotonMapping.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:00:00 2011 franck lavisse
// Last update Fri Apr 29 18:01:54 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::photonMapping(void)
{
  QSpinBox	*PM = new QSpinBox();
  QLabel	*label = new QLabel("Photon mapping"); 
  QGridLayout	*PMGrid = new QGridLayout();
  
  PMGrid->addWidget(label,1,0);
  PMGrid->addWidget(PM,1,1);
  _Grid->addLayout(PMGrid,5,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
