#include "StagesManager.hpp"

#include <format>
#include <fstream>

#include "SceneManager.hpp"
#include "Animations/PlayerAnimations.hpp"
#include "Animations/ZenChanAnimation.hpp"
#include "Component/AnimationComponent.hpp"
#include "Component/BubbleComponent.hpp"
#include "Component/LivesScoreComponent.hpp"
#include "Component/PlayerInputComponent.hpp"
#include "Component/PickupComponent.hpp"
#include "UI/ScoreUiComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Component/FallingDeadEnemy.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/PlatformAiMovement.hpp"
#include "Component/PlayerAnimationComponent.hpp"
#include "Component/PlayerSoundProducer.hpp"
#include "Component/SwitchSceneOnEnemiesKilled.hpp"
#include "Component/TextComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Component/WrapAroundScreenComponent.hpp"
#include "Component/ZenChanAnimationComponent.hpp"
#include "Event/Sdbm.hpp"
#include "glm/gtx/norm.inl"
#include "Render/ResourceManager.hpp"

void game::StagesManager::LoadNextStageFromJson()
{
	LoadStageFromJson(m_currentStage+1);
}

void game::StagesManager::LoadStageFromJson(int32_t stageNumber)
{
	m_currentStage = stageNumber;
	LoadSceneFromJson(std::format("Stage{}", stageNumber));
}

void game::StagesManager::LoadSceneFromJson(std::string const &sceneName, bool preserveKeepAlive)
{
	using json = nlohmann::json;

	m_scene = &dae::SceneManager::GetInstance().CreateScene(preserveKeepAlive);

	// TODO log the fact that it failed
	// Return empty scene if JSON failed to load
	std::ifstream jsonFile{dae::ResourceManager::GetInstance().LoadFile(sceneName + ".json")};
	if (!jsonFile.is_open()) return;

	const json &sceneJson{json::parse(jsonFile)};

	m_scaleFactor = sceneJson["scalar"].get<float>();

	for (const auto &item : sceneJson["prefabs"])
	{
		if (auto newItem{PrefabLoader(item)})
		{
			m_scene->Add(std::move(newItem));
		}
	}
}

void game::StagesManager::SpawnBubble(ProjectilePrefabData const &data) const
{
	auto bubblePrefab{std::make_unique<dae::GameObject>()};

	bubblePrefab->SetLocalPosition({
		data.location,
		0.0f
	});

	bubblePrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*bubblePrefab,
		dae::ResourceManager::GetInstance().LoadTexture("PlayerBubble.png"),
		m_scaleFactor
	));

	bubblePrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*bubblePrefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("BUBBLE")));
	bubblePrefab->AddComponent(std::make_unique<BubbleComponent>(*bubblePrefab, data.facingLeft));

	m_scene->Add(std::move(bubblePrefab));
}

void game::StagesManager::SpawnPickup(PickupPrefabData const &data) const
{
	auto pickupPrefab{std::make_unique<dae::GameObject>()};

	pickupPrefab->SetLocalPosition({
		data.location,
		0.0f
	});

	pickupPrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*pickupPrefab,
		dae::ResourceManager::GetInstance().LoadTexture("PickupSprites.png"),
		m_scaleFactor,
		glm::vec2{16.0f, 16.0f},
		glm::vec2{0.0f, 0.0f}
	));

	pickupPrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*pickupPrefab, glm::vec2{64.0f, 64.0f}, dae::sdbm_hash("PICKUP")));
	pickupPrefab->AddComponent(std::make_unique<PickupComponent>(*pickupPrefab, data.worth));

	m_scene->Add(std::move(pickupPrefab));
}

void game::StagesManager::SpawnDeadZenChanEnemy(ProjectilePrefabData const &data) const
{
	auto pickupPrefab{std::make_unique<dae::GameObject>()};

	pickupPrefab->SetLocalPosition({
		data.location,
		0.0f
	});

	pickupPrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*pickupPrefab,
		dae::ResourceManager::GetInstance().LoadTexture("PickupSprites.png"),
		m_scaleFactor,
		glm::vec2{16.0f, 16.0f},
		glm::vec2{0.0f, 0.0f}
	));

	pickupPrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*pickupPrefab, glm::vec2{64.0f, 64.0f}, dae::sdbm_hash("DEAD_ENEMY")));
	pickupPrefab->AddComponent(std::make_unique<PhysicsComponent>(*pickupPrefab, data.facingLeft, 320.0f, 520.0f));
	pickupPrefab->AddComponent(std::make_unique<FallingDeadEnemy>(*pickupPrefab, data.facingLeft));

	m_scene->Add(std::move(pickupPrefab));
}

