
#define PI 3.1415926538

float centerDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV, 1), 1, false).r;
float depthScaler = rsqrt(DefaultDepth / centerDepth);
float2 scaledEdgeOffset = EdgeUVOffset / depthScaler;
if (scaledEdgeOffset.x < MinUVOffset)
    scaledEdgeOffset.x = MinUVOffset;
if (scaledEdgeOffset.y < MinUVOffset)
    scaledEdgeOffset.y = MinUVOffset;
float scaledDepthThreshold = DepthThreshold * depthScaler;

double curv = 0;
float angleStep = PI / NumberEdgeChecks;
for (int i = 0; i < NumberEdgeChecks; i++)
{
    float2 offsetVec = float2(cos(angleStep * i) * scaledEdgeOffset.x, sin(angleStep * i) * scaledEdgeOffset.y);

    float firstDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV + offsetVec, 1), 1, false).r;
    float secondDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV - offsetVec, 1), 1, false).r;
    bool depthDetected = abs(firstDepth + secondDepth - centerDepth * 2) > scaledDepthThreshold * 2;

    float3 firstNormal = SceneTextureLookup(ViewportUVToSceneTextureUV(UV + offsetVec, 8), 8, false);
    float3 secondNormal = SceneTextureLookup(ViewportUVToSceneTextureUV(UV - offsetVec, 8), 8, false);
    bool normalDetected = dot(firstNormal, secondNormal) < (1. - NormalThreshold);
    
    float3 firstColor = SceneTextureLookup(ViewportUVToSceneTextureUV(UV + offsetVec, 2), 2, false);
    float3 secondColor = SceneTextureLookup(ViewportUVToSceneTextureUV(UV - offsetVec, 2), 2, false);
    float3 diffColor = abs(firstColor - secondColor);
    bool colorDetected = diffColor.r + diffColor.g + diffColor.b > ColorThreshold;
    
    if (depthDetected || normalDetected || colorDetected)
        return 1;
    
}
return 0;

#undef PI