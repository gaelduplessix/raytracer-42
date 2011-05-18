//
// gui.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May 11 18:59:19 2011 loick michard
// Last update Wed May 18 13:26:14 2011 samuel olivier
//

#ifndef _GUI_HPP_
#define _GUI_HPP_

void	gui(int ac, char **av);

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QPixmap>
#include <string>
#include <QCloseEvent>
#include "ui_raytracer.h"
#include "RenderingConfiguration.hpp"
#include "Raytracer.hpp"
#include "CubeMap.hpp"

using namespace std;

namespace Ui {
  class MainWindow;
}

class RaytracerGUI : public QMainWindow, public RenderingInterface
{
  Q_OBJECT
  
  public:
  RaytracerGUI(QWidget *parent = 0);
  virtual ~RaytracerGUI();
  
  void	setConfiguration();
  void	renderingHasFinished(void);
  void	renderingHasBegun(void);
  void	pixelHasBeenRendered(int x, int y, Color color);
  void	renderingHasProgressed(double progress);

  void	sendWarningMessage(string message);
  void	sendErrorMessage(string message);
  void	sendSuccessMessage(string message);
  void	sendMessage(string message);
  void	closeEvent(QCloseEvent *event);
  void	photonMappingHasBegun(void);
  void	photonMappingHasFinished(void);

public slots:
  void  pauseRendering(void);
  void  stopRendering(void);
  void	selectCubeMap();
  void	selectBackgroundColor();
  void	selectAmbiantColor();
  void	startRender();
  void	loadScene();
  void	drawWindow();
  void	saveImage();

protected:
  virtual void  paintEvent(QPaintEvent*);
  void		setCameras();

private:
  RenderingConfiguration	*_config;
  Raytracer			*_raytracer;
  QColor			*_backgroundColor;
  QColor			*_ambiantColor;
  QImage			*_image;
  CubeMap			*_cubeMap;
  Scene				*_scene;
  QTimer			*_timer;
  QPixmap			*_pixmap;
  Ui::MainWindow		*_ui;
  int				_progress;
  string			_message;
  bool				_isRendering;
  bool				_pause;
};

#endif
