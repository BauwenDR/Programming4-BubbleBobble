#include "StagesManager.hpp"

#include <format>
#include <fstream>

#include "SceneManager.hpp"
#include "Animations/MightaAnimation.hpp"
#include "Animations/PickupSprites.hpp"
#include "Animations/PlayerAnimations.hpp"
#include "Animations/ZenChanAnimation.hpp"
#include "Component/AnimationComponent.hpp"
#include "Component/AttackIfPlayerAtSameHeight.hpp"
#include "Component/BoulderComponent.hpp"
#include "Component/BubbleComponent.hpp"
#include "Component/BubbleExpireTimer.hpp"
#include "Component/CapturableComponent.hpp"
#include "Component/LivesScoreComponent.hpp"
#include "Component/PlayerInputComponent.hpp"
#include "Component/PickupComponent.hpp"
#include "UI/ScoreUiComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Component/DisablePlayerOnZeroLives.hpp"
#include "Component/FallingDeadEnemy.hpp"
#include "Component/FlickerComponent.hpp"
#include "Component/MightaAnimationComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/PlatformAiMovement.hpp"
#include "Component/PlayerAnimationComponent.hpp"
#include "Component/PlayerPositionResetter.hpp"
#include "Component/PlayerSoundProducer.hpp"
#include "Component/SpawnPickupOnDeath.hpp"
#include "Component/SwitchSceneOnEnemiesKilled.hpp"
#include "Component/TextComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Component/TimedKill.hpp"
#include "Component/WrapAroundScreenComponent.hpp"
#include "Component/ZenChanAnimationComponent.hpp"
#include "Manager/MainMenu.hpp"
#include "Event/Sdbm.hpp"
#include "glm/gtx/norm.inl"
#include "Manager/GameOver.hpp"
#include "Manager/InGame.hpp"
#include "Manager/NameSelector.hpp"
#include "Render/ResourceManager.hpp"
#include "UI/HighScoreUiComponent.hpp"
#include "UI/LiveUiComponent.hpp"

bool game::StagesManager::LoadNextStageFromJson()
{
	if (m_currentStage == STAGE_COUNT) return false;

	LoadStageFromJson(m_currentStage+1);
	return true;
}

void game::StagesManager::LoadStageFromJson(int32_t stageNumber, bool preserveKeepAlive)
{
	m_currentStage = stageNumber;
	LoadSceneFromJson(std::format("Stages/Stage{}", stageNumber), preserveKeepAlive);
}

void game::StagesManager::LoadSceneFromJson(std::string const &sceneName, bool preserveKeepAlive)
{
	using json = nlohmann::json;

	m_scene = &dae::SceneManager::GetInstance().CreateScene(preserveKeepAlive);

	if (!preserveKeepAlive)
	{
		m_players.clear();
		m_playerLivesNumber = 0;
		m_playerScoreNumber = 0;
	}

	std::ifstream jsonFile{dae::ResourceManager::GetInstance().LoadFile(sceneName + ".json")};
	if (!jsonFile.is_open())
	{
		throw std::runtime_error(
			std::string("Failed to load Scene: ") + sceneName
		);
	}

	const json &sceneJson{json::parse(jsonFile)};

	m_scaleFactor = sceneJson["scalar"].get<float>();

	for (const auto &item : sceneJson["prefabs"])
	{
		if (auto newItem{PrefabLoader(item)})
		{
			m_scene->MoveInto(std::move(newItem));
		}
	}
}

