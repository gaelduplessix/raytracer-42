//
// guiReflection.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:39:55 2011 franck lavisse
// Last update Mon May  9 14:40:23 2011 franck lavisse
//
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include "gui.hpp"

bool	Gui::getReflectionDiffuseBool(void) const
{
  return (_reflectionDiffuse->checkState());
}

int	Gui::getReflectionDiffuseSampling(void) const
{
  return (_reflectionDiffuseSampling->value());
}

bool	Gui::getReflectionBool(void) const
{
  return (_reflectionEnabled->checkState());
}

int	Gui::getReflectionProfondeur(void) const
{
  return (_reflectionProfondeur->value());
}

void		Gui::reflection(void)
{  
  QLabel	*lprofondeur = new QLabel("Profondeur");
  QGroupBox	*gbox = new QGroupBox("Reflection");
  _reflectionProfondeur = new QSpinBox();
  _reflectionDiffuse = new QCheckBox("Reflection diffuse");
  _reflectionDiffuseSampling = new QSpinBox();
  QGridLayout	*greflection = new QGridLayout();
  _reflectionEnabled = new QCheckBox("Reflection");
  
  _reflectionEnabled->setChecked(true);
  _reflectionProfondeur->setValue(20);
  greflection->addWidget(_reflectionEnabled,0,0);
  greflection->addWidget(lprofondeur,1,0);
  greflection->addWidget(_reflectionProfondeur,1,1);  
  greflection->addWidget(_reflectionDiffuse,3,0);
  greflection->addWidget(_reflectionDiffuseSampling,3,1);
  gbox->setLayout(greflection);
  _Grid->addWidget(gbox,100,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
