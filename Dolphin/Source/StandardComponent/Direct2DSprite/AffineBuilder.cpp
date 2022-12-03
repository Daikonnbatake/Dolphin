#include "Direct2DSprite.h"
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::AffineBuilder()
{
    this->matrix = D2D1::Matrix3x2F();
    this->origin = D2D1::Point2F();
}


D2D1_MATRIX_3X2_F
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::ReadMatrix()
{
    return this->matrix;
}


Dolphin::StandardComponent::Direct2DSprite::IMatrixBuilder&
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::Scale(
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


Dolphin::StandardComponent::Direct2DSprite::IMatrixBuilder&
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::Rotate(float degrees)
{
    this->matrix = this->matrix * D2D1::Matrix3x2F::Rotation(
        degrees,
        this->origin
    );

    return *this;
}


Dolphin::StandardComponent::Direct2DSprite::IMatrixBuilder&
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::FlipX()
{
    this->origin = this->origin * D2D1::Matrix3x2F(-1, 0, 0, 1, 1, 0);
    return *this;
}


Dolphin::StandardComponent::Direct2DSprite::IMatrixBuilder&
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::FripY()
{
    this->origin = this->origin * D2D1::Matrix3x2F(0, 0, 0, -1, 1, 0);
    return *this;
}


Dolphin::StandardComponent::Direct2DSprite::IMatrixBuilder&
Dolphin::StandardComponent::Direct2DSprite::AffineBuilder::Origin(
    float x,
    float y)
{
    this->origin = D2D1::Point2F(x, y);
    return *this;
}