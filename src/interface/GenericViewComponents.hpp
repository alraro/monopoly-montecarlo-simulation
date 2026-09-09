#pragma once
#include <functional>
#include <memory>
#include "SimulationConfig.hpp"

class IView { 
public: 
    virtual ~IView() = default; 
};

class IMainWindow {
public:
    virtual ~IMainWindow() = default;
    virtual void setMainView(IView* vista) = 0;
    virtual void display() = 0;
};

class IConfigView : public IView {
public:
    using RunCallback = std::function<void(const SimulationConfig&)>;
    virtual void setOnRunCallback(RunCallback callback) = 0;
};

class IProgressView : public IView {
public:
    virtual void setupProgressBar(uint64_t totalPartidas) = 0;
    virtual void updateProgress(uint64_t completado, uint64_t total) = 0;
};

class IGUIFactory {
public:
    virtual ~IGUIFactory() = default;
    virtual std::unique_ptr<IMainWindow> createMainWindow() = 0;
    virtual std::unique_ptr<IConfigView> createConfigView() = 0;
    virtual std::unique_ptr<IProgressView> createProgressView() = 0;
};