#ifndef LOGGER_HPP
# define LOGGER_HPP
# include <iostream>
# include <iomanip>
#include <string>
#include <unordered_map>

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

    inline const std::unordered_map<std::string, LogLevel> logLevelsNames = {
        {"none", LogLevel::None},
        {"progress", LogLevel::Progress},
        {"info", LogLevel::Info},
        {"error", LogLevel::Error},
        {"debug", LogLevel::Debug},
    };

    class LogLevelNotFoundException : public std::exception {
        private:
            std::string _message;
        public:
            LogLevelNotFoundException(const std::string &levelName) : _message("Unknown log level: " + levelName + " <none|info|error|debug>") {}
            const char* what() const noexcept override {
                return _message.c_str();
            }
    };

    inline LogLevel getLogLevelFromName(const std::string &name) {
        auto it = logLevelsNames.find(name);
        if (it != logLevelsNames.end()) {
            return it->second;
        }
        throw LogLevelNotFoundException(name);
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

    inline void progress(unsigned int current, unsigned int total) {
        constexpr int increment = 5;
        constexpr int barWidth = 20;  // 20 segmentos = cada uno vale 5%

        if (currentLevel != LogLevel::Progress) {
            return;
        }

        int percentage = static_cast<int>((current + 1) / static_cast<double>(total) * 100);
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