void game::StagesManager::SpawnBubble(ProjectilePrefabData const &data, glm::vec2 const &spriteOffset) const
{
	auto bubblePrefab{std::make_unique<dae::GameObject>()};

	bubblePrefab->SetLocalPosition({
		data.location + PROJECTILE_OFFSET,
		0.0f
	});

	bubblePrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*bubblePrefab,
		dae::ResourceManager::GetInstance().LoadTexture("Player/PlayerBubble.png"),
		m_scaleFactor,
		glm::vec2{16.0f, 16.0f},
		spriteOffset
	));

	bubblePrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*bubblePrefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("BUBBLE")));
	bubblePrefab->AddComponent(std::make_unique<BubbleComponent>(*bubblePrefab, data.facingLeft));
	bubblePrefab->AddComponent(std::make_unique<BubbleExpireTimer>(*bubblePrefab, 8.0f));
	bubblePrefab->AddComponent(std::make_unique<FlickerComponent>(*bubblePrefab));
	bubblePrefab->AddComponent(std::make_unique<TimedKill>(*bubblePrefab, 8.2f));

	m_scene->Add(std::move(bubblePrefab));
}

void game::StagesManager::SpawnBoulder(ProjectilePrefabData const& data) const
{
	auto boulderPrefab{std::make_unique<dae::GameObject>()};

	boulderPrefab->SetLocalPosition({
		data.location + PROJECTILE_OFFSET,
		0.0f
	});

	boulderPrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*boulderPrefab,
		dae::ResourceManager::GetInstance().LoadTexture("Enemies/MightaBoulder.png"),
		m_scaleFactor
	));

	boulderPrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*boulderPrefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("ENEMY")));
	boulderPrefab->AddComponent(std::make_unique<BoulderComponent>(*boulderPrefab, data.facingLeft));

	m_scene->Add(std::move(boulderPrefab));
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
		PICKUP_SPRITE_OFFSETS.at(data.worth)
	));

	pickupPrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*pickupPrefab, glm::vec2{64.0f, 64.0f}, dae::sdbm_hash("PICKUP")));
	pickupPrefab->AddComponent(std::make_unique<PickupComponent>(*pickupPrefab, data.worth));
	pickupPrefab->AddComponent(std::make_unique<FlickerComponent>(*pickupPrefab));
	pickupPrefab->AddComponent(std::make_unique<TimedKill>(*pickupPrefab, 8.0f));

	m_scene->Add(std::move(pickupPrefab));
}

dae::GameObject *game::StagesManager::SpawnDeadEnemy(ProjectilePrefabData const &data, glm::vec2 const &spriteOffset) const
{
	auto deadEnemyPrefab{std::make_unique<dae::GameObject>()};
	auto const newDeadEnemy{deadEnemyPrefab.get()};

	deadEnemyPrefab->SetLocalPosition({
		data.location,
		0.0f
	});

	deadEnemyPrefab->AddComponent(std::make_unique<dae::TextureComponent>(
		*deadEnemyPrefab,
		dae::ResourceManager::GetInstance().LoadTexture("Enemies/DeadEnemies.png"),
		m_scaleFactor,
		glm::vec2{16.0f, 16.0f},
		spriteOffset
	));

	deadEnemyPrefab->AddComponent(std::make_unique<dae::ColliderComponent>(*deadEnemyPrefab, glm::vec2{64.0f, 64.0f}, dae::sdbm_hash("DEAD_ENEMY")));
	deadEnemyPrefab->AddComponent(std::make_unique<PhysicsComponent>(*deadEnemyPrefab, data.facingLeft, 520.0f * 2.0f, 280.0f));
	deadEnemyPrefab->AddComponent(std::make_unique<FallingDeadEnemy>(*deadEnemyPrefab, data.facingLeft));
	deadEnemyPrefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*deadEnemyPrefab));

	m_scene->Add(std::move(deadEnemyPrefab));

	return newDeadEnemy;
}

void game::StagesManager::AddScoreDisplay(GameRecord const& record, float height) const
{
	auto scoreDisplay{std::make_unique<dae::GameObject>()};
	auto const recordText{std::format("{}{: 15}", record.Name, record.Score)};

	scoreDisplay->SetLocalPosition({
		88.0f * m_scaleFactor,
		height * m_scaleFactor,
		0.0f
	});

	scoreDisplay->AddComponent(std::make_unique<dae::TextureComponent>(*scoreDisplay));
	scoreDisplay->AddComponent(std::make_unique<dae::TextComponent>(*scoreDisplay, recordText, m_uiFont));

	m_scene->Add(std::move(scoreDisplay));
}

