//
// gui.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed May 11 18:57:40 2011 loick michard
// Last update Sun May 29 13:04:15 2011 loick michard
//

#include <QApplication>
#include <QtGui>
#include <QMutexLocker>
#include <sstream>
#include <QSystemTrayIcon>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>

#include "gui.hpp"

#include "RenderingConfiguration.hpp"
#include "Color.hpp"
#include "Raytracer.hpp"
#include "CinemaCamera.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Rotation.hpp"
#include "ObjectPrimitive.hpp"
#include "Sphere.hpp"
#include "Spot.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"
#include "Parallelogram.hpp"
#include "Torus.hpp"
#include "CubeTroue.hpp"
#include "PerlinNoise.hpp"
#include "CubeMap.hpp"
#include "Sett.hpp"

Scene           *createScene()
{
  Material      mat("base");
  mat.setColor(Color(255, 255, 255));
  mat.setSpecularCoeff(0.5);
  mat.setSpecularPow(50);
  Material      *reflection = new Material("Reflection");
  *reflection = mat;
  reflection->setReflectionCoeff(1);
  // reflection->setTransmissionCoeff(0);
  // reflection->setRefractionIndex(1.33);
  //reflection->setLimitTexture(new Texture("stripes.png"));  
  // Material      refraction = mat;
  // refraction.setTransmissionCoeff(0);
  // refraction.setRefractionIndex(1.33);
  // Material      matFloor("sol");
  // matFloor.setReflectionCoeff(0);
  // matFloor.setColor(Color(255, 255, 255));
  // matFloor.setSpecularCoeff(0.5);
  // matFloor.setSpecularPow(50);

  vector<Camera*> cam;
  Camera* camera = new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0));
  camera->setFocus(40);
  camera->setTarget(Point(20, 0, 0));
  cam.push_back(camera);

  // reflection->setTexture(new Texture("terre.jpg"));
  vector<ObjectPrimitive*> primitives;
  // primitives.push_back(new Pa(NULL, Point(30, 0, -3), Rotation(0, 0, 0),
  // 				  reflection, 3));

  primitives.push_back(new Sphere(NULL, Point(20, 0, -1),
				  Rotation(0, 0, 0), reflection, 2));
  primitives.push_back(new Sphere(NULL, Point(40, -6, -1),
                                  Rotation(0, 0, 0), reflection, 2));
  // Material special = refraction;
  // PerlinNoise *perlin = new PerlinNoise();
  // special.setTransmissionCoeff(0);
  // special.setTexture(perlin);

  // refraction.setTransmissionCoeff(0.9);
  // refraction.setRefractionIndex(1.5);
  vector<Object*> obj;
  obj.push_back(new Object(primitives, Rotation(0, 0, 0), Point(0, 0, 0),
			   true));

  vector<Light*> light;
  //light.push_back(new Spot(Point(10, 5, 2), Color(255, 255, 255)));
  light.push_back(new Spot(Point(10, 10, 0), Color(255, 255, 255)));

  Scene         *res = new Scene(cam, obj, light);
  return (res);
}

