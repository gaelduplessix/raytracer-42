//
// ServerEntry.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 26 18:14:23 2011 gael jochaud-du-plessix
// Last update Sat May 28 21:45:00 2011 gael jochaud-du-plessix
//

#ifndef _SERVERENTRY_HPP_
#define _SERVERENTRY_HPP_

#include <QString>

class ServerEntry
{
public:
  static const int      FREE = 0;
  static const int      DOWNLOADING_RESSOURCES = 1;
  static const int      PROCESSING_RESSOURCES = 2;
  static const int      RAYTRACING = 3;
  static const int      SENDING_RESPONSE = 4;

  ServerEntry();
  ServerEntry(QString ip, int port, int status=0, int progress=0);

  QString&	getIp(void);
  void		setIp(QString& ip);
  int		getPort(void);
  void		setPort(int port);
  int		getStatus(void);
  void		setStatus(int status);
  int		getProgress(void);
  void		setProgress(int progress);

private:
  QString	_ip;
  int		_port;
  int		_status;
  int		_progress;
};

#endif
