//
// gui.hpp for  in /home/laviss_f//raytracer-42
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Wed Apr 27 13:06:58 2011 franck lavisse
// Last update Fri Apr 29 18:06:05 2011 franck lavisse
//
#ifndef __GUI_H__
#define __GUI_H__

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPolygon>
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLine>
#include <QPen>
#include <QRect>
#include <QMainWindow>
#include <QPainter>
#include <QDockWidget>
#include <QLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QTabWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QStringList>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>

int	gui(int argc, char **argv);

class	Gui : public QMainWindow
{
Q_OBJECT

public:
  Gui();
  ~Gui();
  void	putPixel(unsigned char color[3], int x, int y);
  void	rendu(void);
  void	init_dock(void);
  void	accordion(void);	       
  void	samplingMethod(void);
  void	aliasing(void);
  void	reflection(void);		     
  void	directLight(void);			
  void	ambiantOcclusion(void);
  void	photonMapping(void);
  void	lumiereDiffuse(void);
  void	flou(void);

public slots:
  void	launch_raytracer(void);

private:
  QComboBox	*_samplingMethod;
  QWidget	*_widget;
  QPushButton	*_Rendu;
  QGridLayout	*_Grid;
  QDockWidget	*_Dock;
  QGraphicsScene*_Scene;
  QGraphicsItem	*_Item;
  QGraphicsView	*_View;
};

#endif