bool RaytracerGUI::setConfiguration()
{
  if (_ui->_mode->currentIndex() == 0)
    _config->setRenderingSamplingMethod(RSM_LINEAR_HORIZONTAL);
  else if (_ui->_mode->currentIndex() == 1)
    _config->setRenderingSamplingMethod(RSM_LINEAR_VERTICAL);
  else if (_ui->_mode->currentIndex() == 2)
    _config->setRenderingSamplingMethod(RSM_UNPIXELISING);
  else if (_ui->_mode->currentIndex() == 3)
    _config->setRenderingSamplingMethod(RSM_RANDOM_HORIZONTAL);
  else if (_ui->_mode->currentIndex() == 4)
    _config->setRenderingSamplingMethod(RSM_RANDOM_VERTICAL);
  else
    _config->setRenderingSamplingMethod(RSM_RANDOM_PIXEL);
  _config->setWidth(_ui->_width->value());
  _config->setHeight(_ui->_height->value());
  _config->setNbThreads(_ui->_threads->value());
  _config->setCurrentCamera(_ui->_camera->currentIndex());
  _config->setAntialiasing(_ui->_antialiasing->value());
  _config->setFieldDepthSampling(_ui->_depthFieldSampling->value());
  _config->setFieldDepthEnabled(_ui->_depthField->isChecked());

  _config->_3DEnabled = _ui->_3d->isChecked();
  _config->_3DMode = _ui->_3DMode->currentIndex();
  _config->_eyesSpace = _ui->_3DSpace->value();

  _config->setKdTreeDepth(_ui->_kdTreeDepth->value());
  _config->setKdTreeEnabled(_ui->_kdTree->isChecked());
  _config->setExposure(_ui->_exposure->value());
  _config->setDirectLightingCoeff(_ui->_directLightingIntensity->value());
  _config->setDirectLighting(_ui->_directLighting->isChecked());
  _config->setDiffuseLighting(_ui->_diffuseLighting->isChecked());
  _config->setSpecularLighting(_ui->_specularLighting->isChecked());
  _config->setDiffuseShadingSampling(_ui->_diffuseShadingSampling->value());
  _config->setDiffuseShadingEnabled(_ui->_diffuseShading->isChecked());
  _config->setReflection(_ui->_reflection->isChecked(),
			 _ui->_reflectionLimit->value(),
			 _ui->_diffuseReflection->isChecked(),
			 _ui->_diffuseReflectionSampling->value());
  _config->setTransparencyMaxDepth(_ui->_transparencyLimit->value());
  _config->setTransparency(_ui->_transparency->isChecked());

  if (_ui->_cubeMap->isChecked())
    {
      if (_cubeMap)
      	delete _cubeMap;
      _cubeMap = NULL;
      try
	{
	  _cubeMap = new CubeMap(_ui->_cubeMapRepertory->text().toStdString());
	}
      catch (int error)
	{
	  if (error == CubeMap::ERROR_INVALID_FILE)
	    this->sendErrorMessage(tr("Cube Map: dossier invalide").
				   toStdString());
	  return (false);
	}
      _config->setCubeMap(_cubeMap);
    }
  else
    _config->setCubeMap(NULL);
  _config->setBackgroundColor(Color((*_backgroundColor).rgba()));
  _config->setMinimalAmbiantLightingEnabled(_ui->
					    _ambiantLighting->isChecked());
  _config->setMinimalAmbiantLighting(_ui->_ambiantLightingCoeff->value());
  _config->setAdditiveAmbiantLighting((*_ambiantColor).rgba());
  _config->setAdditiveAmbiantLightingEnabled(_ui->_ambiantColor->isChecked());
  _config->setAmbientOcclusionSampling(_ui->
				       _ambientOcclusionSampling->value());
  _config->setAmbientOcclusionEnabled(_ui->_ambientOcclusion->isChecked());

  _config->setPhotonMappingSampling(_ui->
				    _photonMappingValue->value());
  _config->setPhotonMappingEnabled(_ui->_photonMapping->isChecked());

  // {
  //   std::ofstream ofs("fichierDeSerialisation");
  //   boost::archive::text_oarchive oa(ofs);
  //   oa << *_config;

  //   RenderingConfiguration newConf;
  //   std::ifstream ifs("fichierDeSerialisation");
  // boost::archive::text_iarchive ia(ifs);
  // ia >> newConf;
  // }

  return (true);
}

void	RaytracerGUI::selectCubeMap()
{
  QString file =
    QFileDialog::getExistingDirectory(this,
				      "Selectioner une CubeMap",
				      QString(),
				      QFileDialog::DontUseNativeDialog);
  _ui->_cubeMapRepertory->setText(file);
}

