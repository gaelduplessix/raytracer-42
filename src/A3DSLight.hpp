//
// A3DSLight.hpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Sun May 22 15:53:04 2011 melvin laplanche
// Last update Sun May 29 16:27:19 2011 melvin laplanche
//

#ifndef A3DSLIGHT_H_
# define A3DSLIGHT_H_
# include <fstream>
# include <iostream>
# include "A3DSChunk.hpp"
# include "Vector.hpp"

class A3DSLight
{
public:
			A3DSLight(std::string, A3DSChunk);
  const Vector&		getPosition(void);
  const Vector&		getTarget(void);
  const std::string&	getName(void);
  bool			isSpot(void);

private:
  std::string	_name;
  Vector	_position;
  Vector	_target;
  bool		_isSpot;
};
#endif /* !A3DSLIGHT_H_ */
