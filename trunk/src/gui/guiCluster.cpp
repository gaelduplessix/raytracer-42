//
// guiCluster.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon May 23 15:55:20 2011 loick michard
// Last update Mon May 23 18:26:23 2011 loick michard
//

#include <QInputDialog>
#include "ClusterServer.hpp"
#include "gui.hpp"

void		RaytracerGUI::logServerConsoleMessage(string message)
{
  if (_consoleLog != "")
    _consoleLog += "<br/>";
  _consoleLog += message;
}

void		RaytracerGUI::_initDialogCluster()
{
  _clusterDialog = new QDialog();
  _clusterDialogUi = new Ui::ClusterDialog();
  _clusterDialogUi->setupUi(_clusterDialog);
  _launchServerDialog = new QDialog();
  _launchServerDialogUi = new Ui::LaunchServerDialog();
  _launchServerDialogUi->setupUi(_launchServerDialog);
}

void		RaytracerGUI::updateServerConsole()
{
  _clusterDialogUi->_clusterConsole->setText(_consoleLog.c_str());
}

void		RaytracerGUI::launchServer()
{
  int ok = _launchServerDialog->exec();

  if (ok)
    {
      this->setEnabled(false);
      ClusterServer
	server(_launchServerDialogUi->_adress->text().toStdString());
      QTimer *timer = new QTimer();
      timer->start(200);
      QObject::connect(timer, SIGNAL(timeout()),
		       this, SLOT(updateServerConsole()));
      _clusterDialog->exec();
      timer->stop();
      delete timer;
      this->setEnabled(true);
    }
}
