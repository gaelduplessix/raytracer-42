//
// guiInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu May 12 00:09:02 2011 loick michard
// Last update Thu May 12 19:38:03 2011 loick michard
//

#include <QMessageBox>
#include <QFileDialog>
#include "gui.hpp"

void RaytracerGUI::closeEvent(QCloseEvent *event)
{
  if (!_isRendering)
    event->accept();
  else
    {
      QMessageBox msgBox;
      msgBox.setText("Un rendu est en cours.");
      msgBox.setInformativeText("Etes-vous sur de vouloir fermer la fenetre?");
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = 
	QMessageBox::warning(this, tr("Raytracer"),
			     tr("Un rendu est en cours.\n"
				"Etes-vous sur de vouloir fermer la fenetre?"),
			     QMessageBox::Yes
			     | QMessageBox::Cancel,
			     QMessageBox::Cancel);
      if (ret == QMessageBox::Yes)
	event->accept();
      else
	event->ignore();
    }
}

void RaytracerGUI::sendWarningMessage(string message)
{
  QDateTime time = QDateTime::currentDateTime();
  if (_message != "")
    _message += "<br/>";
  _message += "<span style=\"color:blue;\">";
  _message += time.toString("<b>[dd/mm/yy hh:mm:ss] ").toStdString();
  _message += "Warning : </b>";
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
  _message += "Erreur : </b>";
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
  _message += "Succes : </b>";
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
  _message += "Info : </b>";
  _message += message;
  _message += "</span>";
}

void    RaytracerGUI::pauseRendering(void)
{
  sendMessage("Rendu mis en pause");
  _timer->setSingleShot(true);
  _raytracer->pauseRendering();
  _pause = true;
}

void    RaytracerGUI::renderingHasFinished(void)
{
  sendSuccessMessage(tr("Rendu termine").toStdString());
  _timer->setSingleShot(true);
  _ui->_progressBar->setHidden(true);
  _isRendering = false;
}

void    RaytracerGUI::renderingHasBegun(void)
{
  
}

void    RaytracerGUI::renderingHasProgressed(double progress)
{
  _progress = progress * (_ui->_progressBar->maximum() -
			  _ui->_progressBar->minimum()) +
    _ui->_progressBar->minimum();
}

void    RaytracerGUI::stopRendering(void)
{
  _raytracer->stopRendering();
  _isRendering = false;
  _pause = false;
}

void    RaytracerGUI::loadScene(void)
{
  string scene = 
    QFileDialog::getOpenFileName(this, tr("Charger une scene"), 
				 "", "*.xml;;", 0, 
				 QFileDialog::DontUseNativeDialog).toStdString();
  _scene->loadFromFile(scene);
}

void  RaytracerGUI::pixelHasBeenRendered(int x, int y, Color color)
{
  if (_image)
    _image->setPixel(x, y, QColor(color._r, color._g,
                                  color._b, color._a).rgba());
}

void    RaytracerGUI::startRender()
{
  setConfiguration();
  _timer->setSingleShot(false);
  _timer->start();
  if (!_isRendering)
    {
      if (_image)
	delete _image;
      _image = new QImage(_ui->_width->value(),
                          _ui->_height->value(),
                          QImage::Format_ARGB32);
    }
  try
    {
      _ui->_progressBar->setHidden(false);
      if (pause)
	sendSuccessMessage(tr("Reprise du rendu").toStdString());
      else
	sendSuccessMessage(tr("Depart du rendu").toStdString());
      _pause = false;
      _raytracer->launchRendering();
      _isRendering = true;
    }
  catch(int error)
    {
      std::cout << "ERREUR" << error << std::endl;
    }
}
