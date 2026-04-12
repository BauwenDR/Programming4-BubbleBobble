#ifndef MINIGIN_PREFABMANAGER_HPP
#define MINIGIN_PREFABMANAGER_HPP
#include <memory>

#include <nlohmann/json.hpp>

#include "Prefabs.hpp"
#include "Singleton.hpp"

namespace dae
{
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
        dae::GameObject* object;
        LivesScoreComponent *m_livesScore;
    };

    class PrefabManager final : public dae::Singleton<PrefabManager>
    {
    public:
        void LoadSceneFromJson(std::string const & sceneName);

        void SpawnPickup(PickupPrefabData const &data) const;
        // void SpawnBarronEnemy() const;

        [[nodiscard]] std::vector<PlayerData> const &GetPlayers() const;
    private:
        friend class Singleton;

        std::unique_ptr<dae::GameObject> PrefabLoader(nlohmann::json const &data);

        const std::shared_ptr<dae::Font> m_uiFont{};
        dae::Scene *m_scene{};
        std::vector<PlayerData> m_players{};

        PrefabManager();
    };
}

#endif //MINIGIN_PREFABMANAGER_HPP