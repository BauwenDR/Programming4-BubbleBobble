#ifndef MINIGIN_PREFABMANAGER_HPP
#define MINIGIN_PREFABMANAGER_HPP
#include <memory>

#include <nlohmann/json.hpp>
#include <glm/vec3.hpp>

#include "Prefabs.hpp"
#include "Singleton.hpp"

namespace dae
{
    class GuiWindow;
    class Font;
    class Scene;
}

namespace dae
{
    class ColliderComponent;
    class GameObject;
}

namespace game
{
    class LivesScoreComponent;

    struct PlayerData
    {
        dae::GameObject* object{};
        LivesScoreComponent *m_livesScore{};
    };

    class StagesManager final : public dae::Singleton<StagesManager>
    {
    public:
        void LoadNextStageFromJson();
        void LoadStageFromJson(int32_t stageNumber);

        void LoadSceneFromJson(std::string const & sceneName, bool preserveKeepAlive = true);

        void SpawnBubble(ProjectilePrefabData const &data) const;
        void SpawnPickup(PickupPrefabData const &data) const;

        void AttachGui(std::unique_ptr<dae::GuiWindow> &&gui) const;

        [[nodiscard]] PlayerData GetClosestActivePlayer(glm::vec3 const &searchPos) const;

    private:
        friend class Singleton;

        std::unique_ptr<dae::GameObject> PrefabLoader(nlohmann::json const &data);

        const std::shared_ptr<dae::Font> m_uiFont{};
        dae::Scene *m_scene{};
        std::vector<PlayerData> m_players{};

        int32_t m_currentStage{1};
        float m_scaleFactor{1.0f};
        int8_t m_maxPlayers{2};

        StagesManager();
    };
}

#endif //MINIGIN_PREFABMANAGER_HPP