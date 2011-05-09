//
// guiSamplingMethod.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:07:56 2011 franck lavisse
// Last update Mon May  9 15:54:55 2011 franck lavisse
//
#include <QGroupBox>
#include <QStringList>
#include <QVBoxLayout>
#include <QComboBox>
#include "gui.hpp"

int	Gui::getSamplingMethod(void) const
{
  return (_samplingMethod->currentIndex());
}

void	Gui::samplingMethod(void)
{
  QLabel	*name = new QLabel("Methode de sampling");
  QStringList	*List = new QStringList();
  QVBoxLayout	*vbox = new QVBoxLayout();
  _samplingMethod = new QComboBox();

  *List << "Lineaire horizontal"
	<< "Lineaire vertical"
	<< "Desentrelacement 2D"
	<< "Aleatoire vertical"
	<< "Aleatoire horizontal"
	<< "Aleatoire 2D";
  _samplingMethod->addItems(*List);
  vbox->addWidget(name,0,0);
  vbox->addWidget(_samplingMethod,1,0);
  _Grid->addLayout(vbox,0,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);  
}
