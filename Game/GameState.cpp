#include "GameState.hpp"

void game::GameState::SaveScore(std::string_view const &) {
}

int game::GameState::GetMaxPlayersForGame() const {
    return CurrentType == GameType::Single ? 1 : 2;
}

game::PlayerTwoType game::GameState::GetPlayerTwoTypeForGame() const {
    return CurrentType == GameType::Coop ? PlayerTwoType::Bob : PlayerTwoType::Maita;
}

game::GameState::GameState() = default;
