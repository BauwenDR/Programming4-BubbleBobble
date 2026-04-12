#include <filesystem>

#include "Animations/PlayerAnimations.hpp"
#include "Animations/ZenChanAnimation.hpp"
#include "Component/AnimationComponent.hpp"
#include "Component/PlayerAnimationComponent.hpp"
#include "Component/WrapAroundScreenComponent.hpp"
#include "Component/ZenChanAnimationComponent.hpp"
#include "Prefab/PrefabManager.hpp"
namespace fs = std::filesystem;

#if (_WIN32 or _WIN64)
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

#if _DEBUG and __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Component/TextComponent.hpp"
#include "SceneManager.hpp"
#include "Minigin.hpp"

static void load()
{
	game::PrefabManager::GetInstance().LoadSceneFromJson("Stage1");
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
