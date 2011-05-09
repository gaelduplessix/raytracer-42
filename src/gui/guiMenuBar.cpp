//
// guiMenuBar.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:30:28 2011 franck lavisse
// Last update Mon May  9 17:17:16 2011 franck lavisse
//
#include <QMenuBar>
#include <QAction>
#include <QHBoxLayout>
#include <QString>
#include <iostream>
#include <QToolBar>
#include <QKeySequence>
#include "gui.hpp"

using namespace std;

void	Gui::menuBar(void)
{
  QMenuBar	*menu = new QMenuBar();
  QMenu		*file = menu->addMenu("&Fichier");  
  QAction	*openScene = new QAction("&Charger une scene", this);
  QAction	*quitter = new QAction("&Quitter", this);
  QAction	*saveConfig = new QAction("&Sauvegarder la configuration de la scene", this);
  QAction	*newScene = new QAction("&Nouvelle scene", this);

  _toolbar = addToolBar("42");
  QObject::connect(quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
  file->addAction(newScene);
  file->addAction(openScene);
  file->addAction(saveConfig);
  file->addAction(quitter);
  quitter->setShortcut(QKeySequence("Ctrl+Q"));
  quitter->setIcon(QIcon("quitter.png"));
  openScene->setIcon(QIcon("opendossier.png"));
  newScene->setIcon(QIcon("nouveau.png"));
  saveConfig->setIcon(QIcon("save.png"));
  setMenuBar(menu);
  _toolbar->addAction(newScene);
  _toolbar->addAction(openScene);
  _toolbar->addAction(saveConfig);
  _toolbar->addAction(quitter);
}
