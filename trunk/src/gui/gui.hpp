//
// gui.hpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Wed Apr 27 13:06:58 2011 franck lavisse
// Last update Sun May  1 15:41:38 2011 loick michard
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

  void pixelHasBeenRendered(int x, int y, Color color);
  bool	getTransparenceBool(void) const;
  int	getTransparenceInt(void) const;
  int	getTransparenceDiffusion(void) const;
  bool	getFlouBool(void) const;
  int	getFlouInt(void) const;
  bool	getLumiereDiffuseBool(void) const;
  int	getLumiereDiffuseInt(void) const;
  int	getAliasing(void) const;
  bool	getAmbiantOcclusionBool(void) const;
  int	getAmbiantOcclusionInt(void) const;
  bool	getDirectLight(void) const;
  bool	getReflectionBool(void) const;
  int	getReflectionSampling(void) const;
  int	getReflectionProfondeur(void) const;
  bool	getPhotonMappingBool(void) const;
  int	getPhotonMappingInt(void) const;
  int	getSamplingMethod(void) const;

  void	putPixel(const Color& color, int x, int y);
  void	rendu(void);
  void	init_dock(void);
  void	samplingMethod(void);
  void	aliasing(void);
  void	reflection(void);
  void	directLight(void);
  void	ambiantOcclusion(void);
  void	photonMapping(void);
  void	lumiereDiffuse(void);
  void	transparence(void);
  void	flou(void);
  void	menuBar(void);

  Raytracer	_raytracer;
public slots:
  void	launch_raytracer(void);
  void	putPixelSlot(int, int);

protected:
  void	paintEvent(void);

private:
  QDockWidget	*_DockBar;
  QWidget	*_widgetBar;
  QWidget	*_widget;
  QGridLayout	*_Grid;
  QDockWidget	*_Dock;
  QGraphicsScene*_Scene;
  QGraphicsItem	*_Item;
  QGraphicsView	*_View;

  QLabel	*_label;
  QPixmap	*_pixmap;
  QCheckBox	*_transparence;
  QSpinBox	*_transpBox;
  QSpinBox	*_transpDiffusion;
  QCheckBox	*_flou;
  QSpinBox	*_flouBox;
  QCheckBox	*_lumiereDiffuse;
  QSpinBox	*_lumiereDiffuseBox;
  QSpinBox	*_aliasing;
  QCheckBox	*_ambiantOcclusion;
  QSpinBox	*_ambiantOcclusionBox;
  QCheckBox	*_directLight;
  QSpinBox	*_reflectionProfondeur;
  QSpinBox	*_reflectionSampling;
  QCheckBox	*_reflectionEnabled;
  QCheckBox	*_photonMapping;
  QSpinBox	*_photonMappingBox;
  QComboBox	*_samplingMethod;
  QImage	*_image;
};

#endif
