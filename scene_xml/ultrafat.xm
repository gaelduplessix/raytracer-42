<scene>
  <cameras>
    <camera type="cinema" name="main">
      <position>0, 0, 0</position>
      <rotation type="radian">0, 0, 0</rotation>
      <focus>30</focus>
    </camera>
  </cameras>
  
  <materials>
    <material name="materialPlane2">
      <color>255,255,255</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
    <material name="materialPlane1">
      <color>255,255,255</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>1</reflection>
    </material>
    <material name="materialSphere1">
      <color>140,110,55</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>1</reflection>
      <diffusedReflection>1</diffusedReflection>
    </material>
    <material name="materialSphere2">
      <color>150,120,155</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
    <material name="materialSphere3">
      <color>100,200,180</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
    <material name="materialCylinder">
      <color>60,100,220</color>
      <specular>0.5</specular>
      <specularPow>50</specularPow>
      <reflection>0</reflection>
    </material>
  </materials>
  
  <objects>
    <object>
      <position>0, 0, 0</position>
      <rotation type="radian">0, 0, 0</rotation>
      <solid>false</solid>
      <primitives>
	</primitive>
	<primitive type="plane" material="materialPlane2">
	  <position>0, 0, -2</position>
	  <rotation type="degree">0, 0, 0</rotation>
	</primitive>
	<primitive type="plane" material="materialPlane2">
	  <position>0, 0, 2</position>
	  <rotation type="degree">0, 0, 0</rotation>
	</primitive>
	<primitive type="plane" material="materialPlane2">
	  <position>0, 7, -2</position>
	  <rotation type="degree">90, 0, -20</rotation>
	</primitive>
	<primitive type="plane" material="materialPlane2">
	  <position>0, -7, -2</position>
	  <rotation type="degree">90, 0, -20</rotation>
	</primitive>
	<primitive type="plane" material="materialPlane2">
	  <position>40,0,-2</position>
	  <rotation type="degree">0, 90, 0</rotation>
	</primitive>
	<primitive type="plane" material="materialPlane1">
	  <position>-70,0,-2</position>
	  <rotation type="degree">0, 90, 0</rotation>
	</primitive>
      </primitives>
    </object>
  </objects>

  <lights>
    <light type="parallelogram">
      <point>6,2,3</point>
      <point2>6,0,3</point2>
      <point3>6,0,1</point3>
      <color>100,180,110</color>
      <intensity>3</intensity>
      <directLight>3000</directLight>
    </light>
    <light type="parallelogram">
      <point>27,-4,1</point>
      <point2>27,-2,1</point2>
      <point3>27,-2,-1</point3>
      <color>160,80,140</color>
      <intensity>2</intensity>
      <directLight>3000</directLight>
    </light>
    <light type="parallelogram">
      <point>11,-6,1</point>
      <point2>13,-4,1</point2>
      <point3>13,-4,-1</point3>
      <color>100,180,40</color>
      <intensity>2</intensity>
      <directLight>3000</directLight>
    </light>
    <light type="spot">
      <position>35,0,-1.7</position>
      <color>200,150,140</color>
      <intensity>1</intensity>
      <directLight>3000</directLight>
    </light>
  </lights>
</scene>