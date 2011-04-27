<?php
function array_clean(&$array)
{
  $new = array();
  foreach ($array as $value)
    {
      if (preg_match("#(\w)+#", $value))
	$new[] = $value;
    }
  $array = $new;
}

class CppClass
{
  public $getters = array();
  public $setters = array();
  public $operators = array();
  public $members = array();
  
  public function hasMember($var_name)
  {
    $var_name = '_' . $var_name;
    foreach ($this->members as $member)
      {
	if ($member['name'] == $var_name)
	  return (1);
      }
    return (0);
  }
};

if ($argc < 2)
  return ;
$file = file_get_contents($argv[1]);
$lines = explode("\n", $file);

$class = new CppClass();
$class->getters = array();
$class->setters = array();
$class->operators = array();
$class->members = array();

foreach ($lines as $line)
{
  if (preg_match("#(\s+)?class(\s+)?(\w+)(:((\w+),?)+)?#", $line, $matches))
    {
      array_clean($matches);
      $class->name = $matches[1];
    }
  else if (preg_match("#(\s+)?((const )?\S+)(\s+)(.+);#", $line, $matches))
    {
      array_clean($matches);
      if (count($matches) >= 3)
	{
	  $nameIndex = strpos($matches[2], 'const') === 0 ?
	    3 : 2;
	  if (strpos($matches[$nameIndex], '(') !== false)
	    {
	      if (strpos($matches[$nameIndex], 'get') === 0
		  || strpos($matches[$nameIndex], 'is') === 0
		  || strpos($matches[$nameIndex], 'has') === 0)
		$class->getters[] = array('type' => $matches[1],
					  'name' => $matches[$nameIndex]);
	      else if (strpos($matches[$nameIndex], 'set') === 0)
		$class->setters[] = array('type' => $matches[1],
					  'name' => $matches[$nameIndex]);
	      else if (strpos($matches[$nameIndex], 'operator') === 0)
		$class->operators[] = array('type' => $matches[1],
					    'name' => $matches[$nameIndex]);
	    }
	  else if (strpos($matches[$nameIndex], '_') !== false)
	    $class->members[] = array('type' => $matches[1],
				      'name' => $matches[$nameIndex]);
	}
    }
}

// Génération des getters
foreach ($class->getters as $getter)
{
  if (preg_match("#(get|is|has)(\w+)(.+)#", $getter['name'], $matches))
    {
      array_clean($matches);
      if (count($matches) >= 3)
	{
	  $var_name = lcfirst($matches[2]);
	  if ($class->hasMember($var_name))
	    {
	      echo $getter['type'] . "\t" . $getter['name'] . "\n";
	      echo "{\n";
	      echo "\treturn (_" . $var_name . ");\n";
	      echo "}\n\n";
	    }
	}
    }
}

// Génération des setters
foreach ($class->setters as $setter)
{
  if (preg_match("#(set)(\w+)(.+)#", $setter['name'], $matches))
    {
      array_clean($matches);
      if (count($matches) >= 3)
	{
	  $var_name = lcfirst($matches[2]);
	  preg_match("#\((.+)\)#", $matches[3], $matches);
	  $values = explode(',', $matches[1]);
	  if (count($values) == 1)
	    {
	      $words = preg_split("#\s#", $values[0]);
	      array_clean($words);
	      $value_name = $words[count($words) - 1];
	      if ($class->hasMember($var_name))
		{
		  echo $setter['type'] . "\t" . $setter['name'] . "\n";
		  echo "{\n";
		  echo "\t_" . $var_name . ' = ' . $value_name . ";\n";
		  echo "}\n\n";
	        }
	    }
	  else
	    {
	      echo $setter['type'] . "\t" . $setter['name'] . "\n";
	      echo "{\n";
	      foreach ($values as $value)
		{
		  $words = preg_split("#\s#", $value);
		  array_clean($words);
		  $value_name = $words[count($words) - 1];
		  if ($class->hasMember($value_name))
		    echo "\t_" . $value_name . ' = ' . $value_name . ";\n";
		}
	      echo "}\n\n";
	    }
	}
    }
}