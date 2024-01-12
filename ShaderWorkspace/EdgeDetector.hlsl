
#define PI 3.1415926538

float centerDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV, 1), 1, false).r;
float depthScaler = centerDepth / DefaultDepth;
float scaledEdgeOffset = EdgeUVOffset / depthScaler;
float scaledThreshold = EdgeThreshold * depthScaler;

double curv = 0;
float angleStep = PI / NumberEdgeChecks;
for (int i = 0; i < NumberEdgeChecks; i++)
{
    double2 offsetVec = double2(cos(angleStep * i), sin(angleStep * i)) * scaledEdgeOffset;
    double firstDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV+offsetVec, 1), 1, false).r;
    double secondDepth = SceneTextureLookup(ViewportUVToSceneTextureUV(UV-offsetVec, 1), 1, false).r;
    curv = max(curv, abs(firstDepth + secondDepth - centerDepth * 2));
}
return curv > scaledThreshold * 2;