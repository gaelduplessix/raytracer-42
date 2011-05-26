//
// guiCluster.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon May 23 15:55:20 2011 loick michard
// Last update Thu May 26 16:47:43 2011 loick michard
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
  _connectToServerDialog = new QDialog();
  _connectToServerDialogUi = new Ui::ConnectToServer();
  _connectToServerDialogUi->setupUi(_connectToServerDialog);
}

void		RaytracerGUI::updateServerConsole()
{
  _clusterDialogUi->_clusterConsole->setHtml(_consoleLog.c_str());
  _clusterDialogUi->_clusterConsole->moveCursor(QTextCursor::End);
}

void		RaytracerGUI::launchServer()
{
  _consoleLog = "";
  _clusterDialogUi->_clusterConsole->setText("");
  int ok = _launchServerDialog->exec();

  if (ok)
    {
      this->setEnabled(false);
      ClusterServer
	server(this, _launchServerDialogUi->_adress->text().toStdString(),
	       _launchServerDialogUi->_port->value());
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

void		RaytracerGUI::connectToCluster()
{
  int ok = _connectToServerDialog->exec();  

  if (ok)
    {
      
    }
}
