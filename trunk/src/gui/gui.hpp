//
// gui.hpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Wed Apr 27 13:06:58 2011 franck lavisse
// Last update Tue May 10 14:05:46 2011 franck lavisse
//
#ifndef __GUI_H__
#define __GUI_H__

#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QPainter>
#include <QDockWidget>
#include <QLayout>
#include <QGridLayout>
#include <QMenuBar>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include "../RenderingInterface.hpp"
#include "../Raytracer.hpp"

class Color;

int	gui(int argc, char **argv);

class	Gui : public QMainWindow, public RenderingInterface
{
Q_OBJECT

public:
  Gui();
  ~Gui();

  virtual void	pixelHasBeenRendered(int x, int y, Color color);
  virtual void	renderingHasFinished(void);
  void	putPixel(const Color& color, int x, int y);
  void	init_dock(void);
  void	samplingMethod(void);
  void	aliasing(void);
  void	reflection(void);
  void	directLight(void);
  void	ambiantOcclusion(void);
  void	photonMapping(void);
  void	transparence(void);
  void	flou(void);
  void	menuBar(void);
  void	exposure(void);
  void	specularLight(void);
  void	diffuseLight(void);
  void	diffuseShading(void);
  void	menuEdition(void);

  bool	getTransparenceBool(void) const;
  int	getTransparenceInt(void) const;
  int	getTransparenceDiffusion(void) const;
  bool	getFlouBool(void) const;
  int	getFlouInt(void) const;
  int	getAliasing(void) const;
  bool	getAmbiantOcclusionBool(void) const;
  int	getAmbiantOcclusionInt(void) const;
  bool	getDirectLight(void) const;
  int	getDirectLightInt(void) const;
  bool	getReflectionBool(void) const;
  int	getReflectionProfondeur(void) const;
  bool	getReflectionDiffuseBool(void) const;
  int	getReflectionDiffuseSampling(void) const;
  bool	getPhotonMappingBool(void) const;
  int	getPhotonMappingInt(void) const;
  int	getSamplingMethod(void) const;
  bool	getExposureBool(void) const;
  int	getExposureValue(void) const;  
  bool	getSpecularLightBool(void) const;
  int	getSpecularLightValue(void) const;
  bool	getDiffuseLightBool(void) const;
  bool	getDiffuseShading(void) const;

  Raytracer	_raytracer;

protected:
  virtual void	paintEvent(QPaintEvent*);

public slots:
  void	saveImage(void);
  virtual void	renderingHasStoped(void);
  virtual void	renderingHasPaused(void);
  virtual void	renderingHasBegun(void);
  void	launch_raytracer(void);

private:
  int		isStarted;
  int		isRendering;
  QDockWidget	*_DockBar;
  QWidget	*_widgetBar;
  QWidget	*_widget;
  QGridLayout	*_Grid;
  QDockWidget	*_Dock;
  QGraphicsScene*_Scene;
  QGraphicsItem	*_Item;
  QGraphicsView	*_View;
  QPixmap	*_pixmap;
  QLabel	*_label;
  QLabel	*_pixlabel;
  QImage	*_image;
  QTimer	*_timer;
  QToolBar	*_toolbar;
  QMenuBar	*_menu;

  QCheckBox	*_diffuseLight;
  QCheckBox	*_diffuseShading;
  QCheckBox	*_specularLight;
  QSpinBox	*_specularLightBox;
  QCheckBox	*_transparence;
  QDoubleSpinBox*_transpBox;
  QSpinBox	*_transpDiffusion;
  QCheckBox	*_flou;
  QSpinBox	*_flouBox;
  QSpinBox	*_aliasing;
  QCheckBox	*_ambiantOcclusion;
  QSpinBox	*_ambiantOcclusionBox;
  QCheckBox	*_directLight;
  QSpinBox	*_directLightBox;
  QSpinBox	*_reflectionProfondeur;
  QCheckBox	*_reflectionEnabled;
  QCheckBox	*_reflectionDiffuse;
  QSpinBox	*_reflectionDiffuseSampling;
  QCheckBox	*_photonMapping;
  QSpinBox	*_photonMappingBox;
  QComboBox	*_samplingMethod;
  QCheckBox	*_exposure;
  QSpinBox	*_exposureBox;
};

#endif
