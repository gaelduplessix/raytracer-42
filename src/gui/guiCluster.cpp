//
// guiCluster.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon May 23 15:55:20 2011 loick michard
// Last update Thu May 26 19:53:53 2011 loick michard
// Last update Thu May 26 17:45:53 2011 gael jochaud-du-plessix
//

#include <QMessageBox>
#include <QInputDialog>
#include "ClusterServer.hpp"
#include "ClusterClient.hpp"
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
  int returnCode = _launchServerDialog->exec();

  if (returnCode == QDialog::Accepted)
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

void		RaytracerGUI::disconnect()
{
  int ret =
    QMessageBox::warning(this, tr("Raytracer"),
			 tr("Etes-vous sur de vouloir \
vous deconnecter du cluster?"),
			 QMessageBox::Yes
			 | QMessageBox::Cancel,
			 QMessageBox::Cancel);
  if (ret == QMessageBox::Yes)
    {
      _ui->_clusterDock->hide();
      _ui->actionDeconnexion->setVisible(false);
      _ui->actionSe_connecter_un_serveur->setVisible(true);
      _isConnected = false;
    }
}

void		RaytracerGUI::connectToCluster()
{
  int returnCode = _connectToServerDialog->exec();  

  if (returnCode == QDialog::Accepted)
    {
      _ui->_clusterDock->show();
      _ui->actionDeconnexion->setVisible(true);
      _ui->actionSe_connecter_un_serveur->setVisible(false);
      _isConnected = true;
      ClusterClient
      	client(this, _connectToServerDialogUi->_addres->text().toStdString(),
	       _connectToServerDialogUi->_subdivisions->value());
    }
}
