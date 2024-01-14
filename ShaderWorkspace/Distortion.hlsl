#define PI 3.1415926538

float2 adduv = float2(0, 0);
float factor = WorldPosition.y + WorldPosition.z;
adduv.x += cos(factor/Period)*Distortion;
adduv.x += cos(factor*2/Period)*Distortion;
adduv.x += cos(factor*4/Period)*Distortion;
adduv.y += cos(factor/Period)*Distortion;
adduv.y += cos(factor*2/Period)*Distortion;
adduv.y += cos(factor*4/Period)*Distortion;
adduv/=3;

return UV + adduv;

#undef PI