#include <SDL3/SDL.h>
#if (_WIN32 || _WIN64)
#include <SDL3/SDL_main.h>
#endif

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "LivesScoreComponent.hpp"
#include "LivesUiComponent.hpp"
#include "ScoreUiComponent.hpp"
#include "FpsComponent.hpp"
#include "PlayerInputComponent.hpp"

#include "Minigin.hpp"
#include "Texture2D.hpp"
#include "TextureComponent.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "TextComponent.hpp"
#include "Scene.hpp"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	// Background object
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get(), dae::ResourceManager::GetInstance().LoadTexture("background.png")));
	scene.Add(std::move(go));

	// Logo object
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 358.0f, 180.0f, 0.0f});
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get(), dae::ResourceManager::GetInstance().LoadTexture("logo.png")));
	scene.Add(std::move(go));

	// Programming 4 assignment text
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 292.0f, 20.0f, 0.0f});
	auto bigFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto to = std::make_unique<dae::TextComponent>(*go.get(), "Programming 4 Assignment", bigFont);
	to->SetColor({255, 255, 0, 255});
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// Fps component
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 10.0f, 10.0f, 0.0f });
	to = std::make_unique<dae::TextComponent>(*go.get(), "FPS: 00.0", bigFont);
	to->SetColor({255, 255, 255, 255});
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::make_unique<game::FpsComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// Moving characters
	go = std::make_unique<dae::GameObject>();
	auto playerOne = go.get();
	playerOne->SetLocalPosition({ 200.0f, 200.0f, 0.0f });
	playerOne->AddComponent(std::make_unique<dae::TextureComponent>(*playerOne, dae::ResourceManager::GetInstance().LoadTexture("PlayerSprites.png"), glm::vec2{16.0f, 16.0f}, glm::vec2{0.0f, 0.0f}));
	playerOne->AddComponent(std::make_unique<game::LivesScoreComponent>(*playerOne));
	playerOne->AddComponent(std::make_unique<game::PlayerInputComponent>(*playerOne, 100.0f, 0));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto playerTwo = go.get();
	playerTwo->SetLocalPosition({ 250.0f, 250.0f, 0.0f });
	playerTwo->AddComponent(std::make_unique<dae::TextureComponent>(*playerTwo, dae::ResourceManager::GetInstance().LoadTexture("PlayerSprites.png"), glm::vec2{16.0f, 16.0f}, glm::vec2{1.0f, 0.0f}));
	playerTwo->AddComponent(std::make_unique<game::LivesScoreComponent>(*playerTwo));
	playerTwo->AddComponent(std::make_unique<game::PlayerInputComponent>(*playerTwo, 200.0f, 1));
	scene.Add(std::move(go));

	// Lives and Score components
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 10.0f, 100.0f, 0.0f });
	to = std::make_unique<dae::TextComponent>(*go.get(), "Score: 0", smallFont);
	to->SetColor({200, 200, 200, 255});
	go->AddComponent(std::make_unique<game::ScoreUiComponent>(*go.get(), *playerOne));
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 10.0f, 120.0f, 0.0f });
	to = std::make_unique<dae::TextComponent>(*go.get(), "# Lives: 3", smallFont);
	to->SetColor({200, 200, 200, 255});
	go->AddComponent(std::make_unique<game::LivesUiComponent>(*go.get(), *playerOne));
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 10.0f, 140.0f, 0.0f });
	to = std::make_unique<dae::TextComponent>(*go.get(), "Score: 0", smallFont);
	to->SetColor({200, 200, 200, 255});
	go->AddComponent(std::make_unique<game::ScoreUiComponent>(*go.get(), *playerTwo));
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 10.0f, 160.0f, 0.0f });
	to = std::make_unique<dae::TextComponent>(*go.get(), "# Lives: 3", smallFont);
	to->SetColor({200, 200, 200, 255});
	go->AddComponent(std::make_unique<game::LivesUiComponent>(*go.get(), *playerTwo));
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// TODO: tutorial for what buttons to press
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
