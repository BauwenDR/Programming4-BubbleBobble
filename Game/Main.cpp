#include <filesystem>

#include "Prefab/PrefabManager.hpp"
namespace fs = std::filesystem;

#if (_WIN32 or _WIN64)
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

#if _DEBUG and __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Audio/AudioQueue.hpp"
#include "Event/Sdbm.hpp"
#include "SceneManager.hpp"
#include "Minigin.hpp"

static void load()
{
	// TODO move these into JSON file
	dae::AudioQueue::LoadSound(dae::sdbm_hash("PlayerJump"), "Audio/PlayerJump.wav");
	dae::AudioQueue::LoadSound(dae::sdbm_hash("Pickup"), "Audio/Pickup.wav");

	game::PrefabManager::GetInstance().LoadSceneFromJson("Stage3");
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
