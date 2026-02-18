//
// Created by bauwen on 2/17/26.
//

#include "TextureComponent.hpp"

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace dae
{
    void TextureComponent::Start([[maybe_unused]] GameObject &object)
    {
    }

    void TextureComponent::Update([[maybe_unused]] GameObject &object)
    {
    }

    void TextureComponent::Render([[maybe_unused]] const GameObject &object) const
    {
        if (m_texture != nullptr)
        {
            const auto& pos = object.Position.GetPosition();
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
        }
    }
} // dae