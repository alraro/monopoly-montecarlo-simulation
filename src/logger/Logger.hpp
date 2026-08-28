#ifndef LOGGER_HPP
# define LOGGER_HPP
# include <iostream>

enum class LogLevel {
    None,
    Error,
    Info,
    Debug
};

namespace Logger {
    inline LogLevel currentLevel = LogLevel::Info;

    inline void setLogLevel(LogLevel level) { currentLevel = level; }

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

    template<typename... Args>
    void error(Args&&... args) {
        if (currentLevel >= LogLevel::Error) {
            (std::cerr << ... << args) << "\n";
        }
    }

    template<typename... Args>
    void log(Args&&... args) {
        (std::cout << ... << args) << "\n";
    }

}

#endif