#include <filesystem>

#if (_WIN32 or _WIN64)
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

#if (not NDEBUG) and __has_include(<vld.h>)
#include <vld.h>
#endif

#include "InstructionWindow.hpp"
#include "Prefab/StagesManager.hpp"
#include "Audio/AudioQueue.hpp"
#include "Event/Sdbm.hpp"
#include "Minigin.hpp"

namespace fs = std::filesystem;

static void load()
{
	dae::AudioQueue::LoadSound(dae::sdbm_hash("PlayerJump"), "Audio/PlayerJump.wav");
	dae::AudioQueue::LoadSound(dae::sdbm_hash("Pickup"), "Audio/Pickup.wav");
	dae::AudioQueue::LoadSound(dae::sdbm_hash("PlayerShoot"), "Audio/PlayerShoot.wav");

	game::StagesManager::GetInstance().LoadSceneFromJson("MainMenu");
	game::StagesManager::GetInstance().AttachGui(std::make_unique<game::InstructionWindow>());
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
