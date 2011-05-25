//
// RenderingConfiguration.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 13:51:17 2011 loick michard
// Last update Wed May 25 10:41:34 2011 samuel olivier
//

#ifndef _RENDERINGCONFIGURATION_HPP_
#define _RENDERINGCONFIGURATION_HPP_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "CubeMap.hpp"

enum	renderingSamplingMethod{
  RSM_LINEAR_HORIZONTAL,
  RSM_LINEAR_VERTICAL,
  RSM_UNPIXELISING,
  RSM_RANDOM_HORIZONTAL,
  RSM_RANDOM_VERTICAL,
  RSM_RANDOM_PIXEL
};

typedef struct	s_reflection
{
  bool		enabled;
  int		maxDepth;
  bool		diffused;
  int		diffusedSampling;
}		t_reflection;

typedef struct	s_transparency
{
  bool		enabled;
  int		maxDepth;
}               t_transparency;

class RenderingConfiguration
{
public:
  RenderingConfiguration();

  int		getNbThreads(void) const;
  void		setNbThreads(int nbThreads);
  int		getWidth(void) const;
  void		setWidth(int width);
  int		getHeight(void) const;
  void		setHeight(int width);

  int		getCurrentCamera(void) const;
  void		setCurrentCamera(int id);

  int		getAntialiasing(void) const;
  void		setAntialiasing(int antialiasing);  
  double	getExposure(void) const;
  void		setExposure(double exposure);
  bool		isDirectLighting(void) const;
  void		setDirectLighting(bool value);
  void		setDirectLightingCoeff(double coef);
  double	getDirectLightingCoeff(void) const;
  bool		isSpecularLighting(void) const;
  void		setSpecularLighting(bool value);
  bool		isDiffuseLighting(void) const;
  void		setDiffuseLighting(bool value);

  bool		isReflectionEnabled(void) const;
  int		getReflectionMaxDepth(void) const;
  bool		isReflectionDiffused(void) const;
  int		getReflectionDiffusedSampling(void) const;
  void		setReflection(bool enabled, int maxDepth = 20,
			      bool diffused = false,
			      int diffusedSampling = 0);
  void		setReflectionEnabled(bool enabled = 1);
  void		setReflectionMaxDepth(int maxDepth);
  void		setReflectionDiffused(bool diffused = 1);
  void		setReflectionDiffusedSampling(int diffusedSampling);

  bool		isTransparencyEnabled(void) const;
  int		getTransparencyMaxDepth(void) const;
  void		setTransparency(bool enabled, int maxDepth = 20);
  void		setTransparencyEnabled(bool enabled = 1);
  void		setTransparencyMaxDepth(int maxDepth);

  const Color&	getBackgroundColor(void) const;
  void		setBackgroundColor(const Color& color);

  CubeMap*	getCubeMap(void) const;
  void		setCubeMap(CubeMap *map);

  bool		isAmbientOcclusionEnabled(void) const;
  int		getAmbientOcclusionSampling(void) const;
  void		setAmbientOcclusionEnabled(bool enabled = 1);
  void		setAmbientOcclusionSampling(int sampling);

  bool		isPhotonMappingEnabled(void) const;
  int		getPhotonMappingSampling(void) const;
  void		setPhotonMappingEnabled(bool enabled= 1);
  void		setPhotonMappingSampling(int sampling);
  
  bool		isDiffuseShadingEnabled(void) const;
  int		getDiffuseShadingSampling(void) const;
  void		setDiffuseShadingEnabled(bool enabled= 1);
  void		setDiffuseShadingSampling(int sampling);

  bool		isFieldDepthEnabled(void) const;
  int		getFieldDepthSampling(void) const;
  void		setFieldDepthEnabled(bool enabled= 1);
  void		setFieldDepthSampling(int sampling);

  const Color&	getAdditiveAmbiantLighting(void) const;
  double	getMinimalAmbiantLighting(void) const;
  void		setAdditiveAmbiantLighting(const Color& value);
  void		setMinimalAmbiantLighting(double value);
  bool		isMinimalAmbiantLighting(void) const;
  bool		isAdditiveAmbiantLighting(void) const;
  void		setAdditiveAmbiantLightingEnabled(bool value = true);
  void		setMinimalAmbiantLightingEnabled(bool value = true);


  renderingSamplingMethod getRenderingSamplingMethod(void) const;
  void setRenderingSamplingMethod(renderingSamplingMethod rsm);

  bool		isKdTreeEnabled() const;
  void		setKdTreeEnabled(bool enabled = true);
  int		getKdTreeDepth() const;
  void		setKdTreeDepth(int depth);

  friend class		boost::serialization::access;
  template<class Archive>
  void			serialize(Archive& ar, unsigned int version);

private:
  int			_nbThreads;
  int			_width;
  int			_height;
  int			_currentCamera;
  int			_antialiasing;
  renderingSamplingMethod _renderingSamplingMethod;
  double		_exposure;
  bool			_directLighting;
  double		_directLightingCoeff;
  bool			_diffuseLighting;
  bool			_specularLighting;
  t_reflection		_reflection;
  t_transparency	_transparency;
  CubeMap*		_cubeMap;
  Color			_backgroundColor;
  bool			_ambientOcclusionEnabled;
  int			_ambientOcclusionSampling;
  bool                  _photonMappingEnabled;
  int                   _photonMappingSampling;
  bool                  _diffuseShadingEnabled;
  int                   _diffuseShadingSampling;
  bool                  _fieldDepthEnabled;
  int                   _fieldDepthSampling;
  bool			_additiveAmbiantLightingEnabled;
  Color			_additiveAmbiantLighting;
  bool			_minimalAmbiantLightingEnabled;
  double		_minimalAmbiantLighting;
  bool			_kdTreeEnabled;
  int			_kdTreeDepth;
};

template<class Archive>
void			RenderingConfiguration::serialize(Archive& ar,
							  unsigned int version)
  {
    version = version;
    ar & _nbThreads;
    ar & _width;
    ar & _height;
    ar & _currentCamera;
    ar & _antialiasing;
    ar & _renderingSamplingMethod;
    ar & _exposure;
    ar & _directLighting;
    ar & _directLightingCoeff;
    ar & _diffuseLighting;
    ar & _specularLighting;
    // ar & _reflection;
    // ar & _transparency;
    // ar & _backgroundColor;
    ar & _ambientOcclusionEnabled;
    ar & _ambientOcclusionSampling;
    ar & _photonMappingEnabled;
    ar & _photonMappingSampling;
    ar & _diffuseShadingEnabled;
    ar & _diffuseShadingSampling;
    ar & _fieldDepthEnabled;
    ar & _fieldDepthSampling;
    ar & _additiveAmbiantLightingEnabled;
    // ar & _additiveAmbiantLighting;
    ar & _minimalAmbiantLightingEnabled;
    ar & _minimalAmbiantLighting;
    ar & _kdTreeEnabled;
    ar & _kdTreeDepth;
  }

#endif
