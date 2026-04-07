#include <SDL3/SDL.h>

#if (_WIN32 or _WIN64)
#include <SDL3/SDL_main.h>
#endif

#if _DEBUG and __has_include(<vld.h>)
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

std::unique_ptr<dae::GameObject> prefabLoader(nlohmann::json const & data) {
	auto prefab = std::make_unique<dae::GameObject>();
	const auto prefabName{data["name"].get<std::string>()};


	if (prefabName == "background") {
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab.get(),
			dae::ResourceManager::GetInstance().LoadTexture(data["texture"].get<std::string>()),
			4)
		);
	}

	if (prefabName == "player") {
		static int playerNumber{0};

		prefab->SetLocalPosition({
			data["position"]["x"].get<float>(),
			data["position"]["y"].get<float>(),
			0.0f
		});

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("PlayerSprites.png"),
			4,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(playerNumber), 0.0f})
		);

		prefab->AddComponent(std::make_unique<game::LivesScoreComponent>(*prefab));

		prefab->AddComponent(std::make_unique<game::PlayerInputComponent>(*prefab, 100.0f, playerNumber));

		++playerNumber;
	}

	return prefab;
}

static void load()
{
	dae::SceneManager::GetInstance().CreateScene("Stage1", &prefabLoader);
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
