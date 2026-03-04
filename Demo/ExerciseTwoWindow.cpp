#include "ExerciseTwoWindow.hpp"

#include <algorithm>
#include <chrono>
#include <imgui.h>
#include <implot.h>
#include <numeric>

#include "Transform.hpp"

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

void ExerciseTwoWindow::DrawWindowContent()
{
    ImGui::InputInt("Samples", &m_samples);
    if (ImGui::Button("Thrash the cache with Big GameObject"))
    {
        TrashCacheBig();
    }

    if (ImGui::Button("Thrash the cache with Small GameObject"))
    {
        TrashCacheSmall();
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

// Quite a bit of duplicated code from this point on...
void ExerciseTwoWindow::TrashCacheBig()
{
    const auto bigArray{new BigObject[BUFFER_SIZE]}; // size of 2^22

    std::vector<std::vector<long long>> elapsedTimes(POWERS_OF_TWO);
    for (int repeatCount{0}; repeatCount < m_samples; ++repeatCount)
    {
        for(int powerOfTwo{0}; powerOfTwo < POWERS_OF_TWO; powerOfTwo += 1) {
            const int stepSize{1 << powerOfTwo};
            auto start{std::chrono::high_resolution_clock::now()};
            for(int index{0}; index < BUFFER_SIZE; index += stepSize) {
                bigArray[index].id *= 2;
            }

            auto end{std::chrono::high_resolution_clock::now()};
            elapsedTimes[powerOfTwo].push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }
    }

    m_bigYAxis.clear();
    for (int index{0}; index < POWERS_OF_TWO; ++index)
    {
        const auto [min, max]{std::ranges::minmax_element(elapsedTimes[index])};
        long sum{std::accumulate(elapsedTimes[index].begin(), elapsedTimes[index].end(), 0L)};

        if (elapsedTimes[index].size() > 3)
        {
            sum -= *min + *max;
        }

        m_bigYAxis.push_back(static_cast<int>(sum));
    }

    delete[] bigArray;
}

void ExerciseTwoWindow::TrashCacheSmall()
{
    const auto bigArray{new SmallObject[BUFFER_SIZE]}; // size of 2^22

    std::vector<std::vector<long long>> elapsedTimes(POWERS_OF_TWO);
    for (int repeatCount{0}; repeatCount < m_samples; ++repeatCount)
    {
        for(int powerOfTwo{0}; powerOfTwo < POWERS_OF_TWO; powerOfTwo += 1) {
            const int stepSize{1 << powerOfTwo};
            auto start{std::chrono::high_resolution_clock::now()};
            for(int index{0}; index < BUFFER_SIZE; index += stepSize) {
                bigArray[index].id *= 2;
            }

            auto end{std::chrono::high_resolution_clock::now()};
            elapsedTimes[powerOfTwo].push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }
    }

    m_smallYAxis.clear();
    for (int index{0}; index < POWERS_OF_TWO; ++index)
    {
        const auto [min, max]{std::ranges::minmax_element(elapsedTimes[index])};
        long sum{std::accumulate(elapsedTimes[index].begin(), elapsedTimes[index].end(), 0L)};

        if (elapsedTimes[index].size() > 3)
        {
            sum -= *min + *max;
        }

        m_smallYAxis.push_back(static_cast<int>(sum));
    }

    delete[] bigArray;
}
