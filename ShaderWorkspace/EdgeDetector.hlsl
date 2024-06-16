
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
    float2 firstVec = UV - offsetVec;
    //firstVec.x = clamp(firstVec.x, 0.f, 1.f);
    //firstVec.y = clamp(firstVec.y, 0.f, 1.f);
    float2 secondVec = UV + offsetVec;
    //secondVec.y = clamp(secondVec.x, 0.f, 1.f);
    //secondVec.y = clamp(secondVec.y, 0.f, 1.f);
    if ((firstVec.x < 0 || secondVec.x < 0 || firstVec.x > 1 || secondVec.x > 1)
        || (firstVec.y < 0 || secondVec.y < 0 || firstVec.y > 1 || secondVec.y > 1))    
        continue;

    float firstDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(firstVec, 1), 1, false).r;
    float secondDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(secondVec, 1), 1, false).r;
    bool depthDetected = abs(firstDepth + secondDepth - centerDepth * 2) > DepthThreshold * 2;

    float3 firstNormal = SceneTextureLookup(ViewportUVToSceneTextureUV(firstVec, 8), 8, false);
    float3 secondNormal = SceneTextureLookup(ViewportUVToSceneTextureUV(secondVec, 8), 8, false);
    bool normalDetected = dot(firstNormal, secondNormal) < (1. - NormalThreshold);
    
    if (depthDetected || normalDetected)
        return 1;
    
}
return 0;

#undef PI