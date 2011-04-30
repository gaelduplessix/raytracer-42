#include "RenderingConfiguration.hpp"

RenderingConfiguration::RenderingConfiguration():
  _width(0), _height(0), _currentCamera(0), _antialiasing(0),
  _directLighting(true), _specularLighting(true),
  _ambientOcclusionEnabled(false),
  _ambientOcclusionSampling(0), _photonMappingEnabled(false),
  _photonMappingSampling(0), _diffuseLightingEnabled(false),
  _diffuseLightingSampling(0), _fieldDepthEnabled(false),
  _fieldDepthSampling(0)
{

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

bool	RenderingConfiguration::isDirectLighting(void) const
{
  return (_directLighting);
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

bool	RenderingConfiguration::isTransparencyDiffused(void) const
{
  return (_transparency.diffused);
}

int	RenderingConfiguration::getTransparencyDiffusedSampling(void) const
{
  return (_transparency.diffusedSampling);
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

bool	RenderingConfiguration::isDiffuseLightingEnabled(void) const
{
  return (_diffuseLightingEnabled);
}

int	RenderingConfiguration::getDiffuseLightingSampling(void) const
{
  return (_diffuseLightingSampling);
}

bool	RenderingConfiguration::isFieldDepthEnabled(void) const
{
  return (_fieldDepthEnabled);
}

int	RenderingConfiguration::getFieldDepthSampling(void) const
{
  return (_fieldDepthSampling);
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

void	RenderingConfiguration::setDirectLighting(bool directLighting)
{
  _directLighting = directLighting;
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
			      bool diffused, int diffusedSampling)
{
  _transparency.enabled = enabled;
  _transparency.diffused = diffused;
  _transparency.diffusedSampling = diffusedSampling;
}

void	RenderingConfiguration::setTransparencyEnabled(bool enabled)
{
  _transparency.enabled = enabled;
}

void	RenderingConfiguration::setTransparencyDiffused(bool diffused)
{
  _transparency.diffused = diffused;
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

void	RenderingConfiguration::setDiffuseLightingEnabled(bool enabled)
{
  _diffuseLightingEnabled = enabled;
}

void	RenderingConfiguration::setDiffuseLightingSampling(int sampling)
{
  _diffuseLightingSampling = sampling;
}

void	RenderingConfiguration::setFieldDepthEnabled(bool enabled)
{
  _fieldDepthEnabled = enabled;
}

void	RenderingConfiguration::setFieldDepthSampling(int sampling)
{
  _fieldDepthSampling = sampling;
}

void	RenderingConfiguration::
setRenderingSamplingMethod(renderingSamplingMethod rsm)
{
  _renderingSamplingMethod = rsm;
}
