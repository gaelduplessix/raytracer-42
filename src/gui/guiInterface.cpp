//
// guiInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Thu May 12 00:09:02 2011 loick michard
// Last update Tue May 31 19:17:08 2011 gael jochaud-du-plessix
// Last update Mon May 30 20:30:33 2011 gael jochaud-du-plessix
//

#include <QMessageBox>
#include <QFileDialog>
#include <QMutexLocker>
#include <QSystemTrayIcon>
#include "gui.hpp"

void	RaytracerGUI::openEditMaterialDialog()
{
  _editMaterialDialog.setMaterials(_scene->getMaterials());
  _editMaterialDialog.show();
}

void 
RaytracerGUI::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  if (reason == QSystemTrayIcon::Trigger)
    show();
}

void RaytracerGUI::closeEvent(QCloseEvent *event)
{
  (void)event;
  hide();
}

void RaytracerGUI::realQuit()
{
  if (!_isRendering)
    qApp->quit();
  else
    {
      int ret =
        QMessageBox::warning(this, tr("Raytracer"),
                             tr("Un rendu est en cours.\n"
                                "Etes-vous sur de vouloir fermer la fenetre?"),
                             QMessageBox::Yes
                             | QMessageBox::Cancel,
                             QMessageBox::Cancel);
      if (ret == QMessageBox::Yes)
	{
          _raytracer->stopRendering();
	  qApp->quit();
        }
    }
}

void RaytracerGUI::sendWarningMessage(string message)
{
  QDateTime time = QDateTime::currentDateTime();
  if (_message != "")
    _message += "<br/>";
  _message += "<span style=\"color:blue;\">";
  _message += time.toString("<b>[dd/mm/yy hh:mm:ss] ").toStdString();
  _message += tr("Attention").toStdString();
  _message += ": </b>";
  _message += message;
  _message += "</span>";
}

void RaytracerGUI::sendErrorMessage(string message)
{
  QDateTime time = QDateTime::currentDateTime();
  if (_message != "")
    _message += "<br/>";
  _message += "<span style=\"color:red;\">";
  _message += time.toString("<b>[dd/mm/yy hh:mm:ss] ").toStdString();
  _message += tr("Error").toStdString();
  _message += ": </b>";
  _message += message;
  _message += "</span>";
}

void RaytracerGUI::sendSuccessMessage(string message)
{
  QDateTime time = QDateTime::currentDateTime();
  if (_message != "")
    _message += "<br/>";
  _message += "<span style=\"color:green;\">";
  _message += time.toString("<b>[dd/mm/yy hh:mm:ss] ").toStdString();
  _message += tr("Success").toStdString();
  _message += ": </b>";
  _message += message;
  _message += "</span>";
}

void RaytracerGUI::sendMessage(string message)
{
  QDateTime time = QDateTime::currentDateTime();
  if (_message != "")
    _message += "<br/>";
  _message += "<span>";
  _message += time.toString("<b>[dd/mm/yy hh:mm:ss] ").toStdString();
  _message += tr("Info").toStdString();
  _message += ": </b>";
  _message += message;
  _message += "</span>";
}

void    RaytracerGUI::pauseRendering(void)
{
  sendMessage(tr("Rendu mis en pause").toStdString());
  _ui->action_Play->setEnabled(true);
  _pause = true;  
  if (!_isConnected)
    _raytracer->pauseRendering();
  else
    _clusterClient->pauseRendering();
}

void    RaytracerGUI::renderingHasFinished(void)
{
  if (_isRendering)
    {
      _endOfRendering = true;
      sendSuccessMessage(tr("Rendu termine").toStdString());
      _isRendering = false;
      _timer->setSingleShot(true);
      _ui->_progress->setHidden(true);
    }
}

void    RaytracerGUI::renderingHasBegun(void)
{

}

void    RaytracerGUI::photonMappingHasBegun(void)
{
  sendMessage(tr("D&eacute;but de la g&eacute;n&eacute;ration de la carte de"
		 " Photon").toStdString());
}

void    RaytracerGUI::photonMappingHasFinished(void)
{
  sendSuccessMessage(tr("G&eacute;n&eacute;ration de la carte de Photon "
			"termin&eacute;e").toStdString());
}

void    RaytracerGUI::kdtreeGenerationHasBegun(void)
{
  sendMessage(tr("D&eacute;but de la g&eacute;n&eacute;ration du Kdtree")
	      .toStdString());
}

void    RaytracerGUI::kdtreeGenerationHasFinished(void)
{
  sendSuccessMessage(tr("G&eacute;n&eacute;ration du KdTree termin&eacute;e")
		     .toStdString());
}