void game::StagesManager::AttachGui(std::unique_ptr<dae::GuiWindow> &&gui) const
{
	m_scene->AddGui(std::move(gui));
}

game::PlayerData game::StagesManager::GetClosestActivePlayer(glm::vec3 const &searchPos) const
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

std::unique_ptr<dae::GameObject> game::StagesManager::PrefabLoader(nlohmann::json const &data)
{
	auto prefab = std::make_unique<dae::GameObject>();
	const auto prefabName{data["name"].get<std::string>()};

	prefab->SetLocalPosition({
		data["position"]["x"].get<float>() * m_scaleFactor,
		data["position"]["y"].get<float>() * m_scaleFactor,
		0.0f
	});

	if (prefabName == "background") {
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab.get(),
			dae::ResourceManager::GetInstance().LoadTexture(data["texture"].get<std::string>()),
			m_scaleFactor)
		);
	}

	else if (prefabName == "level-manager")
	{
		auto const threshold{data["threshold"].get<int32_t>()};
		prefab->AddComponent(std::make_unique<SwitchSceneOnEnemiesKilled>(*prefab, threshold));
	}

	else if (prefabName == "player") {
		if (m_players.size() == static_cast<size_t>(m_maxPlayers)) return nullptr;

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("PlayerSprites.png"),
			m_scaleFactor,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("PLAYER")));
		prefab->AddComponent(std::make_unique<PhysicsComponent>(*prefab, !m_players.empty()));
		prefab->AddComponent(std::make_unique<LivesScoreComponent>(*prefab));
		prefab->AddComponent(std::make_unique<PlayerInputComponent>(*prefab, static_cast<int>(m_players.size())));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &PLAYER_ANIMATIONS.at(!m_players.empty() ? PlayerAnimationStates::IdleLeft : PlayerAnimationStates::IdleRight), 1.0f/3.0f, glm::vec2{static_cast<float>(m_players.size()) * 4.0f, 0.0f} ));
		prefab->AddComponent(std::make_unique<PlayerAnimationComponent>(*prefab));
		prefab->AddComponent(std::make_unique<PlayerSoundProducer>(*prefab));

		prefab->KeepAlive = true;
		m_players.emplace_back(prefab.get(), prefab->GetComponent<LivesScoreComponent>());
	}

	else if (prefabName == "zen-chan-enemy")
	{
		bool facingLeft{data["facingLeft"].get<bool>()};

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("ZenChan.png"),
			m_scaleFactor,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("ENEMY")));
		prefab->AddComponent(std::make_unique<PhysicsComponent>(*prefab, facingLeft, 320.0f));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &ZEN_CHAN_ANIMATIONS.at(facingLeft ? ZenChanAnimationStates::WalkingLeft : ZenChanAnimationStates::WalkingRight), 1.0f / 6.0f));
		prefab->AddComponent(std::make_unique<PlatformAiMovement>(*prefab, facingLeft ? PlatformAiActions::WalkingLeft : PlatformAiActions::WalkingRight));
		prefab->AddComponent(std::make_unique<ZenChanAnimationComponent>(*prefab));
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

	else if (prefabName == "level-roof")
	{
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			 256.0f * m_scaleFactor,
			24.0f * m_scaleFactor
		},
		dae::sdbm_hash("LEVEL_ROOF")));
	}

	else if (prefabName == "wind-current")
	{
		uint32_t const tag{data["isLeft"].get<bool>() ? dae::sdbm_hash("WIND_CURRENT_LEFT") : dae::sdbm_hash("WIND_CURRENT_RIGHT")};
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			data["rect"]["width"].get<float>() * m_scaleFactor,
			data["rect"]["height"].get<float>() * m_scaleFactor
		},
		tag));
	}

	else if (prefabName == "rect-collider")
	{
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			data["rect"]["width"].get<float>() * m_scaleFactor,
			data["rect"]["height"].get<float>() * m_scaleFactor
		},
		dae::sdbm_hash("STAGE")));
	}

	else if (prefabName == "ai-jumpable-zone")
	{
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			data["rect"]["width"].get<float>() * m_scaleFactor,
			data["rect"]["height"].get<float>() * m_scaleFactor,
		},
		dae::sdbm_hash("AI_JUMPABLE")));
	}

	else if (prefabName == "ai-jump-zone")
	{
		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{
			4.0f * m_scaleFactor,
			4.0f * m_scaleFactor
		},
		dae::sdbm_hash("PLATFORM_EDGE")));
	}

	return prefab;
}

game::StagesManager::StagesManager()
	: m_uiFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24))
{
}
