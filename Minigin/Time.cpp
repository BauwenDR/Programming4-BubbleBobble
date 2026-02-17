#include "Time.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace Time
{
    static std::chrono::high_resolution_clock::time_point current_time{};
    static std::chrono::high_resolution_clock::time_point last_time{};

    constexpr uint32_t us_per_frame{16500};

    static float delta_time{};

    constexpr float fps_update_interval_seconds{1.0f};
    static float last_fps{0.0f};
    static float ms_since_last_fps_calculation{0.0f};
}

float Time::get_delta_time()
{
    return delta_time;
}

float Time::get_frame_rate()
{
    return last_fps;
}

void Time::pre_update()
{
    current_time = std::chrono::high_resolution_clock::now();
    delta_time = std::chrono::duration<float>(current_time - last_time).count();
    last_time = current_time;

    ms_since_last_fps_calculation += delta_time;
    if (ms_since_last_fps_calculation > fps_update_interval_seconds)
    {
        std::cout << last_fps << std::endl;
        ms_since_last_fps_calculation = 0.0f;
        last_fps = 1.f / delta_time;
    }
}

void Time::post_update()
{
    const auto sleep_time = current_time + std::chrono::microseconds(us_per_frame) - std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(sleep_time);
}
