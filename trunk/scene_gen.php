<scene>
  <cameras>
    <camera type="cinema">
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
   <?php define('NB_TRIANGLES', 120); ?>
   <?php for ($i = 1; $i <= NB_TRIANGLES; $i++): ?>
	  <primitive type="triangle" material="sol<?= rand(0, 3) ?>">
	     <position><?= rand(15, 30) ?>, <?= rand(-10, 10) ?>, <?= rand(-10, 10) ?></position>
	    <vertex1><?= rand(15, 30) ?>, <?= rand(-10, 10) ?>, <?= rand(-10, 10) ?></vertex1>
	    <vertex2><?= rand(15, 30) ?>, <?= rand(-10, 10) ?>, <?= rand(-10, 10) ?></vertex2>
	    <rotation>0, 0, 0</rotation>
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

