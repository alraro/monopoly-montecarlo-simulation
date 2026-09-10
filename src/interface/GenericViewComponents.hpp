#pragma once
#include <functional>
#include <memory>
#include "SimulationConfig.hpp"

class IView { 
public: 
    virtual ~IView() = default;
    virtual void renderFrame() = 0;
};

class IMainWindow {
public:
    virtual ~IMainWindow() = default;
    virtual void setMainView(IView* displayView) = 0;
    virtual bool openWindow(int width, int height, const std::string_view title) = 0;
    virtual void closeWindow() = 0;
    virtual void display() = 0;
};

class IConfigView : public IView {
public:
    using RunCallback = std::function<void(const SimulationConfig&)>;
    virtual void setOnRunCallback(RunCallback callback) = 0;
};

class IProgressView : public IView {
public:
    virtual void setupProgressBar(uint64_t totalGames) = 0;
    virtual void updateProgress(uint64_t completedCount, uint64_t totalGames) = 0;
};

class IGUIFactory {
public:
    virtual ~IGUIFactory() = default;
    virtual std::unique_ptr<IMainWindow> createMainWindow() = 0;
    virtual std::unique_ptr<IConfigView> createConfigView() = 0;
    virtual std::unique_ptr<IProgressView> createProgressView() = 0;
};