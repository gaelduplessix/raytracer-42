//
// guiLumiereDiffuse.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:03:22 2011 franck lavisse
// Last update Fri Apr 29 18:05:16 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::lumiereDiffuse(void)
{
  QSpinBox	*LD = new QSpinBox();
  QLabel	*label = new QLabel("Lumiere diffuse"); 
  QGridLayout	*LDGrid = new QGridLayout();
  
  LDGrid->addWidget(label,1,0);
  LDGrid->addWidget(LD,1,1);
  _Grid->addLayout(LDGrid,6,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
