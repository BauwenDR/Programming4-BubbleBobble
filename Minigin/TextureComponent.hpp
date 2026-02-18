#ifndef MINIGIN_TEXTURECOMPONENT_HPP
#define MINIGIN_TEXTURECOMPONENT_HPP
#include <memory>

#include "GameComponent.hpp"

namespace dae
{
    class Texture2D;
    class TextureComponent : public GameComponent
    {
    public:
        TextureComponent(std::shared_ptr<Texture2D> texture) : m_texture(std::move(texture)) {}
        ~TextureComponent() override = default;

        void Start(GameObject &object) override;
        void Update(GameObject &object) override;
        void Render(const GameObject &object) const override;

    private:
        std::shared_ptr<Texture2D> m_texture{};
    };
} // dae

#endif //MINIGIN_TEXTURECOMPONENT_HPP