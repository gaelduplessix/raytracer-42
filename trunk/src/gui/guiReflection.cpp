//
// guiReflection.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:39:55 2011 franck lavisse
// Last update Fri Apr 29 23:50:54 2011 franck lavisse
//
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include "gui.hpp"

void		Gui::reflection(void)
{  
  QLabel	*lprofondeur = new QLabel("Profondeur");
  QLabel	*lsampling = new QLabel("Sampling");
  QGroupBox	*gbox = new QGroupBox("Reflection");
  QSpinBox	*profondeur = new QSpinBox();
  QSpinBox	*sampling = new QSpinBox();
  QVBoxLayout	*vbox = new QVBoxLayout();
  QGridLayout	*gprofondeur = new QGridLayout();
  QGridLayout	*gsampling = new QGridLayout();
  
  gprofondeur->addWidget(lprofondeur,1,0);
  gprofondeur->addWidget(profondeur,1,1);  
  gsampling->addWidget(lsampling,1,0);
  gsampling->addWidget(sampling,1,1);
  vbox->addLayout(gprofondeur);  
  vbox->addLayout(gsampling);
  gbox->setLayout(vbox);
  _Grid->addWidget(gbox,100,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);
}
