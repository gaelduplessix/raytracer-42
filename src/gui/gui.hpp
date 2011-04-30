//
// gui.hpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Wed Apr 27 13:06:58 2011 franck lavisse
// Last update Sat Apr 30 17:57:44 2011 franck lavisse
//
#ifndef __GUI_H__
#define __GUI_H__

#include <QApplication>
#include <QWidget>
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

class Color;

int	gui(int argc, char **argv);

class	Gui : public QMainWindow
{
Q_OBJECT

public:
  Gui();
  ~Gui();

  bool	getTransparenceBool(void) const;
  int	getTransparenceInt(void) const;
  int	getTransparenceDiffusion(void) const;

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

public slots:
  void	launch_raytracer(void);

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
  QCheckBox	*_transparence;
  QSpinBox	*_transpBox;
  QSpinBox	*_transpDiffusion;
};

#endif
