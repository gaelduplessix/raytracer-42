//
// guiCluster.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon May 23 15:55:20 2011 loick michard
// Last update Sun May 29 15:10:37 2011 loick michard
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
  if (_clusterTimer)
    delete _clusterTimer;
  _clusterTimer = new QTimer();
  _clusterTimer->setInterval(200);
  QObject::connect(_clusterTimer, SIGNAL(timeout()), 
		   this, SLOT(updateServersTab()));
}

void		RaytracerGUI::updateServersTab()
{
  vector<ServerEntry*> list = _clusterClient->_servers;
  list.push_back(new ServerEntry("127.0.0.1", 80));
  _ui->_serversTab->setRowCount(list.size());
  for (unsigned int i = 0; i < list.size(); i++)
    {
      if (_ui->_serversTab->item(i, 0))
	delete _ui->_serversTab->item(i, 0);
      _ui->_serversTab
	->setItem(i, 0,
		  new QTableWidgetItem(list[i]->getIp()));
      
      if (_ui->_serversTab->item(i, 1))
        delete _ui->_serversTab->item(i, 1);
      _ui->_serversTab
        ->setItem(i, 1,
                  new QTableWidgetItem(QString::number(list[i]->getPort())));
      

      if (_ui->_serversTab->item(i, 2))
        delete _ui->_serversTab->item(i, 2);
      QString state;
      if (list[i]->getStatus() == ServerEntry::FREE)
	state = tr("Libre");
      else if (list[i]->getStatus() == ServerEntry::DOWNLOADING_RESSOURCES)
	state = tr("Telechargement ressources");
      else if (list[i]->getStatus() == ServerEntry::PROCESSING_RESSOURCES)
        state = tr("Traitement ressources");
      else if (list[i]->getStatus() == ServerEntry::RAYTRACING)
	state =tr("Raytracing");
      else if (list[i]->getStatus() == ServerEntry::SENDING_RESPONSE)
	state =tr("Envoi reponse");
      _ui->_serversTab
	->setItem(i, 2,
		  new QTableWidgetItem(state));

      if (_ui->_serversTab->cellWidget(i, 3))
        delete _ui->_serversTab->cellWidget(i, 3);
      QProgressBar *bar = new QProgressBar();
      bar->setRange(0, 100);
      bar->setValue(list[i]->getProgress());
      _ui->_serversTab
        ->setCellWidget(i, 3, bar);
    }
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
      delete _clusterClient;
      _isConnected = false;
      _clusterTimer->stop();
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
      if (!_timer->isActive())
	_timer->start();
      _clusterClient =
	new ClusterClient(this, _connectToServerDialogUi
			  ->_addres->text().toStdString(),
			  _connectToServerDialogUi->_subdivisions->value());
      _clusterTimer->start();
    }
}
