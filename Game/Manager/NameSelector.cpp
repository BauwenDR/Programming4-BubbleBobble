#include "Manager/NameSelector.hpp"

#include "GameObject.hpp"
#include "GameState.hpp"
#include "Command/ConfirmCommand.hpp"
#include "Command/LetterChangeCommand.hpp"
#include "Component/TextComponent.hpp"
#include "Input/InputManager.hpp"
#include "Prefab/StagesManager.hpp"

void game::NameSelector::Start()
{
    m_text = GetGameObject().GetComponent<dae::TextComponent>();
    assert(m_text != nullptr);

    auto const &inputManager{dae::InputManager::GetInstance()};

    inputManager.Bind(SDLK_UP, dae::Input::CommandTrigger::KeyDown, m_letterUp.get());
    inputManager.Bind(SDLK_DOWN, dae::Input::CommandTrigger::KeyDown, m_letterDown.get());
    inputManager.Bind(SDLK_RIGHT, dae::Input::CommandTrigger::KeyUp, m_confirm.get());

    inputManager.Bind(dae::Input::ControllerKey::DpadUp, 0, dae::Input::CommandTrigger::KeyDown, m_letterUp.get());
    inputManager.Bind(dae::Input::ControllerKey::DpadDown, 0, dae::Input::CommandTrigger::KeyDown, m_letterDown.get());
    inputManager.Bind(dae::Input::ControllerKey::DpadRight, 0, dae::Input::CommandTrigger::KeyUp, m_confirm.get());
}

void game::NameSelector::OnDelete()
{
    dae::InputManager::GetInstance().Unbind(m_confirm.get());
    dae::InputManager::GetInstance().Unbind(m_letterDown.get());
    dae::InputManager::GetInstance().Unbind(m_letterUp.get());
}

void game::NameSelector::CycleUp()
{
    m_letters[m_currentLetter] = (m_letters[m_currentLetter] + 1) % 26;
    SetNameText();
}

void game::NameSelector::CycleDown()
{
    --m_letters[m_currentLetter];

    if (m_letters[m_currentLetter] < 0)
    {
        m_letters[m_currentLetter] = 25;
    }

    SetNameText();
}

void game::NameSelector::NextLetter()
{
    ++m_currentLetter;

    if (static_cast<size_t>(m_currentLetter) >= std::size(m_letters))
    {
        SwitchToLeaderboard();
    }

    SetNameText();
}

game::NameSelector::NameSelector(dae::GameObject& owner)
    : GameComponent(owner)
    , m_letterUp(std::make_unique<LetterChangeCommand>(*this, true))
    , m_letterDown(std::make_unique<LetterChangeCommand>(*this, false))
    , m_confirm(std::make_unique<ConfirmCommand>(*this))
{
}

game::NameSelector::~NameSelector() = default;

void game::NameSelector::SetNameText() const
{
    if (!m_text) return;
    std::string textVal{};
    textVal.reserve(3);

    for (int const letter : m_letters)
    {
        textVal.push_back(static_cast<char>('A' + letter));
    }

    m_text->SetText(textVal);
}

void game::NameSelector::SwitchToLeaderboard() const
{
    GameState::GetInstance().SaveScore(m_text->GetText());
    StagesManager::GetInstance().LoadSceneFromJson("GameOver", false);
}