void	RaytracerGUI::selectBackgroundColor()
{
  QColor color = QColorDialog::getColor(*_backgroundColor, this,
					"Selectionner la couleur de fond",
					QColorDialog::ShowAlphaChannel |
					QColorDialog::DontUseNativeDialog);
  if (color.isValid())
    {
      *_backgroundColor = color;
      ostringstream oss;

      oss << "background-color: rgb(" << _backgroundColor->red() <<
	"," << _backgroundColor->green() << "," <<
	_backgroundColor->blue() << ");";

      string style = oss.str();
      _ui->_backgroundColor->setStyleSheet(style.c_str());
    }
}

void    RaytracerGUI::selectAmbiantColor()
{
  QColor color = QColorDialog::getColor(*_ambiantColor, this,
                                        "Selectionner la couleur de fond",
                                        QColorDialog::ShowAlphaChannel |
					QColorDialog::DontUseNativeDialog);
  if (color.isValid())
    {
      *_ambiantColor = color;
      ostringstream oss;

      oss << "background-color: rgb(" << _ambiantColor->red() <<
	"," << _ambiantColor->green() << "," <<
	_ambiantColor->blue() << ");";

      string style = oss.str();
      _ui->_ambiantColorButton->setStyleSheet(style.c_str());
      _ui->_ambiantColor->setChecked(true);
    }
}

void RaytracerGUI::clearConsole()
{
  _message = "";
}

void RaytracerGUI::paintEvent(QPaintEvent*)
{
  QMutexLocker	locker(&_mutex);
  if (_image)
    {
      *_pixmap = _pixmap->fromImage(*_image);
      _ui->_image->setPixmap(*_pixmap);
    }
  if (!_isRendering)
    {
      if (!_isMultiThreading)
	_ui->_mode->setEnabled(true);
      _ui->_width->setEnabled(true);
      _ui->_height->setEnabled(true);
      _ui->_threads->setEnabled(true);
      _ui->action_Play->setEnabled(true);
    }
}

void RaytracerGUI::setCameras()
{
  while (_ui->_camera->currentIndex() != -1)
    _ui->_camera->removeItem(_ui->_camera->currentIndex());
  vector<Camera*> cameras =_scene->getCameras();
  for (unsigned int i = 0; i < cameras.size(); i++)
    {
      if (cameras[i]->getName() != "")
	_ui->_camera->addItem(cameras[i]->getName().c_str());
      else
	{
	  char name[50];
	  snprintf(name, 50, "Camera %d", i + 1);
	  _ui->_camera->addItem(name);
	}
    }
}

void RaytracerGUI::drawWindow()
{
  if (_endOfRendering)
    {
      _endOfRendering = false;
      _sticon->showMessage(tr("Rendu"), tr("Le rendu est terminé"));
    }
  if (_isRendering)
    _ui->_progressBar->setValue(_progress);
  _ui->_console->setHtml(_message.c_str());
  _ui->_console->moveCursor(QTextCursor::End);
  repaint();
}

void RaytracerGUI::threadsChange(int i)
{
  if (i > 1)
    {
      _isMultiThreading = true;
      _ui->_mode->setEnabled(false);
      _ui->_mode->setCurrentIndex(0);
    }
  else
    {
      _isMultiThreading = false;
      _ui->_mode->setEnabled(true);
    }
}

