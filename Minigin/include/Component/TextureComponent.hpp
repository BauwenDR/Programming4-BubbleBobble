#ifndef MINIGIN_TEXTURECOMPONENT_HPP
#define MINIGIN_TEXTURECOMPONENT_HPP
#include <memory>

#include <SDL3/SDL_rect.h>
#include <glm/vec2.hpp>

#include "GameComponent.hpp"

namespace dae
{
    class Texture2D;

    class TextureComponent : public GameComponent
    {
    public:
        void Start() override {}
        void Update() override {}
        void Render() const override;

        void SetTexture(const std::shared_ptr<Texture2D> &newTexture);
        void SetSpriteOffset(const glm::vec2 &spritePos);

        explicit TextureComponent(GameObject &gameObject, std::shared_ptr<Texture2D> texture = nullptr, float imageScale = 1, const glm::vec2 &spriteSize = {-1, -1}, const glm::vec2 &spritePos = {0, 0});
        ~TextureComponent() override = default;

    private:
        std::shared_ptr<Texture2D> m_texture{};

        SDL_FRect m_srcRect{};

        glm::vec2 m_spritePosition{};
        glm::vec2 m_imageSize{};
        glm::vec2 m_spriteSize{};

        float m_imageScale{};

        void InitTextureDetails();
        void SetSourceRect();
    };
} // dae

#endif //MINIGIN_TEXTURECOMPONENT_HPP
