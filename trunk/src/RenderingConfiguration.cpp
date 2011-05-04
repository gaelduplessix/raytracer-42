#include "RenderingConfiguration.hpp"

RenderingConfiguration::RenderingConfiguration():
  _width(0), _height(0), _currentCamera(0), _antialiasing(0),
  _exposure(1.0), _directLighting(true), _directLightingCoeff(1),
  _diffuseLighting(true), _specularLighting(true), _cubeMap(NULL),
  _backgroundColor(Color(0, 0, 0)), _ambientOcclusionEnabled(false),
  _ambientOcclusionSampling(0), _photonMappingEnabled(false),
  _photonMappingSampling(0), _diffuseShadingEnabled(false),
  _diffuseShadingSampling(0), _fieldDepthEnabled(false),
  _fieldDepthSampling(0), _additiveAmbiantLighting(-1),
  _minimalAmbiantLighting(-1)
{
  _transparency.enabled = false;
  _reflection.enabled = false;
}

int	RenderingConfiguration::getWidth(void) const
{
  return (_width);
}

int	RenderingConfiguration::getHeight(void) const
{
  return (_height);
}

int	RenderingConfiguration::getCurrentCamera(void) const
{
  return (_currentCamera);
}

int	RenderingConfiguration::getAntialiasing(void) const
{
  return (_antialiasing);
}

double	RenderingConfiguration::getExposure(void) const
{
  return (_exposure);
}


bool	RenderingConfiguration::isDirectLighting(void) const
{
  return (_directLighting);
}

double	RenderingConfiguration::getDirectLightingCoeff(void) const
{
  return (_directLightingCoeff);
}

bool	RenderingConfiguration::isDiffuseLighting(void) const
{
  return (_diffuseLighting);
}

bool	RenderingConfiguration::isSpecularLighting(void) const
{
  return (_specularLighting);
}

bool	RenderingConfiguration::isReflectionEnabled(void) const
{
  return (_reflection.enabled);
}

int	RenderingConfiguration::getReflectionMaxDepth(void) const
{
  return (_reflection.maxDepth);
}

bool	RenderingConfiguration::isReflectionDiffused(void) const
{
  return (_reflection.diffused);
}

int	RenderingConfiguration::getReflectionDiffusedSampling(void) const
{
  return (_reflection.diffusedSampling);
}

bool	RenderingConfiguration::isTransparencyEnabled(void) const
{
  return (_transparency.enabled);
}

int	RenderingConfiguration::getTransparencyMaxDepth(void) const
{
  return (_transparency.maxDepth);
}

bool	RenderingConfiguration::isTransparencyDiffused(void) const
{
  return (_transparency.diffused);
}

int	RenderingConfiguration::getTransparencyDiffusedSampling(void) const
{
  return (_transparency.diffusedSampling);
}

CubeMap*	RenderingConfiguration::getCubeMap(void) const
{
  return (_cubeMap);
}

const Color&	RenderingConfiguration::getBackgroundColor(void) const
{
  return (_backgroundColor);
}

bool	RenderingConfiguration::isAmbientOcclusionEnabled(void) const
{
  return (_ambientOcclusionEnabled);
}

int	RenderingConfiguration::getAmbientOcclusionSampling(void) const
{
  return (_ambientOcclusionSampling);
}

bool	RenderingConfiguration::isPhotonMappingEnabled(void) const
{
  return (_photonMappingEnabled);
}

int	RenderingConfiguration::getPhotonMappingSampling(void) const
{
  return (_photonMappingSampling);
}

bool	RenderingConfiguration::isDiffuseShadingEnabled(void) const
{
  return (_diffuseShadingEnabled);
}

int	RenderingConfiguration::getDiffuseShadingSampling(void) const
{
  return (_diffuseShadingSampling);
}

bool	RenderingConfiguration::isFieldDepthEnabled(void) const
{
  return (_fieldDepthEnabled);
}

int	RenderingConfiguration::getFieldDepthSampling(void) const
{
  return (_fieldDepthSampling);
}

double	RenderingConfiguration::getAdditiveAmbiantLighting(void) const
{
  return (_additiveAmbiantLighting);
}

double	RenderingConfiguration::getMinimalAmbiantLighting(void) const
{
  return (_minimalAmbiantLighting);
}

renderingSamplingMethod	RenderingConfiguration::
getRenderingSamplingMethod(void) const
{
  return (_renderingSamplingMethod);
}

