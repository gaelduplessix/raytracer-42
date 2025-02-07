//
// guiCluster.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon May 23 15:55:20 2011 loick michard
// Last update Mon Jun  6 23:10:36 2011 gael jochaud-du-plessix
//

#include <QMessageBox>
#include <QInputDialog>
#include "ClusterServer.hpp"
#include "ClusterClient.hpp"
#include "gui.hpp"

void		RaytracerGUI::logServerConsoleMessage(string message)
{
  if (_serverMode)
    {
      cout << QString(message.c_str())
	.remove(QRegExp("<([^<>]+)>")).toStdString()
	   << endl;
      return ;
    }
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
  _connectToServerDialogUi->buttonBox->button(QDialogButtonBox::Ok)
    ->setFocus(Qt::OtherFocusReason);
  if (_clusterTimer)
    delete _clusterTimer;
  _clusterTimer = new QTimer();
  _clusterTimer->setInterval(100);
  QObject::connect(_clusterTimer, SIGNAL(timeout()), 
		   this, SLOT(updateServersTab()));

  _ui->_serversTab->horizontalHeader()
    ->setResizeMode(QHeaderView::ResizeToContents);
  _ui->_serversTab->
    horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
}

void		RaytracerGUI::updateServersTab()
{
  vector<ServerEntry*> list = _clusterClient->getServers();

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
      else if (list[i]->getStatus() == ServerEntry::WAITING_REQUEST)
	state = tr("En attente");
      else if (list[i]->getStatus() == ServerEntry::PROCESSING_REQUEST)
	state = tr("Traitement requ�te");
      else if (list[i]->getStatus() == ServerEntry::DOWNLOADING_RESOURCES)
	state = tr("T�l�chargement ressources");
      else if (list[i]->getStatus() == ServerEntry::PROCESSING_RESOURCES)
        state = tr("Traitement ressources");
      else if (list[i]->getStatus() == ServerEntry::RAYTRACING)
	state = tr("Raytracing");
      else if (list[i]->getStatus() == ServerEntry::SENDING_RESPONSE)
	state = tr("Envoi r�ponse");
      _ui->_serversTab->setItem(i, 2, new QTableWidgetItem(state));

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
	       _launchServerDialogUi->_port->value(), 
	       _preferencesDialogUi->_serverLogTime->value(),
	       _preferencesDialogUi->_threads->value());
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
			 tr("Etes-vous sur de vouloir "
			    "vous deconnecter du cluster?"),
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
      if (_isRendering && _image && _raytracer && _raytracer->_thread)
	{
	  int			nbSubdivisions =
	    _connectToServerDialogUi->_subdivisions->value();
	  if ((nbSubdivisions < 1)
	       || nbSubdivisions > _image->width())
	    nbSubdivisions = sqrt(_image->width());
	  QByteArray            clusterState;
	  QDataStream           stream(&clusterState, QIODevice::ReadWrite);
	  QString		urlStr(_connectToServerDialogUi
				       ->_addres->text());
	  QUrl			url(urlStr);

	  stream << url;
	  stream << (int)nbSubdivisions;
	  for (int i = 0; i < nbSubdivisions; i++)
	    {
	      for (int j = 0; j < nbSubdivisions; j++)
		{
		  ClusterClient::ImageSection status =
		    ClusterClient::RAYTRACED;
		  for (int k = 0, l = (double)_image->width() / nbSubdivisions;
			 k < l; k++)
		    {
		      for (int m = 0, n = (double)_image->height()
			     / nbSubdivisions; m < n; m++)
			{
			  if(!_raytracer->_thread
			     ->isRaytracedPixel(_image->width()
						/ nbSubdivisions * i + k,
						_image->height()
						/ nbSubdivisions * j + m))
			    status = ClusterClient::NOT_RAYTRACED;
			}
		    }
		  stream << (int)status;
		}
	    }
	  _clusterClient =
	    new ClusterClient(this, clusterState,
			      _preferencesDialogUi->_clientLogTime->value(),
			      &urlStr);
	}
      else
	{
	  _clusterClient =
	    new ClusterClient(this, _connectToServerDialogUi
			      ->_addres->text().toStdString(),
			      _connectToServerDialogUi->_subdivisions->value(),
			      _preferencesDialogUi->_clientLogTime->value());
	}
	  _clusterTimer->start();
    }
}
