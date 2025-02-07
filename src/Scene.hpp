//
// Scene.hpp for raytracer in /home/michar_l//Raytracer
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Tue Apr 26 11:43:19 2011 loick michard
// Last update Mon Oct  8 16:40:50 2012 samuel olivier
//

#ifndef _SCENE_HPP_
#define _SCENE_HPP_
#define _USE_MATH_DEFINES // Pour la portabilité de PI (visual C++)

#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <QString>
#include <QColor>
#include <QObject>
#include <QtXml>
#include <sstream>
#include <lib3ds/file.h>
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "CinemaCamera.hpp"
#include "RenderingInterface.hpp"
#include "PerlinNoise.hpp"
#include "Rotation.hpp"
#include "Vector.hpp"
#include "Object.hpp"
#include "Light.hpp"
#include "Sett.hpp"
#include "Plane.hpp"
#include "Torus.hpp"
#include "Triangle.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "CubeTroue.hpp"
#include "ParallelLight.hpp"
#include "ParallelogramLight.hpp"
#include "SphericalLight.hpp"
#include "Spot.hpp"
#include "Sphere.hpp"
#include "EquationPrimitive.hpp"
#include "Parallelogram.hpp"
#include "A3DSParser.hpp"

using namespace std;

class	Scene
{
public:
  Scene(vector<Camera*> cameras,
	vector<Object*> objects,
	vector<Light*> lights);
  Scene(vector<Camera*> cameras,
	vector<Object*> objects,
	vector<Light*> lights,
	vector<Material*> materials);
  Scene(void);
  ~Scene(void);

  void				loadFromFile(string, RenderingInterface*);

  const vector<Camera*>&		getCameras(void) const;
  const vector<Object*>&		getObjects(void) const;
  const vector<Light*>&			getLights(void) const;
  const vector<Material*>&		getMaterials(void) const;
  const Camera&				getCamera(int) const;
  const Object&				getObject(int) const;
  const Light&				getLight(int) const;
  const Material&			getMaterial(int) const;
  int					getNbCameras(void) const;
  int					getNbObjects(void) const;
  int					getNbLights(void) const;
  int					getNbMaterials(void) const;
  bool					isValid(void) const;
  const QString&			getFilename(void) const;
  const vector<QString>&		getSceneFilenames(void) const;

private:
  bool				_hasError;
  bool				_parsingDone;
  RenderingInterface*		_interface;
  vector<Camera*>		_cameras;
  vector<Object*>		_objects;
  vector<Light*>		_lights;
  vector<Material*>		_materials;
  QString			_filename;
  vector<QString>		_sceneFilenames;

  void			_clearOldScene(void);
  QDomDocument		_loadFromFile_checkAndGetFile(string filename);
  bool			_loadFromFile_validFirstDepth(QDomNode n);
  void			_dispatcher(QDomNode	node,
				    bool&	has_cameras,
				    bool&	has_materials,
				    bool&	has_objects,
				    bool&	has_lights);
  void			_parseCameras(QDomNode);
  void			_parseCamera(QDomNode);
  void			_parseCameraCinema(QDomNode, QString);
  bool			_cameraExists(string);
  void			_parseMaterials(QDomNode);
  void			_parseMaterial(QDomNode);
  void			_parseObjects(QDomNode);
  void			_parseObject(QDomNode);
  void			_parseObjectOptions(QDomNode);
  Point			_parsePosition(QDomNode, string);
  Point			_parse2DPosition(QDomNode, string);
  Rotation		_parseRotation(QDomNode);
  bool			_checkContentIsSingleText(QDomNode, string);
  void			_putWarning(string, QDomNode);
  void			_putWarning(string);
  void			_putWarning(QString);
  void			_putWarning(QString, QDomNode);
  void			_putError(string, QDomNode);
  void			_putError(QString, QDomNode);
  void			_putError(string);
  void			_putError(QString);
  void			_putSuccess(string);
  void			_putSuccess(QString);
  void			_putInfo(string);
  void			_putInfo(QString);
  void			_parseMaterialOptions(QDomNode, QString);
  QRgb			_parseColor(QDomNode);
  bool			_isDouble(QString);
  bool			_isInt(QString);
  bool			_isHexa(QString);
  double		_parseDouble(QDomNode, double, double, string);
  int			_parseInt(QDomNode, int, int, string);
  void			_parseNormalDef(QDomNode, Material*);
  string		_parseFile(QDomNode, string);
  string		_parseDir(QDomNode, string);
  Texture*		_parseTexture(QDomNode, string);
  QString		_parseTextureType(QDomNode, string);
  bool			_parseBoolean(QDomNode, string);
  void			_parsePrimitives(QDomNode, Object*);
  void			_parsePrimitive(QDomNode, Object*);
  Sphere*		_parseSphere(QDomNode, QString, Object*);
  Torus*		_parseTorus(QDomNode, QString, Object*);
  Plane*		_parsePlane(QDomNode, QString, Object*);
  Cone*			_parseCone(QDomNode, QString, Object*);
  Cylinder*		_parseCylinder(QDomNode, QString, Object*);
  CubeTroue*		_parseCubeTroue(QDomNode, QString, Object*);
  Triangle*		_parseTriangle(QDomNode, QString, Object*);
  EquationPrimitive*	_parseEquation(QDomNode, QString, Object*);
  Parallelogram*	_parseParallelogram(QDomNode, QString, Object*);
  void			_parse3dsFile(QDomNode, QString);
  void			_parseModel(QDomNode);
  bool			_parse3dsIntern(string, string, Object*);
  bool			_parseModel(string, string, Object*);
  bool			_parseModelAssimp(string, string, Object*);
  bool			_parse3dsLib3ds(string, string, Object*);
  void			_parseSett(QDomNode, QString);
  Material*		_getMaterialByName(QString);
  void			_parseLight(QDomNode);
  void			_parseLights(QDomNode);
  Spot*			_parseSpotLight(QDomNode);
  ParallelLight*	_parseParallelLight(QDomNode);
  SphericalLight*	_parseSphericalLight(QDomNode);
  ParallelogramLight*	_parseParallelogramLight(QDomNode);
  bool			_parseCommonElement(QDomNode,
					    ObjectPrimitive*, bool&, bool&);
  bool			_materialExists(QString);
  Material*		_3dsgetFaceMat(int, const map<string, vector<int> >&);
  Texture*		_parseTextureSetTexture(QString, string, QDomNode);
  Material		*_loadAssimpMaterial(const aiScene *scene,
					     aiMaterial *mat,
					     string textureDir);
  void			_loadAssimpNode(const aiScene *scene,
					aiNode *node, Object *obj,
					int matIndex);
};
#endif
