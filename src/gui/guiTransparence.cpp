//
// guiTransparence.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:21:11 2011 franck lavisse
// Last update Mon May  9 15:55:06 2011 franck lavisse
//
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>
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
  QLabel	*diffusion = new QLabel("Diffusion transparence");
  QGroupBox	*gbox = new QGroupBox("Transparence");
  _transparence = new QCheckBox("Transparence");
  _transpBox = new QDoubleSpinBox();
  QGridLayout	*transpGrid = new QGridLayout();
  QLabel	*label =  new QLabel("Diffusion transparence");
  _transpDiffusion = new QSpinBox();

  _transparence->setChecked(true);
  _transpBox->setValue(1);
  _transpBox->setRange(0,1);
  _transpDiffusion->setValue(20);
  transpGrid->addWidget(_transparence,0,0);
  transpGrid->addWidget(_transpBox,0,1);
  transpGrid->addWidget(label,1,0);
  transpGrid->addWidget(_transpDiffusion,1,1);
  gbox->setLayout(transpGrid);
  _Grid->addWidget(gbox,8,0);
  _widget->setLayout(_Grid);  
  _Dock->setWidget(_widget);
}
