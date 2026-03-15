#include "TextureComponent.hpp"

#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Texture2D.hpp"

namespace dae
{
    void TextureComponent::Render() const
    {
        if (m_texture != nullptr)
        {
            const auto &pos = GetGameObject().GetWorldPosition();
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, &m_srcRect);
        }
    }

    void TextureComponent::SetTexture(const std::shared_ptr<Texture2D> &newTexture)
    {
        m_texture = newTexture;
        InitTextureDetails();
    }

    void TextureComponent::SetSpriteOffset(const glm::vec2 &spritePos)
    {
        SetSourceRect(spritePos);
    }

    TextureComponent::TextureComponent(GameObject &gameObject, std::shared_ptr<Texture2D> texture, const glm::vec2 &spriteSize, const glm::vec2 &spritePos)
        : GameComponent(gameObject), m_texture(std::move(texture)), m_spriteSize(spriteSize)
    {
        InitTextureDetails();
        SetSourceRect(spritePos);
    }

    void TextureComponent::InitTextureDetails() {
        if (m_texture == nullptr) return;

        m_imageSize = m_texture->GetSize();
    }

    void TextureComponent::SetSourceRect(const glm::vec2 &spritePos) {
        m_srcRect = {0.0f, 0.0f, m_imageSize.x, m_imageSize.y};

        if (m_spriteSize.x < 0.0f || m_spriteSize.y < 0.0f) return;

        m_srcRect.w = m_spriteSize.x;
        m_srcRect.h = m_spriteSize.y;

        m_srcRect.x = spritePos.x * m_spriteSize.x;
        m_srcRect.y = spritePos.y * m_spriteSize.y;

        assert(m_srcRect.w > 0.0f && m_srcRect.h > 0.0f && "Image sprite bounds cannot be negative.");
        assert(m_srcRect.x + m_spriteSize.x <= m_imageSize.x && "New source rect width was out of bounds.");
        assert(m_srcRect.y + m_spriteSize.y <= m_imageSize.y && "New source rect height was out of bounds.");
    }
}
