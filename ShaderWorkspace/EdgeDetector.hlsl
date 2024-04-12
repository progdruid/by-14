
#define PI 3.1415926538

float centerDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV, 1), 1, false).r;
float2 scaledEdgeOffset = EdgeUVOffset * (DefaultDepth / centerDepth);
if (scaledEdgeOffset.x < MinUVOffset)
    scaledEdgeOffset.x = MinUVOffset;
if (scaledEdgeOffset.y < MinUVOffset)
    scaledEdgeOffset.y = MinUVOffset;

float angleStep = PI / NumberEdgeChecks;
for (int i = 0; i < NumberEdgeChecks; i++)
{
    float2 offsetVec = float2(cos(angleStep * i) * scaledEdgeOffset.x, sin(angleStep * i) * scaledEdgeOffset.y);

    float firstDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV + offsetVec, 1), 1, false).r;
    float secondDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV - offsetVec, 1), 1, false).r;
    bool depthDetected = abs(firstDepth + secondDepth - centerDepth * 2) > DepthThreshold * 2;

    float3 firstNormal = SceneTextureLookup(ViewportUVToSceneTextureUV(UV + offsetVec, 8), 8, false);
    float3 secondNormal = SceneTextureLookup(ViewportUVToSceneTextureUV(UV - offsetVec, 8), 8, false);
    bool normalDetected = dot(firstNormal, secondNormal) < (1. - NormalThreshold);
    
    if (depthDetected || normalDetected)
        return 1;
    
}
return 0;

#undef PI