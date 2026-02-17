#include "Time.hpp"

#include <chrono>
#include <thread>

namespace Time
{
    static std::chrono::high_resolution_clock::time_point current_time{};
    static std::chrono::high_resolution_clock::time_point last_time{};

    constexpr uint16_t ms_per_frame{16};
    static float delta_time{};
}

float Time::get_delta_time()
{
    return delta_time;
}

void Time::pre_update()
{
    current_time = std::chrono::high_resolution_clock::now();
    delta_time = std::chrono::duration<float>(current_time - last_time).count();
    last_time = current_time;
}


void Time::post_update()
{
    const auto sleep_time = current_time + std::chrono::milliseconds(ms_per_frame) - std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(sleep_time);
}
