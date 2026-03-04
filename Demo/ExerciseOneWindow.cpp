#include "ExerciseOneWindow.hpp"

#include <algorithm>
#include <chrono>
#include <imgui.h>
#include <implot.h>
#include <numeric>
#include <vector>

void ExerciseOneWindow::DrawWindowContent()
{
    ImGui::InputInt("Samples", &m_samples);
    if (ImGui::Button("Thrash the cache"))
    {
        TrashCache();
        std::cout << m_samples << "\n";
    }

    if (!m_y_axis.empty())
    {
        ImPlot::BeginPlot("Exercise one", ImVec2(400, 200), ImPlotFlags_NoFrame | ImPlotFlags_NoLegend | ImPlotFlags_NoTitle);
        ImPlot::PlotLine("Data", m_x_axis.data(), m_y_axis.data(), static_cast<int>(m_x_axis.size()));
        ImPlot::EndPlot();
    }
}

void ExerciseOneWindow::TrashCache()
{
    const auto bigArray{new int[BUFFER_SIZE]}; // size of 2^26
    std::fill_n(bigArray, BUFFER_SIZE, 1);

    std::vector<std::vector<long>> elapsedTimes(POWERS_OF_TWO);
    for (int repeatCount{0}; repeatCount < m_samples; ++repeatCount)
    {
        for(int powerOfTwo{0}; powerOfTwo < POWERS_OF_TWO; powerOfTwo += 1) {
            const int stepSize{1 << powerOfTwo};
            auto start{std::chrono::high_resolution_clock::now()};
            for(int index{0}; index < BUFFER_SIZE; index += stepSize) {
                bigArray[index] *= 2;
            }

            auto end{std::chrono::high_resolution_clock::now()};
            elapsedTimes[powerOfTwo].push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }
    }

    m_y_axis.clear();
    for (int index{0}; index < POWERS_OF_TWO; ++index)
    {
        const auto [min, max]{std::ranges::minmax_element(elapsedTimes[index])};
        long sum{std::accumulate(elapsedTimes[index].begin(), elapsedTimes[index].end(), 0L)};

        if (elapsedTimes[index].size() > 3)
        {
            sum -= *min + *max;
        }

        m_y_axis.push_back(static_cast<int>(sum));
    }

    delete[] bigArray;
}
