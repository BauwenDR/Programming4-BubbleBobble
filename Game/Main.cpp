#include <filesystem>
namespace fs = std::filesystem;

#if (_WIN32 or _WIN64)
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

#if _DEBUG and __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Component/LivesScoreComponent.hpp"
#include "Component/PlayerInputComponent.hpp"
#include "Component/PickupComponent.hpp"
#include "UI/ScoreUiComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/TextComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Event/Sdbm.hpp"
#include "SceneManager.hpp"
#include "Render/ResourceManager.hpp"
#include "Scene.hpp"
#include "Minigin.hpp"

// TODO place in class so we can track number of players (and accept scale as param)
std::unique_ptr<dae::GameObject> prefabLoader(nlohmann::json const & data) {
	static std::vector<dae::GameObject*> players{};
	static auto uiFont{dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24)};

	auto prefab = std::make_unique<dae::GameObject>();
	const auto prefabName{data["name"].get<std::string>()};

	prefab->SetLocalPosition({
		data["position"]["x"].get<float>() * 4.0f,
		data["position"]["y"].get<float>() * 4.0f,
		0.0f
	});

	if (prefabName == "background") {
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab.get(),
			dae::ResourceManager::GetInstance().LoadTexture(data["texture"].get<std::string>()),
			4.0f)
		);
	}

	else if (prefabName == "player") {
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("PlayerSprites.png"),
			4.0f,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<game::LivesScoreComponent>(*prefab));
		prefab->AddComponent(std::make_unique<game::PlayerInputComponent>(*prefab, static_cast<int>(players.size())));
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("PLAYER")));
		prefab->AddComponent(std::make_unique<dae::PhysicsComponent>(*prefab));

		players.emplace_back(prefab.get());
	}

	else if (prefabName == "rect-collider")
	{
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			data["rect"]["width"].get<float>() * 4.0f,
			data["rect"]["height"].get<float>() * 4.0f
		},
		dae::sdbm_hash("STAGE")));
	}

	else if (prefabName == "player-score")
	{
		static int playerNumber{0};

		if (playerNumber >= static_cast<int>(players.size())) return prefab;

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(*prefab));
		prefab->AddComponent(std::make_unique<dae::TextComponent>(*prefab, "000000000", uiFont));
		prefab->AddComponent(std::make_unique<game::ScoreUiComponent>(*prefab, players[playerNumber]));

		++playerNumber;
	}

	else if (prefabName == "pickup")
	{
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("PickupSprites.png"),
			4.0f,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{0.0f, 0.0f}
		));

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f, 64.0f}, dae::sdbm_hash("PICKUP")));
		prefab->AddComponent(std::make_unique<game::PickupComponent>(*prefab, data["worth"].get<int>()));
	}

	return prefab;
}

static void load()
{
	dae::SceneManager::GetInstance().CreateScene("Stage3", &prefabLoader);
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
