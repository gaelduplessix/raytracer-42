//
// gui.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May 11 18:59:19 2011 loick michard
// Last update Thu May 12 17:17:22 2011 gael jochaud-du-plessix
//

#ifndef _GUI_HPP_
#define _GUI_HPP_

void	gui(int ac, char **av);

#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QPixmap>
#include "ui_raytracer.h"
#include "RenderingConfiguration.hpp"
#include "Raytracer.hpp"
#include "CubeMap.hpp"

namespace Ui {
  class MainWindow;
}

class RaytracerGUI : public QMainWindow, public RenderingInterface
{
  Q_OBJECT
  
  public:
  RaytracerGUI(QWidget *parent = 0);
  virtual ~RaytracerGUI();
  
  void setConfiguration();
  void    renderingHasFinished(void);
  void    renderingHasBegun(void);
  void pixelHasBeenRendered(int x, int y, Color color);
  void renderingHasProgressed(double progress);

public slots:
  void  pauseRendering(void);
  void  stopRendering(void);
  void	selectCubeMap();
  void	selectBackgroundColor();
  void	selectAmbiantColor();
  void	startRender();
  void	loadScene();
  void	drawWindow();

protected:
  virtual void  paintEvent(QPaintEvent*);

private:
  Ui::MainWindow		*_ui;
  RenderingConfiguration	*_config;
  Raytracer			*_raytracer;
  QColor			*_backgroundColor;
  QColor			*_ambiantColor;
  CubeMap			*_cubeMap;
  Scene				*_scene;
  QImage			*_image;
  QPixmap			*_pixmap;
  bool				_isRendering;
  QTimer			*_timer;
  int				_progress;
};

#endif
