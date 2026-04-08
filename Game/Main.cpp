#include <filesystem>
namespace fs = std::filesystem;

#if (_WIN32 or _WIN64)
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

#if _DEBUG and __has_include(<vld.h>)
#include <vld.h>
#endif

#include "LivesScoreComponent.hpp"
#include "PlayerInputComponent.hpp"

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
	auto prefab = std::make_unique<dae::GameObject>();
	const auto prefabName{data["name"].get<std::string>()};

	if (prefabName == "background") {
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab.get(),
			dae::ResourceManager::GetInstance().LoadTexture(data["texture"].get<std::string>()),
			4.0f)
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
			4.0f,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(playerNumber), 0.0f})
		);

		prefab->AddComponent(std::make_unique<game::LivesScoreComponent>(*prefab));

		prefab->AddComponent(std::make_unique<game::PlayerInputComponent>(*prefab, playerNumber));

		auto collider{std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("PLAYER"))};
		dae::PhysicsSystem::GetInstance().RegisterCollider(collider.get());
		prefab->AddComponent(std::move(collider));

		prefab->AddComponent(std::make_unique<dae::PhysicsComponent>(*prefab));

		++playerNumber;
	}

	if (prefabName == "rect-collider")
	{
		prefab->SetLocalPosition({
			data["rect"]["x"].get<float>() * 4.0f,
			data["rect"]["y"].get<float>() * 4.0f,
			0.0f
		});

		auto collider{std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			data["rect"]["width"].get<float>() * 4.0f,
			data["rect"]["height"].get<float>() * 4.0f
		},
		dae::sdbm_hash("STAGE"))};

		dae::PhysicsSystem::GetInstance().RegisterCollider(collider.get());
		prefab->AddComponent(std::move(collider));
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
