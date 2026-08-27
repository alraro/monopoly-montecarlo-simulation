#ifndef LOGGER_HPP
# define LOGGER_HPP
# include <iostream>

enum class LogLevel {
    None,
    Info,
    Error,
    Debug
};

namespace Logger {
    inline LogLevel currentLevel = LogLevel::Info;

    inline void setLogLevel(LogLevel level) { currentLevel = level; }

    template<typename... Args>
    void info(Args&&... args) {
        if (currentLevel >= LogLevel::Info) {
            (std::cout << ... << args) << std::endl;
        }
    }

    template<typename... Args>
    void debug(Args&&... args) {
        if (currentLevel >= LogLevel::Debug) {
            (std::cout << ... << args) << std::endl;
        }
    }

    template<typename... Args>
    void error(Args&&... args) {
        if (currentLevel != LogLevel::None) {
            (std::cerr << ... << args) << std::endl;
        }
    }

}

#endif