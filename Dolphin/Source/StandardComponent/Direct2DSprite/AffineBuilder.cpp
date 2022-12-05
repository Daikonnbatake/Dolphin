#include "AffineBuilder.h"
Dolphin::StandardComponent::AffineBuilder::AffineBuilder(D2D1_RECT_F cropRect)
{
    this->cropRect = cropRect;
    this->matrix = D2D1::Matrix3x2F::Identity();

    this->width = this->cropRect.right - this->cropRect.left;
    this->height = this->cropRect.bottom - this->cropRect.top;
    this->offsetX = this->cropRect.left;
    this->offsetY = this->cropRect.top;
    this->origin = D2D1::Point2F(offsetX + (width / 2), offsetY + (height / 2));
}


D2D1_MATRIX_3X2_F
Dolphin::StandardComponent::AffineBuilder::ReadMatrix()
{
    return this->matrix;
}


Dolphin::StandardComponent::AffineBuilder&
Dolphin::StandardComponent::AffineBuilder::Scale(
    float scaleX,
    float scaleY
    )
{
    this->matrix = this->matrix * D2D1::Matrix3x2F::Scale(
        D2D1::SizeF(scaleX, scaleY),
        this->origin
    );

    return *this;
}


Dolphin::StandardComponent::AffineBuilder&
Dolphin::StandardComponent::AffineBuilder::Rotate(float degrees)
{
    this->matrix = this->matrix * D2D1::Matrix3x2F::Rotation(
        degrees,
        this->origin
    );

    return *this;
}


Dolphin::StandardComponent::AffineBuilder&
Dolphin::StandardComponent::AffineBuilder::FlipX()
{
    this->matrix = this->matrix * D2D1::Matrix3x2F::Scale(
        D2D1::SizeF(-1, 1),
        this->origin
    );

    return *this;
}


Dolphin::StandardComponent::AffineBuilder&
Dolphin::StandardComponent::AffineBuilder::FripY()
{
    this->matrix = this->matrix * D2D1::Matrix3x2F::Scale(
        D2D1::SizeF(1, -1),
        this->origin
    );
    return *this;
}


Dolphin::StandardComponent::AffineBuilder&
Dolphin::StandardComponent::AffineBuilder::Origin(
    float x,
    float y)
{
    this->origin = D2D1::Point2F(
        offsetX + (min(max(x, 0), 1) * this->width),
        offsetY + (min(max(y, 0), 1) * this->height)
    );
    return *this;
}