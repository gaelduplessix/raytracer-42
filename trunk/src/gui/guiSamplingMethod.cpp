//
// guiSamplingMethod.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:07:56 2011 franck lavisse
// Last update Sat Apr 30 18:31:58 2011 franck lavisse
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
  QGroupBox	*gbox = new QGroupBox("Methode de sampling");
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
  vbox->addWidget(_samplingMethod,0,0);
  gbox->setLayout(vbox);
  _Grid->addWidget(gbox,0,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);  
}
