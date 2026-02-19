#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL_pixels.h>

#include "GameComponent.hpp"

namespace dae
{
	class TextureComponent;
	class Font;
	class Texture2D;
	class TextComponent final : public GameComponent
	{
	public:
		void Start() override;
		void Update() override;
		void Render() const override {};

		void SetText(const std::string_view& text);
		void SetColor(const SDL_Color& color);

		TextComponent(GameObject *pGameObject, const std::string_view& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });

		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font{};

        TextureComponent* m_textureComponent{};
	};
}
