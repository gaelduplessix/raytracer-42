######################################################################
# Automatically generated by qmake (2.01a) dim. juin 5 23:46:10 2011
######################################################################

FORMS=forms/raytracer.ui forms/clusterDialog.ui forms/launchServerDialog.ui forms/editMaterialDialog.ui forms/connectToServer.ui forms/Preferences.ui forms/About.ui
RESOURCES=ressources.qrc
QT+=xml
QT+=network
OBJECTS_DIR=./objects
LIBS=-lboost_serialization -l3ds
MOC_DIR=moc
UI_HEADERS_DIR=uiHeaders
TRANSLATIONS=raytracer-42_en.ts raytracer-42_fr.ts
TEMPLATE = app
TARGET = 
DEPENDPATH += src src/equation-solver src/gui
INCLUDEPATH += . src src/equation-solver src/gui

# Input
HEADERS += src/A3DSChunk.hpp \
           src/A3DSLight.hpp \
           src/A3DSMaterial.hpp \
           src/A3DSMesh.hpp \
           src/A3DSParser.hpp \
           src/BoundingBox.hpp \
           src/Camera.hpp \
           src/CheckerBoard.hpp \
           src/CinemaCamera.hpp \
           src/ClusterClient.hpp \
           src/ClusterRenderingThread.hpp \
           src/ClusterServer.hpp \
           src/Color.hpp \
           src/Cone.hpp \
           src/CubeMap.hpp \
           src/CubeTroue.hpp \
           src/Cylinder.hpp \
           src/EquationPrimitive.hpp \
           src/EquationSolver.hpp \
           src/KdTree.hpp \
           src/Light.hpp \
           src/Material.hpp \
           src/Matrix.hpp \
           src/Object.hpp \
           src/ObjectPrimitive.hpp \
           src/ParallelLight.hpp \
           src/Parallelogram.hpp \
           src/ParallelogramLight.hpp \
           src/PerlinNoise.hpp \
           src/Photon.hpp \
           src/PhotonMap.hpp \
           src/Plane.hpp \
           src/Point.hpp \
           src/Ray.hpp \
           src/Raytracer.hpp \
           src/RaytracerSubThread.hpp \
           src/RaytracerThread.hpp \
           src/RegisterServerThread.hpp \
           src/RenderingConfiguration.hpp \
           src/RenderingInterface.hpp \
           src/Resource.hpp \
           src/Resources.hpp \
           src/Rotation.hpp \
           src/Scene.hpp \
           src/ServerEntry.hpp \
           src/ServersListManager.hpp \
           src/Sett.hpp \
           src/Sphere.hpp \
           src/SphericalLight.hpp \
           src/Spot.hpp \
           src/Texture.hpp \
           src/Torus.hpp \
           src/Triangle.hpp \
           src/Vector.hpp \
           src/equation-solver/EqEntity.hpp \
           src/equation-solver/EqNode.hpp \
           src/equation-solver/EqOperator.hpp \
           src/equation-solver/Equation.hpp \
           src/gui/gui.hpp \
           src/gui/guiEditMaterialDialog.hpp
SOURCES += src/A3DSChunk.cpp \
           src/A3DSLight.cpp \
           src/A3DSMaterial.cpp \
           src/A3DSMesh.cpp \
           src/A3DSParser.cpp \
           src/BoundingBox.cpp \
           src/Camera.cpp \
           src/CheckerBoard.cpp \
           src/CinemaCamera.cpp \
           src/ClusterClient.cpp \
           src/ClusterRenderingThread.cpp \
           src/ClusterServer.cpp \
           src/Color.cpp \
           src/Cone.cpp \
           src/CubeMap.cpp \
           src/CubeTroue.cpp \
           src/Cylinder.cpp \
           src/EquationPrimitive.cpp \
           src/EquationSolver.cpp \
           src/KdTree.cpp \
           src/Light.cpp \
           src/main.cpp \
           src/Material.cpp \
           src/Matrix.cpp \
           src/Object.cpp \
           src/ObjectPrimitive.cpp \
           src/ParallelLight.cpp \
           src/Parallelogram.cpp \
           src/ParallelogramLight.cpp \
           src/PerlinNoise.cpp \
           src/Photon.cpp \
           src/PhotonMap.cpp \
           src/Plane.cpp \
           src/Ray.cpp \
           src/Raytracer.cpp \
           src/RaytracerSubThread.cpp \
           src/RaytracerThread.cpp \
           src/RegisterServerThread.cpp \
           src/RenderingConfiguration.cpp \
           src/RenderingInterface.cpp \
           src/Resource.cpp \
           src/Resources.cpp \
           src/Scene.cpp \
           src/SceneCamera.cpp \
           src/SceneLight.cpp \
           src/SceneMaterial.cpp \
           src/SceneObject.cpp \
           src/ServerEntry.cpp \
           src/ServersListManager.cpp \
           src/Sett.cpp \
           src/Sphere.cpp \
           src/SphericalLight.cpp \
           src/Spot.cpp \
           src/Texture.cpp \
           src/Torus.cpp \
           src/Triangle.cpp \
           src/Vector.cpp \
           src/equation-solver/EqEntity.cpp \
           src/equation-solver/EqNode.cpp \
           src/equation-solver/EqOperator.cpp \
           src/equation-solver/Equation.cpp \
           src/equation-solver/Equation_derivate.cpp \
           src/equation-solver/Equation_develop.cpp \
           src/equation-solver/Equation_factorize.cpp \
           src/gui/gui.cpp \
           src/gui/guiCluster.cpp \
           src/gui/guiEditMaterialDialog.cpp \
           src/gui/guiInterface.cpp \
           src/gui/guiPreferencesDialog.cpp
