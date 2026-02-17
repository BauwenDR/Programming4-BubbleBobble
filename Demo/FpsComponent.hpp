#ifndef MINIGIN_FPSCOMPONENT_HPP
#define MINIGIN_FPSCOMPONENT_HPP
#include <memory>

#include "GameComponent.hpp"


namespace dae
{
    class TextComponent;
}

class FpsComponent : public dae::GameComponent
{
public:
    void start(dae::GameObject &object) override;
    void update(dae::GameObject &object) override;
    void render(const dae::GameObject &object) const override;

    ~FpsComponent() override = default;

private:
    std::shared_ptr<dae::TextComponent> m_text_component{};
};


#endif //MINIGIN_FPSCOMPONENT_HPP