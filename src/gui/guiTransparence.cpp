//
// guiTransparence.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:21:11 2011 franck lavisse
// Last update Sun May  1 11:35:01 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include "gui.hpp"

bool	Gui::getTransparenceBool(void) const
{
  return (_transparence->checkState());
}

int	Gui::getTransparenceInt(void) const
{
  return (_transpBox->value());
}

int	Gui::getTransparenceDiffusion(void) const
{
  return (_transpDiffusion->value());
}

void	Gui::transparence(void)
{
  _transparence = new QCheckBox("Transparence");
  _transpBox = new QSpinBox();
  QGridLayout	*transpGrid = new QGridLayout();
  QLabel	*label =  new QLabel("Diffusion transparence");
  _transpDiffusion = new QSpinBox();

  transpGrid->addWidget(_transparence,0,0);
  transpGrid->addWidget(_transpBox,0,1);
  transpGrid->addWidget(label,1,0);
  transpGrid->addWidget(_transpDiffusion,1,1);
  _Grid->addLayout(transpGrid,8,0);
  _widget->setLayout(_Grid);  
  _Dock->setWidget(_widget);
}
