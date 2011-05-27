//
// Ressource.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Fri May 27 14:53:17 2011 samuel olivier
// Last update Fri May 27 15:32:35 2011 samuel olivier
//

#ifndef _RESSOURCE_
#define _RESSOURCE_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <string>

using namespace std;

class Ressource
{
public:
  Ressource(const string& pathName,
	    const string& fileContent,
	    const string& newPathName = "");
  Ressource(const string& pathName,
	    const string& newPathName = "");
  Ressource(void);
  ~Ressource();

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
void		Ressource::serialize(Archive& ar, unsigned int version)
{
  version = version;
  ar & _pathName & _fileContent & _newPathName;
}

#endif
