//
// guiFlou.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 18:05:44 2011 franck lavisse
// Last update Sat Apr 30 18:04:07 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "gui.hpp"

bool	Gui::getFlouBool(void) const
{
  return (_flou->checkState());
}

int	Gui::getFlouInt(void) const
{
  return (_flouBox->value());
}

void	Gui::flou(void)
{
  _flou = new QCheckBox("Flou de profondeur");
  _flouBox = new QSpinBox();
  QGridLayout	*flouGrid = new QGridLayout();

  flouGrid->addWidget(_flou,1,0);
  flouGrid->addWidget(_flouBox,1,1);  
  _Grid->addLayout(flouGrid,7,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
