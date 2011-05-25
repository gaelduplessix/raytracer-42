//
// guiEditMaterialDialog.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May 24 18:27:53 2011 loick michard
// Last update Wed May 25 11:22:00 2011 loick michard
//

#include <sstream>
#include <iostream>
#include <QColorDialog>
#include "guiEditMaterialDialog.hpp"

GuiEditMaterialDialog::GuiEditMaterialDialog()
{
  _dialog = new Ui::editMaterialDialog;
  _dialog->setupUi(this);
  _color = new QColor(0, 0, 0);
  QObject::connect(_dialog->_color, SIGNAL(clicked()),
                   this, SLOT(selectColor()));
  QObject::connect(_dialog->_materials, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(fillFields()));
}

GuiEditMaterialDialog::~GuiEditMaterialDialog()
{
  
}

void    GuiEditMaterialDialog::selectColor()
{
  QColor color = QColorDialog::getColor(*_color, this,
                                        "Selectionner la couleur de fond",
                                        QColorDialog::ShowAlphaChannel |
					QColorDialog::DontUseNativeDialog\
					);
  if (color.isValid())
    {
      *_color = color;
      this->fillColor();
      this->updateMaterial();
    }
}

void GuiEditMaterialDialog::fillColor()
{
  ostringstream oss;

  oss << "background-color: rgb(" << _color->red() <<
    "," << _color->green() << "," <<
    _color->blue() << ");";

  string style = oss.str();
  _dialog->_color->setStyleSheet(style.c_str());
}

void GuiEditMaterialDialog::updateMaterial()
{
  int   index = _dialog->_materials->currentIndex();

  if (index >= 0)
    {
      _materials->at(index)->setColor(_color->rgba());
      _dialog->_texture->setChecked(_materials->at(index)->_isTextured);
      if (_materials->at(index)->_isTextured)
        {
          _dialog->_textureX->setValue(_materials->
                                       at(index)->_texture->_repeatWidth);
          _dialog->_textureY->setValue(_materials->
                                       at(index)->_texture->_repeatWidth);
          _dialog->_textureType->setCurrentIndex(_materials->
                                                 at(index)->_texture->_type);
          if (_materials->at(index)->_texture->_type == 0 &&
              _materials->at(index)->_texture->_image)
            {
              _dialog->_imagePath->setText(_materials->at(index)->
                                           _texture->getName().c_str());
            }
        }
    }
  _materials->at(index)->_specularCoeff = _dialog->_specular->value();
  _materials->at(index)->_specularPow = _dialog->_specularPow->value();
  _materials->at(index)->_reflectionCoeff = _dialog->_reflection->value();
  _materials->at(index)->_transmissionCoeff = _dialog->_transmission->value();
  _dialog->_transmission->setValue(_materials->
				   at(index)->_transmissionCoeff);
  _dialog->_refraction->setValue(_materials->at(index)->_refractionIndex);
  _dialog->_diffuseReflection->setValue(_materials->
					at(index)->
					_diffusedReflectionCoeff);  
}

void GuiEditMaterialDialog::fillFields()
{
  int	index = _dialog->_materials->currentIndex();

  if (index >= 0)
    {
      _color->setRgb(_materials->at(index)->_color._r,
		     _materials->at(index)->_color._g,
		     _materials->at(index)->_color._b,
		     _materials->at(index)->_color._a);
      this->fillColor();
      _dialog->_texture->setChecked(_materials->at(index)->_isTextured);
      if (_materials->at(index)->_isTextured)
	{
	  _dialog->_textureX->setValue(_materials->
				       at(index)->_texture->_repeatWidth);
	  _dialog->_textureY->setValue(_materials->
				       at(index)->_texture->_repeatWidth);
	  _dialog->_textureType->setCurrentIndex(_materials->
						 at(index)->_texture->_type);
	  if (_materials->at(index)->_texture->_type == 0 &&
	      _materials->at(index)->_texture->_image)
	    {
	      _dialog->_imagePath->setText(_materials->at(index)->
					   _texture->getName().c_str());
	    }
	}
      _dialog->_specular->setValue(_materials->at(index)->_specularCoeff);
      _dialog->_specularPow->setValue(_materials->at(index)->_specularPow);
      _dialog->_reflection->setValue(_materials->at(index)->_reflectionCoeff);
      _dialog->_transmission->setValue(_materials->
				       at(index)->_transmissionCoeff);
      _dialog->_refraction->setValue(_materials->at(index)->_refractionIndex);
      _dialog->_diffuseReflection->setValue(_materials->
					    at(index)->
					    _diffusedReflectionCoeff);
    }
}

void 
GuiEditMaterialDialog::setMaterials(const vector<Material*>& materials)
{
  _materials = &materials;
  _dialog->_materials->clear();
  for (unsigned int i = 0; i < _materials->size(); i++)
    _dialog->_materials->addItem(_materials->at(i)->getName().c_str());
  _dialog->_materials->setCurrentIndex(0);
  this->fillFields();
}
