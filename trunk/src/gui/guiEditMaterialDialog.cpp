//
// guiEditMaterialDialog.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May 24 18:27:53 2011 loick michard
// Last update Sun May 29 17:48:39 2011 loick michard
//

#include <QMutexLocker>
#include <sstream>
#include <iostream>
#include <QColorDialog>
#include <QFileDialog>
#include "CheckerBoard.hpp"
#include "CubeMap.hpp"
#include "guiEditMaterialDialog.hpp"

GuiEditMaterialDialog::GuiEditMaterialDialog()
{
  _isSet = false;
  _dialog = new Ui::editMaterialDialog;
  _dialog->setupUi(this);
  _color = new QColor(0, 0, 0);
  QObject::connect(_dialog->_ok, SIGNAL(clicked()),
                   this, SLOT(closeDialog()));
  QObject::connect(_dialog->_color, SIGNAL(clicked()),
                   this, SLOT(selectColor()));
  QObject::connect(_dialog->_materials, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(fillFields()));
  QObject::connect(_dialog->_specular, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_specularPow, SIGNAL(valueChanged(int)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_reflection, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_transmission, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_refraction, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_diffuseReflection, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_find, SIGNAL(clicked()),
                   this, SLOT(getImage()));
  QObject::connect(_dialog->_textureType, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(updateTextureImage(int)));
  QObject::connect(_dialog->_textureX, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_textureY, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_imagePath,
		   SIGNAL(textChanged(QString)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_texture, SIGNAL(clicked(bool)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_proceduralDeformation, SIGNAL(clicked(bool)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_deformationType, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(updateTextureImage(int)));
  QObject::connect(_dialog->_deformationCoeff, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_findHeightmap, SIGNAL(clicked()),
                   this, SLOT(getHeightmap()));
  QObject::connect(_dialog->_bumpmapType, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(updateHeightmap(int)));
  QObject::connect(_dialog->_bumpmapX, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_bumpmapY, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_bumpmapping, SIGNAL(clicked(bool)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_findLimited, SIGNAL(clicked()),
                   this, SLOT(getLimitTexture()));
  QObject::connect(_dialog->_limitedX, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_limitedY, SIGNAL(valueChanged(double)),
                   this, SLOT(updateMaterial()));
  QObject::connect(_dialog->_limitedTexture, SIGNAL(clicked(bool)),
                   this, SLOT(updateMaterial()));

  _image = new QImage(150, 150, QImage::Format_ARGB32);
  _image->fill(0);
  _pixmap = new QPixmap();
  _scene = createScene();
  _raytracer = new Raytracer();
  _config = new RenderingConfiguration();
  this->setConfiguration();
  _raytracer->setScene(*_scene);
  _raytracer->setRenderingConfiguration(_config);
  _raytracer->setRenderingInterface(this);
}

void	GuiEditMaterialDialog::updateTextureImage(int i)
{
  if (i == 0)
    _dialog->_imageGroup->setEnabled(true);
  else
    _dialog->_imageGroup->setEnabled(false);
  updateMaterial();
}

void    GuiEditMaterialDialog::updateHeightmap(int i)
{
  if (i == 0)
    _dialog->_heightmap->setEnabled(true);
  else
    _dialog->_heightmap->setEnabled(false);
  updateMaterial();
}

Scene* GuiEditMaterialDialog::createScene()
{
  vector<Camera*> cam;
  Camera* camera = new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0));
  camera->_width = 0.5;
  camera->_height = 0.5;
  cam.push_back(camera);

  vector<ObjectPrimitive*> primitives;
  primitives.push_back(new Sphere(NULL, Point(20, 0, 0),
                                  Rotation(0, 0, 0), _currentMat, 3.0));
  vector<Object*> obj;
  obj.push_back(new Object(primitives, Rotation(0, 0, 0), Point(0, 0, 0),
                           true));

  vector<Light*> light;
  light.push_back(new Spot(Point(12, 0, 4), Color(255, 255, 255)));

  Scene         *res = new Scene(cam, obj, light);
  return (res);
}

void GuiEditMaterialDialog::setConfiguration()
{
  _config->setRenderingSamplingMethod(RSM_RANDOM_PIXEL);
  _config->setWidth(150);
  _config->setHeight(150);
  _config->setNbThreads(2);
  _config->setCurrentCamera(0);
  _config->setCubeMap(new CubeMap(":cubemap/cubemaps/Maskonaive3"), 
		      ":cubemap/cubemaps/Maskonaive3");
  _config->setAntialiasing(2);
  _config->setFieldDepthEnabled(false);
  _config->setKdTreeEnabled(false);
  _config->setExposure(3);
  _config->setDirectLightingCoeff(0);
  _config->setDirectLighting(false);
  _config->setDiffuseLighting(true);
  _config->setSpecularLighting(true);
  _config->setDiffuseShadingEnabled(false);
  _config->setReflection(true,
                         50,
                         true,
                         30);
  _config->setTransparencyMaxDepth(10);
  _config->setTransparency(true);
}

void GuiEditMaterialDialog::paintEvent(QPaintEvent*)
{
  QMutexLocker locker(&_mutex);

  if (_image)
    {
      *_pixmap = _pixmap->fromImage(*_image);
      _dialog->_image->setPixmap(*_pixmap);
    }
}

GuiEditMaterialDialog::~GuiEditMaterialDialog()
{
  
}

void    GuiEditMaterialDialog::selectColor()
{
  QColor color = QColorDialog::getColor(*_color, this,
                                        "Selectionner la couleur",
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

void GuiEditMaterialDialog::getImage()
{
  QString image = 
    QFileDialog::getOpenFileName(this,
				 tr("Selectionez une Texture"),
				 QString(), "*.png *.gif *.jpeg *.bmp *.jpg",
				 0, QFileDialog::DontUseNativeDialog);
  if (image != "")
    _dialog->_imagePath->setText(image);
  updateMaterial();
}

void GuiEditMaterialDialog::getLimitTexture()
{
  QString image =
    QFileDialog::getOpenFileName(this,
                                 tr("Selectionez une Texture limitante"),
                                 QString(),
                                 "*.png *.gif *.jpeg *.bmp *.jpg",
                                 0,
                                 QFileDialog::DontUseNativeDialog);
  if (image != "")
    _dialog->_limitedImage->setText(image);
  updateMaterial();
}

void GuiEditMaterialDialog::getHeightmap()
{
  QString image =
    QFileDialog::getOpenFileName(this,
                                 tr("Selectionez une heightmap"),
                                 QString(),
                                 "*.png *.gif *.jpeg *.bmp *.jpg",
                                 0,
                                 QFileDialog::DontUseNativeDialog);
  if (image != "")
    _dialog->_bumpmapHeightmap->setText(image);
  updateMaterial();
}

void GuiEditMaterialDialog::updateMaterial()
{
  int   index = _dialog->_materials->currentIndex();

  if (index >= 0 && _isSet)
    {
      _currentMat = _materials->at(index);
      _materials->at(index)->setColor(_color->rgba());
      if (_dialog->_texture->isChecked())
	{
	  if (_dialog->_textureType->currentIndex() == 0)
	    {
	      if (_dialog->_imagePath->text() != "" &&
		  (!_materials->at(index)->_texture ||
		   _dialog->_imagePath->text().toStdString() != 
		   _materials->at(index)->_texture->getName()))
		{
		  _materials->at(index)->
		    setTexture(new Texture(_dialog->
					   _imagePath->text().toStdString(),
					   _dialog->_textureX->value(),
					   _dialog->_textureY->value()));
		}
	    }
	  else if (!_materials->at(index)->_isTextured ||
		   _materials->at(index)->_texture->_type !=
		   _dialog->_textureType->currentIndex())
	    {
	      if (_dialog->_textureType->currentIndex() == 4)
		{
		  _materials->at(index)->
                    setTexture(new CheckerBoard(_dialog->_textureX->value(),
						_dialog->_textureY->value()));
		}
	      else
		{
		  _materials->at(index)->_isTextured = true;
		  PerlinNoise *texture =
		    new PerlinNoise(_dialog->_textureX->value(),
				    _dialog->_textureY->value());
		  if (_dialog->_textureType->currentIndex() == 2)
		    texture->setMarbleProperties();
		  else if (_dialog->_textureType->currentIndex() == 3)
		    texture->setWoodProperties(); 
		  _materials->at(index)->setTexture(texture);
		  _materials->at(index)->_texture->_type =
		    _dialog->_textureType->currentIndex();
		}
	    }
	}
      else
	_materials->at(index)->_isTextured = false;
      if (_materials->at(index)->_texture)
	{
	  _materials->at(index)->_texture->_repeatWidth =
	    _dialog->_textureX->value();
	  _materials->at(index)->_texture->_repeatHeight =
	    _dialog->_textureY->value();
	}
      _materials->at(index)->_specularCoeff = _dialog->_specular->value();
      _materials->at(index)->_specularPow = _dialog->_specularPow->value();
      _materials->at(index)->_reflectionCoeff = _dialog->_reflection->value();
      _materials->at(index)->_transmissionCoeff =
	_dialog->_transmission->value();
      _materials->at(index)->_refractionIndex = _dialog->_refraction->value();
      _materials->at(index)->_diffusedReflectionCoeff = 
	_dialog->_diffuseReflection->value();

      _materials->at(index)->_hasBumpMap = _dialog->_bumpmapping->isChecked();
      if (_materials->at(index)->_hasBumpMap)
        {
	  if (_dialog->_bumpmapType->currentIndex() == 0)
            {
              if (_dialog->_bumpmapHeightmap->text() != "" &&
                  (!_materials->at(index)->_heightmap ||
                   _dialog->_bumpmapHeightmap->text().toStdString() !=
                   _materials->at(index)->_heightmap->getName()))
                {
		  _materials->at(index)->
                    setHeightmap(new Texture(_dialog->
					     _bumpmapHeightmap
					     ->text().toStdString(),
					     _dialog->_bumpmapX->value(),
					     _dialog->_bumpmapY->value()));
		}
	    }
	  else if (!_materials->at(index)->_heightmap ||
                   _materials->at(index)->_heightmap->_type !=
                   _dialog->_bumpmapType->currentIndex())
	    {
	      _materials->at(index)->
		setHeightmap(new PerlinNoise(_dialog->_bumpmapX->value(),
					     _dialog->_bumpmapY->value()));
	    }
	  if (_materials->at(index)->_heightmap)
	    {
	      _materials->at(index)->_heightmap->_repeatWidth =
		_dialog->_bumpmapX->value();
	      _materials->at(index)->_heightmap->_repeatHeight =
		_dialog->_bumpmapY->value();
	    }
	}

      _materials->at(index)->_hasNormalDeformation |=
        _dialog->_proceduralDeformation->isChecked();
      if (!_dialog->_proceduralDeformation->isChecked())
	_materials->at(index)->_deformationType = -1;
      else
	_materials->at(index)->_deformationType =
	  _dialog->_deformationType->currentIndex();
      _materials->at(index)->_deformationCoeff =
        _dialog->_deformationCoeff->value();

      if (_dialog->_limitedTexture->isChecked())
	{
	  if (_dialog->_limitedImage->text() != "" &&
	      (!_materials->at(index)->_limitTexture ||
	       _dialog->_limitedImage->text().toStdString() !=
	       _materials->at(index)->_limitTexture->getName()))
	    {
	      _materials->at(index)->
		_limitTexture = new Texture(_dialog->
					    _limitedImage
					    ->text().toStdString(),
					    _dialog->_limitedX->value(),
					    _dialog->_limitedY->value());
	    }
	  else if (_dialog->_limitedImage->text() != "")
	    {
	      _materials->at(index)->_limitTexture->_repeatWidth =
		_dialog->_limitedX->value();
	      _materials->at(index)->_limitTexture->_repeatHeight =
		_dialog->_limitedY->value();
	    }
        }
      else
	{
	  delete _materials->at(index)->_limitTexture;
	  _materials->at(index)->_limitTexture = NULL;
	}

      _raytracer->stopRendering();
      _scene = createScene();
      _raytracer->setScene(*_scene);
      _raytracer->launchRendering();
    }
}

void GuiEditMaterialDialog::closeDialog()
{
  _raytracer->stopRendering();
  hide();
}

void GuiEditMaterialDialog::pixelHasBeenRendered(int x, int y,
						 Color color)
{
  QMutexLocker locker(&_mutex);

  if (_image)
    _image->setPixel(x, y, QColor(color._r, color._g,
  				  color._b, color._a).rgba());
}

void GuiEditMaterialDialog::fillFields()
{
  _isSet = false;
  int	index = _dialog->_materials->currentIndex();

  if (index >= 0)
    {
      _currentMat = _materials->at(index);
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
				       at(index)->_texture->_repeatHeight);
	  _dialog->_textureType->setCurrentIndex(_materials->
						 at(index)->_texture->_type);
	  if (_materials->at(index)->_texture->_type == 0 &&
	      _materials->at(index)->_texture->_image)
	    {
	      _dialog->_imagePath->setText(_materials->at(index)->
					   _texture->getName().c_str());
	    }
	}
      else
	_dialog->_textureType->setCurrentIndex(3);
      _dialog->_specular->setValue(_materials->at(index)->_specularCoeff);
      _dialog->_specularPow->setValue(_materials->at(index)->_specularPow);
      _dialog->_reflection->setValue(_materials->at(index)->_reflectionCoeff);
      _dialog->_transmission->setValue(_materials->
				       at(index)->_transmissionCoeff);
      _dialog->_refraction->setValue(_materials->at(index)->_refractionIndex);
      _dialog->_diffuseReflection->setValue(_materials->
					    at(index)->
					    _diffusedReflectionCoeff);
      _dialog->_proceduralDeformation
	->setChecked((_materials->at(index)->_hasNormalDeformation &&
		      _materials->at(index)->_deformationType != -1));
      if (_materials->at(index)->_hasNormalDeformation &&
	  _materials->at(index)->_deformationType != -1)
	_dialog->_deformationType->setCurrentIndex(_materials->at(index)->
						   _deformationType);
      else
	_dialog->_deformationType->setCurrentIndex(0);
      _dialog->_deformationCoeff->setValue(_materials->at(index)->
					   _deformationCoeff);

      _dialog->_bumpmapping->setChecked(_materials->at(index)->
					_hasBumpMap);
      if (_materials->at(index)->_hasBumpMap && _materials->
	  at(index)->_heightmap)
	{
	  _dialog->_bumpmapX->setValue(_materials->
				       at(index)->_heightmap->_repeatWidth);
	  _dialog->_bumpmapY->setValue(_materials->
				       at(index)->_heightmap->_repeatHeight);
	  if (_materials->at(index)->_heightmap->_type == 0 &&
              _materials->at(index)->_heightmap->_image)
	    {
	      _dialog->_bumpmapType->setCurrentIndex(0);
	      _dialog->_bumpmapHeightmap->
		setText(_materials->at(index)->_heightmap->getName().c_str());
	    }
	  else
	    _dialog->_bumpmapType->setCurrentIndex(1);
	}
      else
	_dialog->_bumpmapType->setCurrentIndex(1);

      if (_materials->at(index)->_limitTexture)
	{
	  _dialog->_limitedTexture->setChecked(true);
	  _dialog->_limitedX->setValue(_materials->
				       at(index)->_limitTexture->_repeatWidth);
	  _dialog->_limitedY->
	    setValue(_materials->at(index)->_limitTexture->_repeatHeight);
	  _dialog->_limitedImage->setText(_materials->
					  at(index)->_limitTexture->
					  getName().c_str());
	}
      else
	_dialog->_limitedTexture->setChecked(false);
    }
  _isSet = true;
  updateMaterial();
}

void 
GuiEditMaterialDialog::setMaterials(const vector<Material*>& materials)
{
  _isSet = false;
  _materials = &materials;
  if (_materials->size())
    {
      _dialog->_materials->clear();
      for (unsigned int i = 0; i < _materials->size(); i++)
	_dialog->_materials->insertItem(i,
					_materials->at(i)->getName().c_str());
      _dialog->_materials->setCurrentIndex(0);
      this->fillFields();
      _isSet = true;
      _raytracer->stopRendering();
      delete _scene;
      _scene = createScene();
      _raytracer->setScene(*_scene);
      _raytracer->launchRendering();
    }
  else
    hide();
}
