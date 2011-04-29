//
// guiFlou.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:05:44 2011 franck lavisse
// Last update Fri Apr 29 19:17:32 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::flou(void)
{
  QCheckBox	*check = new QCheckBox("Flou de profondeur");
  QSpinBox	*bflou = new QSpinBox();
  QGridLayout	*flouGrid = new QGridLayout();

  flouGrid->addWidget(check,1,0);
  flouGrid->addWidget(bflou,1,1);  
  _Grid->addLayout(flouGrid,7,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
