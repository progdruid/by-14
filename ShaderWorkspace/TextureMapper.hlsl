
if (Normal.x != 0 || Normal.z != 0)
{
    float projLenMul = rsqrt(Normal.x * Normal.x + Normal.z * Normal.z); //
    float cosA = -Normal.x * projLenMul;
    float sinA = Normal.z * projLenMul;

    float3x3 matA =
    {
        cosA, 0., -sinA,
        0., 1., 0.,
        sinA, 0., cosA
    };

    WorldPosition = mul(matA, WorldPosition);
    Normal = mul(matA, Normal);
}

float cosB = -Normal.x;
float sinB = Normal.y;
float3x3 matB =
{
    cosB, -sinB, 0.,
    sinB, cosB, 0.,
    0., 0., 1.
};
WorldPosition = mul(matB, WorldPosition);
WorldPosition /= 1000;
WorldPosition *= Scale;

return Texture2DSample(Texture, TextureSampler, WorldPosition.yz);