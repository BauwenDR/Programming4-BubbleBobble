#ifndef MINIGIN_IMGUIWINDOW_HPP
#define MINIGIN_IMGUIWINDOW_HPP

#include <string>

namespace dae
{
    class GuiWindow
    {
    public:
        void DrawWindow();

        virtual ~GuiWindow() = default;

        GuiWindow(const GuiWindow &other) = delete;
        GuiWindow(GuiWindow &&other) noexcept = delete;
        GuiWindow & operator=(const GuiWindow &other) = delete;
        GuiWindow & operator=(GuiWindow &&other) noexcept = delete;

    protected:
        explicit GuiWindow(const std::string &windowName);

        std::string m_windowName{};
        bool m_showMenu{};
    private:
        virtual void DrawWindowContent() = 0;
    };
}

#endif //MINIGIN_IMGUIWINDOW_HPP