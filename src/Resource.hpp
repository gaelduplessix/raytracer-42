//
// Resource.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Fri May 27 14:53:17 2011 samuel olivier
// Last update Mon May 30 19:29:49 2011 gael jochaud-du-plessix
//

#ifndef _RESSOURCE_
#define _RESSOURCE_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <string>

using namespace std;

class Resource
{
public:
  Resource(const string& pathName,
	    const string& fileContent,
	    const string& newPathName = "");
  Resource(const string& pathName,
	    const string& newPathName = "");
  Resource(void);
  ~Resource();

  void		setPathName(const string& pathName);
  const string&	getPathName(void);

  void		setNewPathName(const string& newPathName);
  const string&	getNewPathName(void);

  void		setFileContent(const string& fileContent);
  const string&	getFileContent(void);

  friend class	boost::serialization::access;
  template	<class Archive>
  void		serialize(Archive& ar, unsigned int version);

private:
  string	_pathName;
  string	_fileContent;
  string	_newPathName;
};

template	<class Archive>
void		Resource::serialize(Archive& ar, unsigned int version)
{
  version = version;
  ar & _pathName & _fileContent & _newPathName;
}

#endif
