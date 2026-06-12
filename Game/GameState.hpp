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

    struct GameRecord
    {
        std::string Name;
        int32_t Score;
    };

    class GameState final : public dae::Singleton<GameState>
    {
    public:
        GameType CurrentType{};
        int32_t TotalScore{};
        int32_t HighScore{};

        std::vector<GameRecord> GetHighScores();
        void SaveScore(std::string_view const &name) const;

        void LoadHighScore();
        int GetMaxPlayersForGame() const;
        PlayerTwoType GetPlayerTwoTypeForGame() const;
        void SetScore(int totalScore);

    private:
        friend class Singleton;
        GameState();
    };
}

#endif //MINIGIN_GAMESTATE_HPP
