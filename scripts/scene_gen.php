<scene>
  <cameras>
    <camera type="cinema" name="Camera">
      <position>0, 0, 0</position>
      <rotation type="radian">0, 0, 0</rotation>
    </camera>
  </cameras>

  <materials>
    <material name="sol0">
      <color>255, 255, 255</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
    <material name="sol1">
      <color>255, 0, 0</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
    <material name="sol2">
   <color>0, 255, 0</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
    <material name="sol3">
   <color>0, 0, 255</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
  </materials>
  <objects>
    <object>
      <position>0, 0, 0</position>
      <rotation type="radian">0, 0, 0</rotation>
      <solid>true</solid>
	<primitives>
   <?php define('NB_TRIANGLES', 5000); ?>
   <?php for ($i = 1; $i <= NB_TRIANGLES; $i++): ?>
	  <primitive type="triangle" material="sol<?= rand(0, 3) ?>">
	     <?php $x = rand(5, 30); ?>
	     <?php $y = rand(-10, 10); ?>
	     <?php $z = rand(-10, 10); ?>
	     <position><?= $x ?>, <?= $y ?>, <?= $z ?></position>
	    <vertex1><?= $x+0.05 ?>, <?= $y+0.05 ?>, <?= $z+0.05 ?></vertex1>
	    <vertex2><?= $x ?>, <?= $y+0.05 ?>, <?= $z ?></vertex2>
	    <rotation type="radian">0, 0, 0</rotation>
	     </primitive>
	     <?php endfor; ?>
	</primitives>
    </object>
  </objects>

  <lights>
    <light type="spot">
      <position>0,0,5</position>
      <color>FF0000</color>
      <intensity>1</intensity>
      <directLight>1</directLight>
    </light>
    <light type="spot">
      <position>0,0,-5</position>
      <color>00FF00</color>
      <intensity>1</intensity>
      <directLight>1</directLight>
    </light>
  </lights>
  </scene>

