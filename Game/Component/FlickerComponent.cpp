#include "FlickerComponent.hpp"

#include "GameObject.hpp"
#include "Time.hpp"
#include "Component/TextureComponent.hpp"
#include "Event/Sdbm.hpp"

void game::FlickerComponent::Start()
{
    m_texture = GetGameObject().GetComponent<dae::TextureComponent>();
    assert(m_texture != nullptr);

    m_visible = m_texture->Enabled;

    GetGameObject().AddObserver(this);
}

void game::FlickerComponent::Update()
{
    if (!m_flickerEnabled) return;

    m_timer += Time::timeDelta();

    if (m_timer < INTERVAL) return;

    m_timer = std::fmod(m_timer, INTERVAL);
    m_visible = !m_visible;

    m_texture->Enabled = m_visible;
}

void game::FlickerComponent::Notify(uint32_t event, dae::ObserverData const*)
{
    if (event == dae::sdbm_hash("enable_flicker"))
    {
        m_flickerEnabled = true;
        m_timer = 0.0f;
    }

    if (event == dae::sdbm_hash("disable_flicker"))
    {
        m_flickerEnabled = false;
        m_texture->Enabled = true;
    }
}

game::FlickerComponent::FlickerComponent(dae::GameObject& owner)
    : GameComponent(owner)
{
}
