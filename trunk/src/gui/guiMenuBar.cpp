//
// guiMenuBar.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 19:30:28 2011 franck lavisse
// Last update Mon May  9 17:49:04 2011 franck lavisse
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

void	Gui::menuEdition(void)
{
  QMenu		*edition = _menu->addMenu("&Edition");
  QAction	*stop = new QAction("&Stop", this);
  QAction	*play = new QAction("&Continuer", this);
  QAction	*pause = new QAction("&Pause", this);

  QObject::connect(stop, SIGNAL(triggered()), this, SLOT(renderingHasStoped()));
  QObject::connect(play, SIGNAL(triggered()), this, SLOT(renderingHasBegun()));
  QObject::connect(pause, SIGNAL(triggered()), this, SLOT(renderingHasPaused()));
  edition->addAction(stop);
  edition->addAction(play);
  edition->addAction(pause);
  stop->setIcon(QIcon("stop.png"));
  play->setIcon(QIcon("play.png"));
  pause->setIcon(QIcon("pause.png"));
  _toolbar->addSeparator();
  _toolbar->addAction(play);
  _toolbar->addAction(pause);
  _toolbar->addAction(stop);
}

void	Gui::menuBar(void)
{
  _menu = new QMenuBar();
  QMenu		*file = _menu->addMenu("&Fichier");  
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
  setMenuBar(_menu);
  _toolbar->addAction(newScene);
  _toolbar->addAction(openScene);
  _toolbar->addAction(saveConfig);
  _toolbar->addAction(quitter);
  menuEdition();
}
