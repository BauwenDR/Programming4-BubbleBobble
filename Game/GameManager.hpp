#ifndef MINIGIN_GAMEMANAGER_HPP
#define MINIGIN_GAMEMANAGER_HPP
#include <cstdint>
#include <string>
#include <vector>

#include "Singleton.hpp"

namespace game
{
    enum class GameType : uint8_t
    {
        Single,
        Coop,
        Versus
    };

    class GameManager final : public dae::Singleton<GameManager>
    {
    public:
        GameType CurrentType{};
        int32_t TotalScore{};
        int32_t HighScore{};

        std::vector<int32_t> GetHighScores();
        void SaveScore(std::string_view const &name);
        void Destroy();

    private:
        friend class Singleton;
        GameManager();
    };
}

#endif //MINIGIN_GAMEMANAGER_HPP
