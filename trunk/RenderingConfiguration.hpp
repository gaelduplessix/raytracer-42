//
// RenderingConfiguration.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 13:51:17 2011 loick michard
// Last update Tue Apr 26 15:49:27 2011 loick michard
//

#ifndef _RENDERINGCONFIGURATION_HPP_
#define _RENDERINGCONFIGURATION_HPP_

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
  bool          diffused;
  int		diffusedSampling;
}               t_transparency;

class RenderingConfiguration
{
public:
  RenderingConfiguration();
  ~RenderingConfiguration();
  
  int		getAntialiasing() const;
  void		setAntialiasing(int antialiasing);
  bool		isDirectLighting() const;
  void		setDirectLighting(bool antialiasing);

  bool		isReflectionEnabled() const;
  int		getReflectionMaxDepth() const;
  bool		isReflectionDiffused() const;
  int		getReflectionDiffusedSampling() const;
  void		setReflection(bool enabled, int maxDepth = 20,
			      bool diffused = 0, int diffusedSampling = 0);
  void		setReflectionEnabled(bool enabled = 1);
  void		setReflectionMaxDepth(int maxDepth);
  void		setReflectionDiffused(bool diffused = 1);
  void		setReflectionDiffusedSampling(int diffusedSampling);

  bool		isTransparencyEnabled() const;
  bool		isTransparencyDiffused() const;
  int		getTransparencyDiffusedSampling() const;
  void		setTransparency(bool enabled,
				bool diffused = 0, int diffusedSampling = 0);
  void		setTransparencyEnabled(bool enabled = 1);
  void          setTransparencyDiffused(bool diffused = 1);
  void          setTransparencyDiffusedSampling(int diffusedSampling);

  bool		isAmbientOcclusionEnabled() const;
  int		getAmbientOcclusionSampling() const;
  void		setAmbientOcclusionEnabled(bool enabled = 1);
  void		setAmbientOcclusionSampling(int sampling);

  bool		isPhotonMappingEnabled() const;
  int		getPhotonMappingSampling() const;
  void		setPhotonMappingEnabled(bool enabled= 1);
  void		setPhotonMappingSampling(int sampling);

  bool		isDiffuseLightingEnabled() const;
  int		getDiffuseLightingSampling() const;
  void		setDiffuseLightingEnabled(bool enabled= 1);
  void		setDiffuseLightingSampling(int sampling);

  bool		isFieldDepthEnabled() const;
  int		getFieldDepthSampling() const;
  void		setFieldDepthEnabled(bool enabled= 1);
  void		setFieldDepthSampling(int sampling);

  renderingSamplingMethod getRenderingSamplingMethod() const;
  void setRenderingSamplingMethod(renderingSamplingMethod rsm);

  int	getWidth() const;
  void	setWidth(int width);
  int   getHeight() const;
  void	setHeight(int width);

private:
  int			_width;
  int			_height;
  int			_antialiasing;
  bool			_directLighting;
  t_reflection		_reflection;
  t_transparency	_transparency;
  bool			_ambientOcclusionEnabled;
  int			_ambientOcclusionSampling;
  bool                  _photonMappingEnabled;
  int                   _photonMappingSampling;
  bool                  _diffuseLightingEnabled;
  int                   _diffuseLightingSampling;
  bool                  _fieldDepthEnabled;
  int                   _fieldDepthSampling;
  renderingSamplingMethod _renderingSamplingMethod;
};

#endif
