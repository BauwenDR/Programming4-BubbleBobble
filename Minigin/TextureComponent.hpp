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
        void Start() override {};
        void Update() override {};
        void Render() const override;

        void SetTexture(const std::shared_ptr<Texture2D> &newTexture);

        explicit TextureComponent(GameObject *pGameObject, std::shared_ptr<Texture2D> texture = nullptr);
        ~TextureComponent() override = default;

    private:
        std::shared_ptr<Texture2D> m_texture{};
    };
} // dae

#endif //MINIGIN_TEXTURECOMPONENT_HPP
