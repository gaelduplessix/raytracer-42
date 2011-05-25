//
// guiEditMaterialDialog.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May 24 18:27:53 2011 loick michard
// Last update Wed May 25 17:01:48 2011 loick michard
//

#include <QMutexLocker>
#include <sstream>
#include <iostream>
#include <QColorDialog>
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

  _image = new QImage(150, 150, QImage::Format_ARGB32);
  _pixmap = new QPixmap();
  _timer = new QTimer();
  _timer->setInterval(50);
  _scene = createScene();
  _raytracer = new Raytracer();
  _config = new RenderingConfiguration();
  this->setConfiguration();
  _raytracer->setScene(*_scene);
  _raytracer->setRenderingConfiguration(_config);
  _raytracer->setRenderingInterface(this);
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
  _config->setCubeMap(new CubeMap("cubemaps/DallasW"));
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

  if (index >= 0 && _isSet)
    {
      _currentMat = _materials->at(index);
      _materials->at(index)->setColor(_color->rgba());
      /*_dialog->_texture->setChecked(_materials->at(index)->_isTextured);
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
    }*/
      _materials->at(index)->_specularCoeff = _dialog->_specular->value();
      _materials->at(index)->_specularPow = _dialog->_specularPow->value();
      _materials->at(index)->_reflectionCoeff = _dialog->_reflection->value();
      _materials->at(index)->_transmissionCoeff =
	_dialog->_transmission->value();
      _materials->at(index)->_refractionIndex = _dialog->_refraction->value();
      _materials->at(index)->_diffusedReflectionCoeff = 
	_dialog->_diffuseReflection->value();
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
