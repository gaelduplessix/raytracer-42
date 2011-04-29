//
// accordion.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 16:04:48 2011 franck lavisse
// Last update Fri Apr 29 17:26:27 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::aliasing(void)
{
  QSpinBox	*aliasing = new QSpinBox();
  QLabel	*label = new QLabel("Antialiasing"); 
  QGridLayout	*aliasingGrid = new QGridLayout();
  
  aliasingGrid->addWidget(label,1,0);
  aliasingGrid->addWidget(aliasing,1,1);
  _Grid->addLayout(aliasingGrid,1,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
