#include "PlottingWindows.hpp"

#include <algorithm>
#include <chrono>
#include <implot.h>
#include <memory>
#include <numeric>

struct BigObject
{
    int lottaStorage[16]{};
    int id{1};
};

struct SmallObject
{
    int* lottaStorage{};
    int id{1};
};


template <typename T, int size>
void TrashCache(const int sampleCount, std::vector<int> &timings)
{
    constexpr int POWERS_OF_TWO{11};
    std::unique_ptr<std::array<T, size>> buffer = std::make_unique<std::array<T, size>>();
    std::vector<std::vector<int64_t>> elapsedTimes(POWERS_OF_TWO);

    timings.clear();
    timings.reserve(POWERS_OF_TWO);

    for (int repeatCount{0}; repeatCount < sampleCount; ++repeatCount)
    {
        for(int powerOfTwo{0}; powerOfTwo < POWERS_OF_TWO; powerOfTwo += 1) {
            const int stepSize{1 << powerOfTwo};
            auto start{std::chrono::high_resolution_clock::now()};
            for(int index{0}; index < size; index += stepSize) {

                // If normal integral type multiply by 2, if one of the other 2 structs we want to increase the ID
                if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
                {
                    (*buffer)[index] *= 2;
                }

                if constexpr (std::is_same_v<T, BigObject> || std::is_same_v<T, SmallObject>)
                {
                    (*buffer)[index].id *= 2;
                }
            }

            auto end{std::chrono::high_resolution_clock::now()};
            elapsedTimes[powerOfTwo].push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }
    }

    for (int index{0}; index < POWERS_OF_TWO; ++index)
    {
        const auto [min, max]{std::ranges::minmax_element(elapsedTimes[index])};

        int timingsCount{sampleCount};
        int64_t sum{std::accumulate(elapsedTimes[index].begin(), elapsedTimes[index].end(), 0LL)};

        if (elapsedTimes[index].size() > 3)
        {
            sum -= *min + *max;
            timingsCount -=2;
        }

        timings.push_back(static_cast<int>(sum / timingsCount));
    }
}

void game::ExerciseOneWindow::DrawWindowContent()
{
    ImGui::InputInt("Samples", &m_samples);
    if (ImGui::Button("Thrash the cache"))
    {
        TrashCache<int, BUFFER_SIZE>(m_samples, m_y_axis);
    }

    if (!m_y_axis.empty())
    {
        ImPlot::BeginPlot("Exercise one", ImVec2(400, 200), ImPlotFlags_NoFrame | ImPlotFlags_NoLegend | ImPlotFlags_NoTitle);
        ImPlot::PlotLine("Data", m_x_axis.data(), m_y_axis.data(), static_cast<int>(m_x_axis.size()));
        ImPlot::EndPlot();
    }
}

void game::ExerciseTwoWindow::DrawWindowContent()
{
    ImGui::InputInt("Samples", &m_samples);
    if (ImGui::Button("Thrash the cache with Big GameObject"))
    {
        TrashCache<BigObject, BUFFER_SIZE>(m_samples, m_bigYAxis);
    }

    if (ImGui::Button("Thrash the cache with Small GameObject"))
    {
        TrashCache<SmallObject, BUFFER_SIZE>(m_samples, m_smallYAxis);
    }

    if (!m_bigYAxis.empty() || !m_smallYAxis.empty())
    {
        ImPlot::BeginPlot("Exercise two combined", ImVec2(400, 200), ImPlotFlags_NoFrame | ImPlotFlags_NoLegend | ImPlotFlags_NoTitle);

        if (!m_bigYAxis.empty())
        {
            ImPlot::PlotLine("Data Big", m_xAxis.data(), m_bigYAxis.data(), static_cast<int>(m_xAxis.size()));
        }

        if (!m_smallYAxis.empty())
        {
            ImPlot::PlotLine("Data Small", m_xAxis.data(), m_smallYAxis.data(), static_cast<int>(m_xAxis.size()));
        }

        ImPlot::EndPlot();
    }
}
