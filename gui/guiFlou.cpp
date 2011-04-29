//
// guiFlou.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:05:44 2011 franck lavisse
// Last update Fri Apr 29 18:07:47 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::flou(void)
{
  QSpinBox	*bflou = new QSpinBox();
  QLabel	*label = new QLabel("Flou de profondeur"); 
  QGridLayout	*flouGrid = new QGridLayout();
  
  flouGrid->addWidget(label,1,0);
  flouGrid->addWidget(bflou,1,1);
  _Grid->addLayout(flouGrid,7,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
