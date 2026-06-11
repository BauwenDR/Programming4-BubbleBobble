#include "GameManager.hpp"

void game::GameManager::SaveScore(std::string_view const &) {
}

int game::GameManager::GetMaxPlayersForGame() const {
    return CurrentType == GameType::Single ? 1 : 2;
}

game::PlayerTwoType game::GameManager::GetPlayerTwoTypeForGame() const {
    return CurrentType == GameType::Coop ? PlayerTwoType::Bob : PlayerTwoType::Maita;
}

game::GameManager::GameManager() = default;
