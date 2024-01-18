
bool eq = FirstFace == SecondFace;
if ((eq && FirstFace == 0) || (abs(FirstFace - SecondFace) > 0.6))
    return EdgeColor;
else if (eq && FirstFace == 1)
    return InvertedColor;
else
    return DefaultColor;