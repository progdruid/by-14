//float3 WorldPosition;

float factor = WorldPosition.y + WorldPosition.z;
float addAmount = 0;
addAmount += cos(factor/Period);
addAmount += cos(factor*2/Period);
addAmount += cos(factor*4/Period);
addAmount *= Distortion / 3;

float3 worldOffset = { addAmount, addAmount, 0 };
return worldOffset;