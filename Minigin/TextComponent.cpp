#include "TextComponent.hpp"

#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "Renderer.hpp"
#include "Font.hpp"
#include "Texture2D.hpp"

void dae::TextComponent::Start([[maybe_unused]] dae::GameObject &object) {}

void dae::TextComponent::Update([[maybe_unused]] GameObject &object)
{
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
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render([[maybe_unused]] const dae::GameObject &object) const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = object.Position.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::set_text(const std::string_view& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::set_color(const SDL_Color& color)
{
	m_color = color;
	m_needsUpdate = true;
}

dae::TextComponent::TextComponent(const std::string_view& text, std::shared_ptr<Font> font, const SDL_Color& color)
	: m_needsUpdate(true), m_text(text), m_color(color), m_font(std::move(font)), m_textTexture(nullptr)
{ }
