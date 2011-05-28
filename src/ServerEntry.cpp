//
// ServerEntry.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 26 18:17:38 2011 gael jochaud-du-plessix
// Last update Sat May 28 19:15:42 2011 gael jochaud-du-plessix
//

#include "ServerEntry.hpp"

ServerEntry::ServerEntry():
  _ip(), _port(0), _status(0), _progress(0)
{  
}

ServerEntry::ServerEntry(QString ip, int port, int status, int progress):
  _ip(ip), _port(port), _status(status), _progress(0)
{  
}

QString&	ServerEntry::getIp(void)
{
  return (_ip);
}

void		ServerEntry::setIp(QString& ip)
{
  _ip = ip;
}

int		ServerEntry::getPort(void)
{
  return (_port);
}

void		ServerEntry::setPort(int port)
{
  _port = port;
}

int		ServerEntry::getStatus(void)
{
  return (_status);
}

void		ServerEntry::setStatus(int status)
{
  _status = status;
}

int		ServerEntry::getProgress(void)
{
  return (_progress);
}

void		ServerEntry::setProgress(int progress)
{
  _progress = progress;
}
