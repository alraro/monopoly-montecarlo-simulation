#ifndef STRATEGY_HPP
# define STRATEGY_HPP

class Strategy {
    protected:
        Strategy() = default;
    public:
        virtual ~Strategy() = default;
        Strategy(const Strategy&) = default;
        Strategy& operator=(const Strategy&) = default;
        Strategy(Strategy&&) noexcept = default;
        Strategy& operator=(Strategy&&) noexcept = default;
};

#endif