void game::StagesManager::AttachGui(std::unique_ptr<dae::GuiWindow> &&gui) const
{
	m_scene->AddGui(std::move(gui));
}

std::vector<game::PlayerData> const& game::StagesManager::GetPlayers() const
{
	return m_players;
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

// TODO not very extendable, a system where JSON files contain the needed components & properties for said components would be a better system
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
		auto threshold{data["threshold"].get<int32_t>()};
		if (GameState::GetInstance().CurrentType == GameType::Versus) ++threshold;

		prefab->AddComponent(std::make_unique<SwitchSceneOnEnemiesKilled>(*prefab, threshold));
		prefab->AddComponent(std::make_unique<InGame>(*prefab));
	}

	else if (prefabName == "player") {
		if (m_players.size() == static_cast<size_t>(GameState::GetInstance().GetMaxPlayersForGame())) return nullptr;
		if (m_players.size() == 1 && GameState::GetInstance().GetPlayerTwoTypeForGame() != PlayerTwoType::Bob) return nullptr;

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("Player/PlayerSprites.png"),
			m_scaleFactor,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("PLAYER")));
		prefab->AddComponent(std::make_unique<PhysicsComponent>(*prefab, !m_players.empty()));
		prefab->AddComponent(std::make_unique<LivesScoreComponent>(*prefab));
		prefab->AddComponent(std::make_unique<PlayerInputComponent>(*prefab, static_cast<int>(m_players.size()), false));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &PLAYER_ANIMATIONS.at(!m_players.empty() ? PlayerAnimationStates::IdleLeft : PlayerAnimationStates::IdleRight), 1.0f/3.0f, glm::vec2{static_cast<float>(m_players.size()) * 4.0f, 0.0f} ));
		prefab->AddComponent(std::make_unique<PlayerAnimationComponent>(*prefab));
		prefab->AddComponent(std::make_unique<PlayerSoundProducer>(*prefab));
		prefab->AddComponent(std::make_unique<PlayerPositionResetter>(*prefab));
		prefab->AddComponent(std::make_unique<FlickerComponent>(*prefab));
		prefab->AddComponent(std::make_unique<DisablePlayerOnZeroLives>(*prefab));

		prefab->KeepAlive = true;
		m_players.emplace_back(prefab.get(), prefab->GetComponent<LivesScoreComponent>());
	}

	else if (prefabName == "enemy-player")
	{
		if (GameState::GetInstance().CurrentType != GameType::Versus) return nullptr;

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("Enemies/Mighta.png"),
			m_scaleFactor,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("ENEMY")));
		prefab->AddComponent(std::make_unique<PhysicsComponent>(*prefab, true, 320.0f));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &MIGHTA_ANIMATIONS.at(MightaAnimationStates::WalkingLeft), 1.0f / 6.0f));
		prefab->AddComponent(std::make_unique<PlayerInputComponent>(*prefab, static_cast<int>(m_players.size()), true));
		prefab->AddComponent(std::make_unique<SpawnPickupOnDeath>(*prefab, 200));
		prefab->AddComponent(std::make_unique<MightaAnimationComponent>(*prefab));
		prefab->AddComponent(std::make_unique<CapturableComponent>(*prefab, glm::vec2{1.0f, 0.0f}, true));
	}

	else if (prefabName == "zen-chan-enemy")
	{
		bool facingLeft{data["facingLeft"].get<bool>()};

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("Enemies/ZenChan.png"),
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
		prefab->AddComponent(std::make_unique<SpawnPickupOnDeath>(*prefab, 100));
		prefab->AddComponent(std::make_unique<CapturableComponent>(*prefab, glm::vec2{0.0f, 0.0f}, true));
	}

	else if (prefabName == "mighta-enemy")
	{
		bool facingLeft{data["facingLeft"].get<bool>()};

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture("Enemies/Mighta.png"),
			m_scaleFactor,
			glm::vec2{16.0f, 16.0f},
			glm::vec2{static_cast<float>(m_players.size()), 0.0f})
		);

		prefab->AddComponent(std::make_unique<dae::ColliderComponent>(*prefab, glm::vec2{64.0f,64.0f}, dae::sdbm_hash("ENEMY")));
		prefab->AddComponent(std::make_unique<PhysicsComponent>(*prefab, facingLeft, 320.0f));
		prefab->AddComponent(std::make_unique<WrapAroundScreenComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AnimationComponent>(*prefab, &MIGHTA_ANIMATIONS.at(facingLeft ? MightaAnimationStates::WalkingLeft : MightaAnimationStates::WalkingRight), 1.0f / 6.0f));
		prefab->AddComponent(std::make_unique<PlatformAiMovement>(*prefab, facingLeft ? PlatformAiActions::WalkingLeft : PlatformAiActions::WalkingRight));
		prefab->AddComponent(std::make_unique<SpawnPickupOnDeath>(*prefab, 200));
		prefab->AddComponent(std::make_unique<MightaAnimationComponent>(*prefab));
		prefab->AddComponent(std::make_unique<AttackIfPlayerAtSameHeight>(*prefab));
		prefab->AddComponent(std::make_unique<CapturableComponent>(*prefab, glm::vec2{1.0f, 0.0f}, true));
	}

	else if (prefabName == "high-score")
	{
		auto textComp{std::make_unique<dae::TextComponent>(*prefab, "000000000", m_uiFont)};
		textComp->SetColor({255, 0, 0, 255});

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(*prefab));
		prefab->AddComponent(std::move(textComp));
		prefab->AddComponent(std::make_unique<HighScoreUiComponent>(*prefab));
	}

	else if (prefabName == "player-score")
	{
		if (m_playerScoreNumber >= static_cast<int>(m_players.size())) return prefab;

		prefab->AddComponent(std::make_unique<dae::TextureComponent>(*prefab));
		prefab->AddComponent(std::make_unique<dae::TextComponent>(*prefab, "000000000", m_uiFont));
		prefab->AddComponent(std::make_unique<ScoreUiComponent>(*prefab, m_players[m_playerScoreNumber].object));

		prefab->KeepAlive = true;
		++m_playerScoreNumber;
	}

	else if (prefabName == "player-lives")
	{
		if (m_playerLivesNumber >= static_cast<int>(m_players.size())) return prefab;

		prefab->AddComponent(std::make_unique<LiveUiComponent>(*prefab, m_players[m_playerLivesNumber].object, m_playerLivesNumber == 0));

		prefab->KeepAlive = true;
		++m_playerLivesNumber;
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

	else if (prefabName == "image")
	{
		auto const textureName{data["image"].get<std::string>()};
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(
			*prefab,
			dae::ResourceManager::GetInstance().LoadTexture(textureName),
			m_scaleFactor
		));
	}

	else if (prefabName == "text")
	{
		auto const text{data["text"].get<std::string>()};
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(*prefab));
		prefab->AddComponent(std::make_unique<dae::TextComponent>(*prefab, text, m_uiFont));
	}

	else if (prefabName == "name-selector") {
		prefab->AddComponent(std::make_unique<dae::TextureComponent>(*prefab));
		prefab->AddComponent(std::make_unique<dae::TextComponent>(*prefab, "AAA", m_uiFont));
		prefab->AddComponent(std::make_unique<NameSelector>(*prefab));
	}

	else if (prefabName == "main-menu-manager") {
		prefab->AddComponent(std::make_unique<MainMenu>(*prefab));
	}

	else if (prefabName == "game-over-manager") {
		prefab->AddComponent(std::make_unique<GameOver>(*prefab));
	}

	return prefab;
}

game::StagesManager::StagesManager()
	: m_uiFont(dae::ResourceManager::GetInstance().LoadFont("UI/Pixel_NES.otf", 24))
{
}
