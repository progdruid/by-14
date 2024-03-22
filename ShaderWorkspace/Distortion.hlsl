#define PI 3.1415926538

float factor = WorldPosition.y + WorldPosition.z;
float addAmount = 0;
addAmount += cos(factor/Period)*Distortion;
addAmount += cos(factor*2/Period)*Distortion;
addAmount += cos(factor*4/Period)*Distortion;
addAmount/=3;

float2 worldAdd = float2(addAmount, addAmount);
return worldAdd - CameraDirection * dot(worldAdd,CameraDirection);

#undef PI