//
// guiPreferencesDialog.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon May 30 17:06:44 2011 loick michard
// Last update Mon May 30 18:54:09 2011 loick michard
//

#include "gui.hpp"

void    RaytracerGUI::updateEditConfig()
{
  if (_preferencesDialogUi->_cubeMap->isChecked())
    _editMaterialDialog._config->
      setCubeMap(new CubeMap(":cubemap/cubemaps/Maskonaive3"),
		 ":cubemap/cubemaps/Maskonaive3");
  else
    _editMaterialDialog._config->setCubeMap(NULL, "");
  _editMaterialDialog._config->setAntialiasing(_preferencesDialogUi->
					       _antialiasing->value());
}

void	RaytracerGUI::_initPreferencesDialog()
{
  _preferencesDialog = new QDialog();
  _preferencesDialogUi = new Ui::Preferences();
  _aboutDialog = new QDialog();
  _aboutDialogUi = new Ui::About();
  
  _preferencesDialogUi->setupUi(_preferencesDialog);
  _aboutDialogUi->setupUi(_aboutDialog);
  QObject::connect(_ui->actionPreferences, SIGNAL(triggered()),
                   _preferencesDialog, SLOT(show()));
  QObject::connect(_preferencesDialogUi->_antialiasing,
		   SIGNAL(valueChanged(int)),
                   this,
		   SLOT(updateEditConfig()));
  QObject::connect(_preferencesDialogUi->_cubeMap,
                   SIGNAL(stateChanged(int)),
                   this,
                   SLOT(updateEditConfig()));
  QObject::connect(_ui->actionAboutQt, SIGNAL(triggered()),
		   qApp, SLOT(aboutQt()));
  QObject::connect(_ui->actionAbout, SIGNAL(triggered()),
                   _aboutDialog, SLOT(show()));
}
