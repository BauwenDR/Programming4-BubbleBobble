#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "FpsComponent.hpp"
#include "Texture2D.hpp"
#include "TextureComponent.hpp"

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.hpp"
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
	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("background.png")));
	scene.Add(std::move(go));

	// Logo object
	go = std::make_unique<dae::GameObject>();
	go->Position = { 358, 180 };
	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get(), dae::ResourceManager::GetInstance().LoadTexture("logo.png")));
	scene.Add(std::move(go));

	// Programming 4 assignment text
	go = std::make_unique<dae::GameObject>();
	go->Position = { 292, 20, 0 };
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextComponent>(go.get(), "Programming 4 Assignment", font);
	to->SetColor({255, 255, 0, 255});
	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// Fps component
	go = std::make_unique<dae::GameObject>();
	go->Position = { 10, 10, 0 };
	to = std::make_unique<dae::TextComponent>(go.get(), "FPS: 00.0", font);
	to->SetColor({255, 255, 255, 255});
	go->AddComponent(std::make_unique<dae::TextureComponent>(go.get()));
	go->AddComponent(std::make_unique<demo::FpsComponent>(go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// go = std::make_unique<dae::GameObject>();
	// to = std::make_shared<dae::TextComponent>("FPS: 00", font);
	// to->SetColor({ 200, 200, 200, 255 });
	// go->Position = { 10, 10 };
	// go->AddComponent(std::make_shared<demo::FpsComponent>());
	// go->AddComponent(to);
	// scene.Add(std::move(go));
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
