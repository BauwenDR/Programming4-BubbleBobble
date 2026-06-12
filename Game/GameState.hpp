#ifndef MINIGIN_GAMESTATE_HPP
#define MINIGIN_GAMESTATE_HPP
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

    enum class PlayerTwoType : uint8_t
    {
        Bob,
        Maita
    };

    class GameState final : public dae::Singleton<GameState>
    {
    public:
        GameType CurrentType{};
        int32_t TotalScore{};
        int32_t HighScore{};

        // std::vector<int32_t> GetHighScores();
        void SaveScore(std::string_view const &name);

        int GetMaxPlayersForGame() const;
        PlayerTwoType GetPlayerTwoTypeForGame() const;


    private:
        friend class Singleton;
        GameState();
    };
}

#endif //MINIGIN_GAMESTATE_HPP
