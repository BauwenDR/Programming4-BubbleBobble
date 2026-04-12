#include "PrefabManager.hpp"

#include <fstream>

#include "SceneManager.hpp"
#include "Animations/PlayerAnimations.hpp"
#include "Animations/ZenChanAnimation.hpp"
#include "Component/AnimationComponent.hpp"
#include "Component/LivesScoreComponent.hpp"
#include "Component/PlayerInputComponent.hpp"
#include "Component/PickupComponent.hpp"
#include "UI/ScoreUiComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/PlatformAiMovement.hpp"
#include "Component/PlayerAnimationComponent.hpp"
#include "Component/TextComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Component/WrapAroundScreenComponent.hpp"
#include "Component/ZenChanAnimationComponent.hpp"
#include "Event/Sdbm.hpp"
#include "glm/gtx/norm.inl"
#include "Render/ResourceManager.hpp"

void game::PrefabManager::LoadSceneFromJson(std::string const &sceneName)
{
	using json = nlohmann::json;
	m_scene = &dae::SceneManager::GetInstance().CreateScene();

	// TODO log the fact that it failed
	// Return empty scene if json failed to load
	std::ifstream jsonFile{dae::ResourceManager::GetInstance().LoadFile(sceneName + ".json")};
	if (!jsonFile.is_open()) return;

	for (const json &sceneJson{json::parse(jsonFile)}; const auto &item : sceneJson["prefabs"])
	{
		m_scene->Add(PrefabLoader(item));
	}
}

void game::PrefabManager::SpawnPickup(PickupPrefabData const &data) const
{
	auto pickupPrefab = std::make_unique<dae::GameObject>();

	pickupPrefab->SetLocalPosition({
		data.location,
		0.0f
	});

	pickupPrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*pickupPrefab,
		dae::ResourceManager::GetInstance().LoadTexture("PickupSprites.png"),
		4.0f,
		glm::vec2{16.0f, 16.0f},
		glm::vec2{0.0f, 0.0f}
	));

	pickupPrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*pickupPrefab, glm::vec2{64.0f, 64.0f}, dae::sdbm_hash("PICKUP")));
	pickupPrefab->AddComponent(std::make_unique<PickupComponent>(*pickupPrefab, data.worth));

	m_scene->Add(std::move(pickupPrefab));
}

game::PlayerData game::PrefabManager::GetClosestActivePlayer(glm::vec3 const &searchPos) const
{
	auto GetDistanceScore = [&searchPos](PlayerData const &data)
	{
		return glm::distance2(searchPos, data.object->GetWorldPosition());
	};

	if (auto const it = std::ranges::min_element(m_players, {}, GetDistanceScore); it != m_players.end())
	{
		return *it;
	}

	// contains only nullptr's
	return {};
}

std::unique_ptr<dae::GameObject> game::PrefabManager::PrefabLoader(nlohmann::json const &data)
{
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
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<LivesScoreComponent>(*prefab));
		prefab->AddComponent(std::make_unique<PlayerInputComponent>(*prefab, static_cast<int>(m_players.size())));
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("PLAYER")));
		prefab->AddComponent(std::make_unique<dae::PhysicsComponent>(*prefab));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &PLAYER_ANIMATIONS.at(!m_players.empty() ? PlayerAnimationState::IdleLeft : PlayerAnimationState::IdleRight), glm::vec2{static_cast<float>(m_players.size()) * 4.0f, 0.0f} ));
		prefab->AddComponent(std::make_unique<PlayerAnimationComponent>(*prefab, !m_players.empty()));

		m_players.emplace_back(prefab.get(), prefab->GetComponent<LivesScoreComponent>());
	}

	else if (prefabName == "zen-chan-enemy")
	{
		bool facingLeft{data["facingLeft"].get<bool>()};

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("ZenChan.png"),
			4.0f,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("ENEMY")));
		prefab->AddComponent(std::make_unique<dae::PhysicsComponent>(*prefab));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &ZEN_CHAN_ANIMATIONS.at(facingLeft ? ZenChanAnimationState::WalkingLeft : ZenChanAnimationState::WalkingRight)));
		prefab->AddComponent(std::make_unique<PlatformAiMovement>(*prefab, facingLeft ? PlatformAiAction::WalkingLeft : PlatformAiAction::WalkingRight));
		prefab->AddComponent(std::make_unique<ZenChanAnimationComponent>(*prefab, facingLeft));
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

		if (playerNumber >= static_cast<int>(m_players.size())) return prefab;

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(*prefab));
		prefab->AddComponent(std::make_unique<dae::TextComponent>(*prefab, "000000000", m_uiFont));
		prefab->AddComponent(std::make_unique<ScoreUiComponent>(*prefab, m_players[playerNumber].object));

		++playerNumber;
	}

	return prefab;
}

game::PrefabManager::PrefabManager()
	: m_uiFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24))
{
}
