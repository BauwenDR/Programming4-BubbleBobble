#pragma once
#include <SDL3/SDL.h>
#include "Singleton.hpp"
#include "Texture2D.hpp"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D &texture, float x, float y, float scale = 1.0f, const SDL_FRect *srcRect = nullptr) const;

		[[nodiscard]] SDL_Renderer* GetSDLRenderer() const;

		void SetTextureScaleMode(const Texture2D &texture, SDL_ScaleMode scaleMode) const;

		[[nodiscard]] const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

