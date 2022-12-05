#pragma once
#include <d2d1_1.h>
#include "DolphinStruct.h"

namespace Dolphin
{
    namespace StandardComponent
    {
        class AffineBuilder
        {
          private:
            D2D1_MATRIX_3X2_F matrix;
            D2D1_POINT_2F     origin;
            D2D1_RECT_F       cropRect;
            float             width;
            float             height;
            float             offsetX;
            float             offsetY;

          public:
            AffineBuilder(D2D1_RECT_F cropRect);
            D2D1_MATRIX_3X2_F ReadMatrix();
            AffineBuilder&    Scale(float scaleX, float scaleY);
            AffineBuilder&    Rotate(float degrees);
            AffineBuilder&    FlipX();
            AffineBuilder&    FripY();
            AffineBuilder&    Origin(float x, float y);
        };
    }
}