//
// guiTransparence.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:21:11 2011 franck lavisse
// Last update Fri Apr 29 19:27:32 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::transparence(void)
{
  QCheckBox	*check = new QCheckBox("Transparence");
  QSpinBox	*transp = new QSpinBox();
  QGridLayout	*transpGrid = new QGridLayout();
  QLabel	*label =  new QLabel("Diffusion transparence");
  QSpinBox	*box = new QSpinBox();
  
  transpGrid->addWidget(check,0,0);
  transpGrid->addWidget(transp,0,1);
  transpGrid->addWidget(label,1,0);
  transpGrid->addWidget(box,1,1);
  _Grid->addLayout(transpGrid,8,0);
  _widget->setLayout(_Grid);  
  _widget->setMaximumHeight(500);
  _Dock->setWidget(_widget);
}