RaytracerGUI::RaytracerGUI(QWidget *parent)
  : QMainWindow(parent), _config(new RenderingConfiguration()),
    _raytracer(new Raytracer()), _backgroundColor(new QColor(0, 0, 0)), 
    _ambiantColor(new QColor(255, 255, 255)), _image(NULL),
    _cubeMap(NULL), _scene(NULL), _pixmap(new QPixmap()),
    _ui(new Ui::MainWindow), _isRendering(false), _pause(false),
    _sticon(new QSystemTrayIcon(QIcon("images/image.png"))),
    _endOfRendering(false), _actionRealQuit(new QAction(tr("Quitter"), this)),
    _clusterTimer(NULL),
    _isConnected(false), _isMultiThreading(false)
{
  _actionRealQuit->setShortcut(tr("Ctrl+Q"));
  _initDialogCluster();
  _ui->setupUi(this);
  _ui->_progressBar->setHidden(true);
  _ui->menuFichier->addAction(_actionRealQuit);
  _menuSticon = new QMenu();
  _menuSticon->addAction(_ui->action_Play);
  _menuSticon->addAction(_ui->action_Pause);
  _menuSticon->addAction(_ui->action_Stop);
  _menuSticon->addAction(_actionRealQuit);
  _sticon->setContextMenu(_menuSticon);
  connect(_sticon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	  this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
  _sticon->show();
  _ui->_clusterDock->hide();
  _ui->actionDeconnexion->setVisible(false);
  QObject::connect(_ui->_cubeMapButton, SIGNAL(clicked()),
  		   this, SLOT(selectCubeMap()));
  QObject::connect(_ui->_backgroundColor, SIGNAL(clicked()),
                   this, SLOT(selectBackgroundColor()));
  QObject::connect(_ui->_ambiantColorButton, SIGNAL(clicked()),
                   this, SLOT(selectAmbiantColor()));
  QObject::connect(_ui->action_Play, SIGNAL(triggered()),
                   this, SLOT(startRender()));
  QObject::connect(_ui->action_Pause, SIGNAL(triggered()),
                   this, SLOT(pauseRendering()));
  QObject::connect(_ui->action_Stop, SIGNAL(triggered()),
                   this, SLOT(stopRendering()));
  QObject::connect(_ui->action_SaveImage, SIGNAL(triggered()),
                   this, SLOT(saveImage()));
  QObject::connect(_ui->actionEffacer_la_console, SIGNAL(triggered()),
                   this, SLOT(clearConsole()));
  QObject::connect(_actionRealQuit, SIGNAL(triggered()),
                   this, SLOT(realQuit()));
  QObject::connect(_ui->actionLancer_un_serveur, SIGNAL(triggered()),
                   this, SLOT(launchServer()));
  QObject::connect(_ui->actionSe_connecter_un_serveur, SIGNAL(triggered()),
                   this, SLOT(connectToCluster()));
  QObject::connect(_ui->actionEditMaterial, SIGNAL(triggered()),
                   this, SLOT(openEditMaterialDialog())); 
  QObject::connect(_ui->actionDeconnexion, SIGNAL(triggered()),
                   this, SLOT(disconnect()));
  QObject::connect(_ui->_threads, SIGNAL(valueChanged(int)),
                   this, SLOT(threadsChange(int)));
  _scene = createScene();
  _raytracer->setScene(*_scene);
  _raytracer->setRenderingConfiguration(_config);
  _raytracer->setRenderingInterface(this);
  this->setCameras();
  _timer = new QTimer();
  _timer->setInterval(50);
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(drawWindow()));
  QObject::connect(_ui->action_Charger, SIGNAL(triggered()),
                   this, SLOT(loadScene()));
}

RaytracerGUI::~RaytracerGUI()
{
  delete _ui;
  delete _config;
  delete _raytracer;
  if (_cubeMap)
    delete _cubeMap;
  if (_scene)
    delete _scene;
  if (_image)
    delete _image;
  delete _pixmap;
  delete _sticon;
  delete _menuSticon;
  delete _clusterDialog;
  delete _clusterDialogUi;
  delete _launchServerDialog;
  delete _launchServerDialogUi;
}

void		gui(int ac, char **av)
{
  QApplication	app(ac, av);
  QTranslator	translator;
  QString	locale = QLocale::system().name().section('_', 0, 0);
  RaytracerGUI	gui;

  app.setQuitOnLastWindowClosed(false);
  cout << "locale used: " << locale.toStdString() << endl;
  translator.load("raytracer-42_" + locale);
  app.installTranslator(&translator);
  gui.show();
  app.exec();
}
