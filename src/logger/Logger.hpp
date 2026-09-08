#ifndef LOGGER_HPP
# define LOGGER_HPP
#include <array>
# include <iostream>
# include <iomanip>
#include <optional>
#include <string_view>

enum class LogLevel {
    None,
    Error,
    Progress,
    Info,
    Debug
};

namespace Logger {
    inline LogLevel currentLevel        =   LogLevel::Info;
    inline int      lastPercentPrinted  =   -1;

    inline constexpr std::array<std::pair<std::string_view, LogLevel>, 5> logLevelsNames = {{
        {"none",     LogLevel::None},
        {"progress", LogLevel::Progress},
        {"info",     LogLevel::Info},
        {"error",    LogLevel::Error},
        {"debug",    LogLevel::Debug},
    }};

    inline std::optional<LogLevel> getLogLevelFromName(std::string_view name) {
        for (const auto &[str, level] : logLevelsNames) {
            if (str == name) {
                return level;
            }
        }
        return std::nullopt;
    }

    inline void setLogLevel(LogLevel level) { currentLevel = level; }

    template<typename... Args>
    void log(Args&&... args) {
        (std::cout << ... << args) << "\n";
    }
    
    template<typename... Args>
    void error(Args&&... args) {
        if (currentLevel >= LogLevel::Error) {
            (std::cerr << ... << args) << "\n";
        }
    }

    inline void progress(size_t current, size_t total) {
        constexpr int increment = 5;
        constexpr int barWidth = 20;  // 20 segmentos = cada uno vale 5%

        if (currentLevel != LogLevel::Progress || total == 0) {
            return;
        }

        int percentage = static_cast<int>(((current + 1) * 100) / (total));
        percentage = (percentage / increment) * increment;

        if (percentage != lastPercentPrinted) {
            int filled = percentage * barWidth / 100;

            std::cout << "\r[";
            for (int i = 0; i < barWidth; ++i) {
                std::cout << (i < filled ? "█" : " ");
            }
            std::cout << "] " << std::setw(3) << percentage << "% completed." << std::flush;

            lastPercentPrinted = percentage;

            if (percentage >= 100) {
                std::cout << '\n';
                lastPercentPrinted = -1;
            }
        }
    }

    template<typename... Args>
    void info(Args&&... args) {
        if (currentLevel >= LogLevel::Info) {
            (std::cout << ... << args) << "\n";
        }
    }

    template<typename... Args>
    void debug(Args&&... args) {
        if (currentLevel >= LogLevel::Debug) {
            (std::cout << ... << args) << "\n";
        }
    }

}

#endif