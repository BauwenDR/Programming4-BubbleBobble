#include "TextureComponent.hpp"

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace dae
{
    void TextureComponent::Render() const
    {
        if (m_texture != nullptr)
        {
            const auto &pos = GetGameObject()->Position.GetPosition();
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
        }
    }

    void TextureComponent::SetTexture(const std::shared_ptr<Texture2D> &newTexture)
    {
        m_texture = newTexture;
    }

    TextureComponent::TextureComponent(GameObject *pGameObject, std::shared_ptr<Texture2D> texture)
        : GameComponent(pGameObject), m_texture(std::move(texture))
    {
    }
}
