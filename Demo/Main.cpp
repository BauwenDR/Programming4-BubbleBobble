#include <SDL3/SDL.h>
#if (_WIN32 || _WIN64)
#include <SDL3/SDL_main.h>
#endif

#include "FpsComponent.hpp"
#include "MoveObjectComponent.hpp"
#include "PlottingWindows.hpp"

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

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
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextComponent>(*go.get(), "Programming 4 Assignment", font);
	to->SetColor({255, 255, 0, 255});
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// Fps component
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 10.0f, 10.0f, 0.0f });
	to = std::make_unique<dae::TextComponent>(*go.get(), "FPS: 00.0", font);
	to->SetColor({255, 255, 255, 255});
	go->AddComponent(std::make_unique<dae::TextureComponent>(*go.get()));
	go->AddComponent(std::make_unique<demo::FpsComponent>(*go.get()));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));

	// Moving characters
	go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition({ 200.0f, 200.0f, 0.0f });
	dae::GameObject* parentObject{go.get()};

	auto child = new dae::GameObject();
	child->SetParent(parentObject, false);
	child->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	child->AddComponent(std::make_unique<dae::TextureComponent>(*child, dae::ResourceManager::GetInstance().LoadTexture("Character.png")));
	child->AddComponent(std::make_unique<MoveObjectComponent>(*child, 100.0f, 0));

	child = new dae::GameObject();
	child->SetParent(parentObject, false);
	child->SetLocalPosition({ 50.0f, 50.0f, 0.0f });
	child->AddComponent(std::make_unique<dae::TextureComponent>(*child, dae::ResourceManager::GetInstance().LoadTexture("Character.png")));
	child->AddComponent(std::make_unique<MoveObjectComponent>(*child, 200.0f, 1));

	scene.Add(std::move(go));

	scene.AddGui(std::make_unique<demo::ExerciseOneWindow>());
	scene.AddGui(std::make_unique<demo::ExerciseTwoWindow>());
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
