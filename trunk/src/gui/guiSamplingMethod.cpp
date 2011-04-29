//
// guiSamplingMethod.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 17:07:56 2011 franck lavisse
// Last update Fri Apr 29 23:55:24 2011 franck lavisse
//
#include <QGroupBox>
#include <QStringList>
#include <QVBoxLayout>
#include <QComboBox>
#include "gui.hpp"

void	Gui::samplingMethod(void)
{
  QGroupBox	*gbox = new QGroupBox("Methode de sampling");
  QStringList	*List = new QStringList();
  QVBoxLayout	*vbox = new QVBoxLayout();
  QComboBox	*samplingMethod = new QComboBox();

  *List << "Lineaire horizontal"
	<< "Lineaire vertical"
	<< "Desentrelacement 2D"
	<< "Aleatoire vertical"
	<< "Aleatoire horizontal"
	<< "Aleatoire 2D";
  samplingMethod->addItems(*List);
  vbox->addWidget(samplingMethod,0,0);
  gbox->setLayout(vbox);
  _Grid->addWidget(gbox,0,0);
  _widget->setLayout(_Grid);
  _Dock->setWidget(_widget);  
}