void	RenderingConfiguration::setWidth(int width)
{
  _width = width;
}

void	RenderingConfiguration::setHeight(int width)
{
  _height = width;
}

void	RenderingConfiguration::setCurrentCamera(int id)
{
  _currentCamera = id;
}


void	RenderingConfiguration::setAntialiasing(int antialiasing)
{
  _antialiasing = antialiasing;
}

void	RenderingConfiguration::setExposure(double exposure)
{
  _exposure = exposure;
}

void	RenderingConfiguration::setDirectLighting(bool directLighting)
{
  _directLighting = directLighting;
}

void	RenderingConfiguration::setDirectLightingCoeff(double coeff)
{
  _directLightingCoeff = coeff;
}

void	RenderingConfiguration::setDiffuseLighting(bool value)
{
  _diffuseLighting = value;
}

void	RenderingConfiguration::setSpecularLighting(bool specularLighting)
{
  _specularLighting = specularLighting;
}

void	RenderingConfiguration::setReflection(bool enabled,
					      int maxDepth,
					      bool diffused,
					      int diffusedSampling)
{
  _reflection.enabled = enabled;
  _reflection.maxDepth = maxDepth;
  _reflection.diffused = diffused;
  _reflection.diffusedSampling = diffusedSampling;
}

void	RenderingConfiguration::setReflectionEnabled(bool enabled)
{
  _reflection.enabled = enabled;
}

void	RenderingConfiguration::setReflectionMaxDepth(int maxDepth)
{
  _reflection.maxDepth = maxDepth;
}

void	RenderingConfiguration::setReflectionDiffused(bool diffused)
{
  _reflection.diffused = diffused;
}

void	RenderingConfiguration::
setReflectionDiffusedSampling(int diffusedSampling)
{
  _reflection.diffusedSampling = diffusedSampling;
}

void	RenderingConfiguration::setTransparency(bool enabled,
						int maxDepth,
						bool diffused,
						int diffusedSampling)
{
  _transparency.enabled = enabled;
  _transparency.diffused = diffused;
  _transparency.diffusedSampling = diffusedSampling;
  _transparency.maxDepth = maxDepth;
}

void	RenderingConfiguration::setTransparencyEnabled(bool enabled)
{
  _transparency.enabled = enabled;
}

void	RenderingConfiguration::setTransparencyMaxDepth(int maxDepth)
{
  _transparency.maxDepth = maxDepth;
}

void	RenderingConfiguration::setTransparencyDiffused(bool diffused)
{
  _transparency.diffused = diffused;
}

void	RenderingConfiguration::setCubeMap(CubeMap* map)
{
  _cubeMap = map;
}

void	RenderingConfiguration::setBackgroundColor(const Color& color)
{
  _backgroundColor = color;
}

void	RenderingConfiguration::
setTransparencyDiffusedSampling(int diffusedSampling)
{
  _transparency.diffusedSampling = diffusedSampling;
}

void	RenderingConfiguration::setAmbientOcclusionEnabled(bool enabled)
{
  _ambientOcclusionEnabled = enabled;
}

void	RenderingConfiguration::setAmbientOcclusionSampling(int sampling)
{
  _ambientOcclusionSampling = sampling;
}

void	RenderingConfiguration::setPhotonMappingEnabled(bool enabled)
{
  _photonMappingEnabled = enabled;
}

void	RenderingConfiguration::setPhotonMappingSampling(int sampling)
{
  _photonMappingSampling = sampling;
}

void	RenderingConfiguration::setDiffuseShadingEnabled(bool enabled)
{
  _diffuseShadingEnabled = enabled;
}

void	RenderingConfiguration::setDiffuseShadingSampling(int sampling)
{
  _diffuseShadingSampling = sampling;
}

void	RenderingConfiguration::setFieldDepthEnabled(bool enabled)
{
  _fieldDepthEnabled = enabled;
}

void	RenderingConfiguration::setFieldDepthSampling(int sampling)
{
  _fieldDepthSampling = sampling;
}

void	RenderingConfiguration::setAdditiveAmbiantLighting(double value)
{
  _additiveAmbiantLighting = value;
}

void	RenderingConfiguration::setMinimalAmbiantLighting(double value)
{
  _minimalAmbiantLighting = value;
}

void	RenderingConfiguration::
setRenderingSamplingMethod(renderingSamplingMethod rsm)
{
  _renderingSamplingMethod = rsm;
}
