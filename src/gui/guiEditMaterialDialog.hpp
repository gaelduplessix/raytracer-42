//
// guiEditMaterialDialog.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May 24 18:21:30 2011 loick michard
// Last update Wed May 25 10:38:37 2011 loick michard
//

#include <QWidget>
#include <QDialog>
#include "ui_editMaterialDialog.h"
#include "Material.hpp"

namespace Ui {
  class editMaterialDialog;
};

class GuiEditMaterialDialog : public QDialog
{
  Q_OBJECT

  public:
  GuiEditMaterialDialog();
  ~GuiEditMaterialDialog();

  void fillColor();
  void setMaterials(const vector<Material*>& materials);

public slots:
  void updateMaterial();
  void fillFields();
  void selectColor();

private:
  Ui::editMaterialDialog*	_dialog;
  const vector<Material*>	*_materials;
  QColor       			*_color;
};
