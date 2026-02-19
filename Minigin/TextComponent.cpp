#include "TextComponent.hpp"

#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "Renderer.hpp"
#include "Font.hpp"
#include "GameObject.hpp"
#include "Texture2D.hpp"
#include "TextureComponent.hpp"

void dae::TextComponent::Start()
{
	m_textureComponent = GetGameObject()->GetComponent<TextureComponent>();
}

void dae::TextComponent::Update()
{
	if (!m_textureComponent)
	{
		assert(false && "No valid text component");
		return;
	}

	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_textureComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string_view& text)
{
	if (m_text != text)
	{
		m_text = text;
		m_needsUpdate = true;
	}
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_needsUpdate = true;
}

dae::TextComponent::TextComponent(GameObject *pGameObject, const std::string_view& text, std::shared_ptr<Font> font, const SDL_Color& color)
	: GameComponent(pGameObject), m_needsUpdate(true), m_text(text), m_color(color), m_font(std::move(font))
{
}
