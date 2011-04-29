/*
** endian.c for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
** 
** Made by gael jochaud-du-plessix
** Login   <jochau_g@epitech.net>
** 
** Started on  Fri Apr 29 10:23:23 2011 gael jochaud-du-plessix
** Last update Fri Apr 29 10:25:26 2011 gael jochaud-du-plessix
*/

/*
 * Renvoie 1 sur une machine en little endian,
 *         0 sur une machine en big endian
 */

int	main()
{
  int	a;
  char	*ptr;

  a = 1;
  ptr = (char *)&a;
  return (*ptr);
}