void    RaytracerGUI::renderingHasProgressed(double progress)
{
  _progress = progress * (_ui->_progressBar->maximum() -
			  _ui->_progressBar->minimum()) +
    _ui->_progressBar->minimum();
}

void    RaytracerGUI::stopRendering(void)
{
  if (!_isConnected)
    _raytracer->stopRendering();
  else
    _clusterClient->stopRendering();
  _pause = false;
}

void    RaytracerGUI::loadScene(void)
{
  string scene =
    QFileDialog::getOpenFileName(this, tr("Charger une scene"),
				 "", "*.xml;;", 0,
				 QFileDialog::DontUseNativeDialog).toStdString();
  if (scene != "")
    {
      _raytracer->stopRendering();
      _scene->loadFromFile(scene, this);
      _ui->_console->setHtml(_message.c_str());
      _ui->_console->moveCursor(QTextCursor::End);
      this->setCameras();
    }
}

void  RaytracerGUI::pixelHasBeenRendered(int x, int y, Color color)
{
  QMutexLocker  locker(&_mutex);
  _nbProgress++;
  _nbRender++;
  if (_image)
    {      
      _image->setPixel(x, y, QColor(color._r, color._g,
				    color._b, color._a).rgba());
    }
}

void    RaytracerGUI::startRender()
{
  if (_scene != NULL && _scene->isValid())
    {
      if (!setConfiguration())
	{
	  _ui->_console->setHtml(_message.c_str());
	  _ui->_console->moveCursor(QTextCursor::End);
	  return ;
	}
      ftime(&_progressTime);
      _nbProgress = 0;
      if (!_pause)
	_nbRender = 0;
      _ui->_mode->setEnabled(false);
      _ui->_width->setEnabled(false);
      _ui->_height->setEnabled(false);
      _ui->_threads->setEnabled(false);
      _ui->action_Play->setEnabled(false);
      if (!_timer->isActive())
	{
	  _timer->setSingleShot(false);
	  _timer->setInterval(_preferencesDialogUi->_timer->value());
	  _timer->start();
	}
      if (!_isRendering)
	{
	  if (_image)
	    delete _image;
	  _image = new QImage(_config->getSection().width(),
			      _config->getSection().height(),
			      QImage::Format_ARGB32);
	  _image->fill(0);
	  
	}
      _ui->_progress->setHidden(false);
      if (_pause)
	sendMessage(tr("Reprise du rendu").toStdString());
      else
	sendMessage(tr("D&eacute;part du rendu").toStdString());
      _pause = false;
      _isRendering = true;
      if (!(_isConnected && _clusterClient))
	{
	  try
	    {
	      _raytracer->launchRendering();
	    }
	  catch(int error)
	    {
	      std::cerr << "ERREUR" << error << std::endl;
	    }
	}
      else
	_clusterClient->launchRendering(_config, _scene);
    }
  else
    sendErrorMessage(tr("Vous devez charger une sc&egrave;ne avant de faire un"
			"rendu").toStdString());
}

void		RaytracerGUI::saveImage()
{
  if (_image)
    {
      int   found;
      vector<string> validFormat(4);
      validFormat[0] = "png";
      validFormat[1] = "gif";
      validFormat[2] = "bmp";
      validFormat[3] = "jpeg";
      string format;
      QString file =
	QFileDialog::getSaveFileName(this, tr("Enregistrer une sc&egrave;ne"),
				     QString(),
				     "*.png;;*.gif;;*.jpeg;;*.bmp", 0,
				     QFileDialog::DontUseNativeDialog);
      if (file != "")
	{
	  format = file.toStdString();
	  found = format.find(".");
	  format = format.substr(found + 1);
	  if (format.compare(validFormat[0]) != 0 &&
	      format.compare(validFormat[1]) != 0 &&
	      format.compare(validFormat[2]) != 0 &&
	      format.compare(validFormat[3]) != 0)
	    {
	      format = "png";
	      file += ".png";
	    }
	  _image->save(file);
	}
    }
}

void            RaytracerGUI::saveRender()
{
  if (_config)
    {
      QString file =
        QFileDialog::getSaveFileName(this, tr("Enregistrer un rendu"),
                                     QString(),
                                     "*.rt", 0,
                                     QFileDialog::DontUseNativeDialog);
      if (file != "")
        {
	  string format;
          format = file.toStdString();
          format = format.substr(format.find(".") + 1);
          if (format != "rt")
            {
              file += ".rt";
            }
	  string serial = _config->toStr();
	  ofstream flux;

	  flux.open(file.toStdString().c_str(), ios::out);
	  flux << serial;
	  flux.close();
        }
    }
}

