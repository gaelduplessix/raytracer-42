//
// guiInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu May 12 00:09:02 2011 loick michard
// Last update Thu May 12 16:34:57 2011 loick michard
//

#include <QFileDialog>
#include "gui.hpp"

void    RaytracerGUI::pauseRendering(void)
{
  _raytracer->pauseRendering();
}

void    RaytracerGUI::renderingHasFinished(void)
{
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
                                  color._b, color._a).rgb());
}

void    RaytracerGUI::startRender()
{
  setConfiguration();
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
      _raytracer->launchRendering();
      _isRendering = true;
    }
  catch(int error)
    {
      std::cout << "ERREUR" << error << std::endl;
    }
}
