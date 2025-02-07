//
// CubeMap.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue May  3 16:30:47 2011 gael jochaud-du-plessix
// Last update Fri May 27 14:25:33 2011 samuel olivier
//

#ifndef _CUBEMAP_HPP_
#define _CUBEMAP_HPP_

#include <string>
#include <vector>
#include <QImage>

#include "Color.hpp"
#include "Point.hpp"

using namespace std;

class CubeMap
{
public:
  static const int Top	  = 0;
  static const int Left   = 1;
  static const int Front  = 2;
  static const int Right  = 3;
  static const int Bottom = 4;
  static const int Rear   = 5;

  static const int ERROR_INVALID_FILE = 0;

  CubeMap(const string& path);
  ~CubeMap();

  Color getMapColor(Vector viewVector);

  const string& getName(void);
  void  setName(const string& name);
  
protected:
  Color	_readFace(int face, double x, double y);

private:
  double		_facesWidth;
  vector<QImage*>	_facesFiles;
  vector<string>	_faceFileContent;
  string		_name;
};


#endif