void		RaytracerGUI::updateGUIConfig()
{
  _ui->_mode->setCurrentIndex(_config->getRenderingSamplingMethod());
  _ui->_width->setValue(_config->getWidth());
  _ui->_height->setValue(_config->getHeight());
  _ui->_threads->setValue(_config->getNbThreads());
  _ui->_camera->setCurrentIndex(_config->getCurrentCamera());
  _ui->_antialiasing->setValue(_config->getAntialiasing());
  _ui->_depthFieldSampling->setValue(_config->getFieldDepthSampling());
  _ui->_depthField->setChecked(_config->isFieldDepthEnabled());

  _ui->_3d->setChecked(_config->_3DEnabled);
  _ui->_3DMode->setCurrentIndex(_config->_3DMode);
  _ui->_3DSpace->setValue(_config->_eyesSpace);

  _ui->_kdTreeDepth->setValue(_config->getKdTreeDepth());
  _ui->_kdTree->setChecked(_config->isKdTreeEnabled());
  _ui->_exposure->setValue(_config->getExposure());
  _ui->_directLightingIntensity->setValue(_config->getDirectLightingCoeff());

  _ui->_directLighting->setChecked(_config->isDirectLighting());
  _ui->_diffuseLighting->setChecked(_config->isDiffuseLighting());
  _ui->_specularLighting->setChecked(_config->isSpecularLighting());
  _ui->_diffuseShadingSampling->setValue(_config->getDiffuseShadingSampling());

  _ui->_diffuseShading->setChecked(_config->isDiffuseShadingEnabled());
  _ui->_reflection->setChecked(_config->isReflectionEnabled());
  _ui->_reflectionLimit->setValue(_config->getReflectionMaxDepth());
  _ui->_diffuseReflection->setChecked(_config->isReflectionDiffused());
  _ui->_diffuseReflectionSampling->setValue(_config->getReflectionDiffusedSampling());
  _ui->_transparencyLimit->setValue(_config->getTransparencyMaxDepth());
  _ui->_transparency->setChecked(_config->isTransparencyEnabled());

  _ui->_cubeMap->setChecked((_config->getCubeMap() && _config->_cubeMapPath != ""));
  _ui->_cubeMapRepertory->setText( _config->_cubeMapPath.c_str());

  _backgroundColor->setRed(_config->getBackgroundColor()._r);
  _backgroundColor->setGreen(_config->getBackgroundColor()._g);
  _backgroundColor->setBlue(_config->getBackgroundColor()._b);
  ostringstream oss;

  oss << "background-color: rgb(" << _backgroundColor->red() <<
    "," << _backgroundColor->green() << "," <<
    _backgroundColor->blue() << ");";

  string style = oss.str();
  _ui->_backgroundColor->setStyleSheet(style.c_str());

  _ui->_ambiantLighting->setChecked(_config->isMinimalAmbiantLighting());
  _ui->_ambiantLightingCoeff->setValue(_config->getMinimalAmbiantLighting());

  _ambiantColor->setRed(_config->getAdditiveAmbiantLighting()._r);
  _ambiantColor->setGreen(_config->getAdditiveAmbiantLighting()._g);
  _ambiantColor->setBlue(_config->getAdditiveAmbiantLighting()._b);

  oss << "background-color: rgb(" << _ambiantColor->red() <<
    "," << _ambiantColor->green() << "," <<
    _ambiantColor->blue() << ");";

  style = oss.str();
  _ui->_ambiantColorButton->setStyleSheet(style.c_str());

  _ui->_ambiantColor->setChecked(_config->isAdditiveAmbiantLighting());

  _ui->_ambientOcclusionSampling->setValue(_config->getAmbientOcclusionSampling());
  _ui->_ambientOcclusion->setChecked(_config->isAmbientOcclusionEnabled());

  _ui->_photonMappingValue->setValue(_config->getPhotonMappingSampling());
  _ui->_photonMapping->setChecked(_config->isPhotonMappingEnabled());
}

void            RaytracerGUI::openRender()
{
  string render =
    QFileDialog::getOpenFileName(this, tr("Charger un rendu"),
				 "", "*.rt;;", 0,
				 QFileDialog::DontUseNativeDialog).
    toStdString();
  if (render != "")
    {
      ifstream flux;
      string object;

      flux.open(render.c_str(), ios::in);
      while (getline(flux, object))
	;
      flux.close();
      if (_config)
	delete _config;
      _config = new RenderingConfiguration(object);
      _raytracer->setRenderingConfiguration(_config);
      this->updateGUIConfig();
    }  
}
