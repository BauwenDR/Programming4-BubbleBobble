#include "WrapAroundScreenComponent.hpp"

#include "GameObject.hpp"

void game::WrapAroundScreenComponent::Update()
{
    auto position{GetGameObject().GetLocalTransform().GetPosition()};
    if (position.y >= 232.0f * 4.0f)
    {
        position.y -= 248.0f * 4.0f;
        GetGameObject().SetLocalPosition(position);
    }
}
