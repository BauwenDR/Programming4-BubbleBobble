#include "GameState.hpp"

#include <iostream>

#ifndef __emscripten__
#define SQLITE_CORE
#include <sqlite3.h>
#endif

#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"

std::vector<game::GameRecord> game::GameState::GetHighScores()
{
    std::vector<GameRecord> records{};
#ifndef __emscripten__
    sqlite3* db{};

    if (sqlite3_open("game_records.db", &db) != SQLITE_OK)
    {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return records;
    }

    std::string const sql = "SELECT playerName, score FROM records ORDER BY score DESC LIMIT 5;";
    sqlite3_stmt* stmt{};

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return records;
    }

    // Execute the statement and retrieve results
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        auto const name{sqlite3_column_text(stmt, 0)};
        auto const score{sqlite3_column_int(stmt, 1)};

        std::string const nameString = name ? reinterpret_cast<const char*>(name) : std::string{};
        records.emplace_back(nameString, score);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
#endif

    return records;
}

void game::GameState::SaveScore([[maybe_unused]] std::string_view const& name) const
{
#ifndef __emscripten__
    sqlite3* db{};

    // Open the database
    if (sqlite3_open("game_records.db", &db) != SQLITE_OK)
    {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const std::string sql{"INSERT INTO records (playerName, score) VALUES (?, ?);"};
    sqlite3_stmt* stmt{};

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, name.data(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, TotalScore);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
#endif
}

void game::GameState::LoadHighScore()
{
    auto records{GetHighScores()};

    if (records.size() > 0)
    {
        HighScore = records.front().Score;
    }
}

int game::GameState::GetMaxPlayersForGame() const
{
    return CurrentType == GameType::Single ? 1 : 2;
}

game::PlayerTwoType game::GameState::GetPlayerTwoTypeForGame() const
{
    return CurrentType == GameType::Coop ? PlayerTwoType::Bob : PlayerTwoType::Maita;
}

void game::GameState::SetScore(int totalScore)
{
    TotalScore = totalScore;

    if (totalScore > HighScore)
    {
        HighScore = totalScore;
        dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("new_high_score"));
    }
}

game::GameState::GameState()
{
#ifndef __emscripten__
    sqlite3* db{};

    if (sqlite3_open("game_records.db", &db) != SQLITE_OK)
    {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const auto createTableSQL{R"(
            CREATE TABLE IF NOT EXISTS records (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                playerName TEXT NOT NULL,
                score INTEGER NOT NULL
            );
        )"};

    char* errorMessage{};
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_free(errorMessage);
    }

    sqlite3_close(db);
#endif
}
