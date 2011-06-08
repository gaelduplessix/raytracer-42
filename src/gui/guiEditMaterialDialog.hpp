//
// guiEditMaterialDialog.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May 24 18:21:30 2011 loick michard
// Last update Wed Jun  8 11:09:24 2011 gael jochaud-du-plessix
//

#ifndef _GUIEDITMATERIALDIALOG_HPP_
#define _GUIEDITMATERIALDIALOG_HPP_

#include <QMutex>
#include <QWidget>
#include <QDialog>
#include <QImage>
#include <QTimer>
#include "Raytracer.hpp"
#include "ui_editMaterialDialog.h"
#include "Material.hpp"

class RaytracerGUI;

namespace Ui {
  class editMaterialDialog;
};

class GuiEditMaterialDialog : public QDialog, public RenderingInterface
{
  Q_OBJECT

  public:
  GuiEditMaterialDialog(RaytracerGUI* gui);
  ~GuiEditMaterialDialog();

  void paintEvent(QPaintEvent*);
  void fillColor();
  void setConfiguration();
  Scene* createScene();
  void pixelHasBeenRendered(int x, int y, Color color);
  void setMaterials(const vector<Material*>& materials);

public slots:
  void getHeightmap();
  void getLimitTexture();
  void updateTextureImage(int i);
  void updateHeightmap(int i);
  void getImage();
  void closeDialog();
  void updateMaterial();
  void fillFields();
  void selectColor();

public:
  RenderingConfiguration        *_config;
private:
  RaytracerGUI			*_gui;
  Scene                         *_scene;
  Raytracer                     *_raytracer;
  Ui::editMaterialDialog*	_dialog;
  const vector<Material*>	*_materials;
  QColor       			*_color;
  bool				_isSet;
  QImage			*_image;
  QPixmap			*_pixmap;
  QTimer			*_timer;
  Material			*_currentMat;
  QMutex			_mutex;
};

#endif
