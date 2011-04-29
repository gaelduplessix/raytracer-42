//
// guiAmbiantOcclusion.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:56:20 2011 franck lavisse
// Last update Fri Apr 29 19:18:32 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::ambiantOcclusion(void)
{
  QCheckBox	*Ambiant = new QCheckBox("Occlusion ambiante");
  QSpinBox	*AO = new QSpinBox();
  QGridLayout	*AOGrid = new QGridLayout();
  
  AOGrid->addWidget(Ambiant,1,0);
  AOGrid->addWidget(AO,1,1);
  _Grid->addLayout(AOGrid,4,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
