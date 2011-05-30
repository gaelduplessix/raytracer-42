#!/usr/local/bin/php
<?php
  // gen_scene.php for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
  // 
  // Made by samuel olivier
  // Login   <olivie_a@epitech.net>
  // 
  // Started on  Sun May 29 16:57:02 2011 samuel olivier
// Last update Mon May 30 14:34:45 2011 samuel olivier
  //

define('CUBE_SIZE', 1);
define('FIRST_CUBE_DEPTH', 3.5);
define('PLANE_HEIGHT', -6);
define('MIN', 0.2);
define('MIDDLE', 0.6);
define('MAX', 1);
define('MIN_RAY', 0.3);
define('MIDDLE_RAY', 0.4);
define('MAX_RAY', 0.5);
define('LIGHT_WIDTH', CUBE_SIZE * 4);
define('LIGHT_HEIGHT', PLANE_HEIGHT + 7);

?>
<scene>
<cameras>
<camera type="cinema" name="main">
  <position>-0.105, 0, 2</position>
  <rotation type="radian">0, 0.875, 0</rotation>
  <focus><?=FIRST_CUBE_DEPTH + CUBE_SIZE * 3.5?></focus>
  </camera>
  </cameras>
  
  <materials>
  <material name="floor">
  <color>100, 100, 100</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  </material>
  <material name="cubesFaceTop">
  <color>150, 150, 150</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  </material>
  <material name="redLeftRight">
  <color>150, 50, 50</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  <diffusedReflection>0.5</diffusedReflection>
  </material>  
  <material name="redMiddle">
  <color>150, 50, 50</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  </material>  
  <material name="greenLeftRight">
  <color>50, 150, 50</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  <diffusedReflection>0.5</diffusedReflection>
  </material>
  <material name="greenMiddle">
  <color>50, 150, 50</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  </material>
  <material name="whiteLeftRight">
  <color>200, 200, 200</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  <diffusedReflection>0.5</diffusedReflection>
  </material>
  <material name="whiteMiddle">
  <color>200, 200, 200</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  </material>
  <material name="blueLeftRight">
  <color>50, 50, 150</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  <diffusedReflection>0.5</diffusedReflection>
  </material>
  <material name="blueMiddle">
  <color>50, 50, 150</color>
  <specular>0.5</specular>
  <specularPow>50</specularPow>
  <reflection>0.5</reflection>
  </material>
  </materials>
  
  <objects>
  <object>
  <position>0, 0, 0</position>
  <rotation type="radian">0, 0, 0</rotation>
  <solid>false</solid>
  <primitives>
  <primitive type="plane" material="floor">
  <position>0, 0, <?=PLANE_HEIGHT?></position>
  <rotation type="radian">0, 0, 0</rotation>
  </primitive>
  </primitives>
  </object>
  <?php
for ($i = 0 ; $i < 5 ; $i++)
  {
    for ($j = 0 ; $j < 4 ; $j++)
      {
?>
<parallelepipede material="cubesFaceTop">
<position><?=$j * (CUBE_SIZE + CUBE_SIZE / 2) + FIRST_CUBE_DEPTH?>, <?=($i - 2) * (CUBE_SIZE + CUBE_SIZE / 2) - CUBE_SIZE / 2?>, <?=PLANE_HEIGHT?></position>
<width>0, <?=CUBE_SIZE?>, 0</width>
<depth><?=CUBE_SIZE?>, 0, 0</depth>
<height>0, 0, <?=($i == 0 || $i == 4) ? MIN : (($i == 1 || $i == 3) ? MIDDLE : MAX) ?></height>
<solid>true</solid>
<rotation type="radian">0, 0, 0</rotation>
</parallelepipede>
<?php
      }
  }
?>
<object>
<position>0, 0, 0</position>
  <rotation type="radian">0, 0, 0</rotation>
  <solid>false</solid>
  <primitives>
<?php

for ($i = 0 ; $i < 5 ; $i++)
  {
    for ($j = 0 ; $j < 4 ; $j++)
      {
	$material = ($i == 2) ? 'Middle' : 'LeftRight';
	if ($j == 0)
	  $material = 'blue' . $material;
	else if ($j == 1)
	  $material = 'white' . $material;
	else if ($j == 2)
	  $material = 'green' . $material;
	else
	  $material = 'red' . $material;
?>

	<primitive type="sphere" material="<?=$material?>">
<?php
	if ($i == 0 || $i == 4)
	  $z = PLANE_HEIGHT + MIN + MIN_RAY;
	else if ($i == 1 || $i == 3)
	  $z = PLANE_HEIGHT + MIDDLE + MIDDLE_RAY;
	else
	  $z = PLANE_HEIGHT + MAX + MAX_RAY;	  
	?>
	<position><?=FIRST_CUBE_DEPTH + $j * (CUBE_SIZE * 1.5) + CUBE_SIZE / 2?>, <?=($i - 2) * (CUBE_SIZE + CUBE_SIZE / 2)?>, <?=$z?></position>
	<rotation type="radian">0, 0, 0</rotation>
<?php
	if ($i == 0 || $i == 4)
	  $ray = MIN_RAY;
	else if ($i == 1 || $i == 3)
	  $ray = MIDDLE_RAY;
	else
	  $ray = MAX_RAY;
?>
	<radius><?=$ray?></radius>
	</primitive>
<?php
      }
  }
?>
</primitives>
</object>
</objects>
<lights>
<?php
for ($i = 0 ; $i < 4 ; $i++)
  {
    ?>
    
    <light type="parallelogram">
      <point><?=FIRST_CUBE_DEPTH + $i * (CUBE_SIZE * 1.5)?>, <?=-LIGHT_WIDTH / 2?>, <?=LIGHT_HEIGHT?></point>
      <vector1>0, <?=LIGHT_WIDTH?>, 0</vector1>
      <vector2><?=CUBE_SIZE?>, 0, 0</vector2>
      <directLight>3000</directLight>
      <intensity>0.8</intensity>
<?php
      if ($i == 0)
	$color = '50, 50, 200';
      else if ($i == 1)
	$color = '50, 200, 50';
      else if ($i == 2)
	$color = '50, 200, 50';
      else
	$color = '200, 50, 50';
    ?>
      <color><?=$color?></color>
    </light>
<?php
  }
?>
</lights>
</scene>
