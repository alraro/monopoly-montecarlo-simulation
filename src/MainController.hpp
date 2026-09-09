#pragma once
#include "GenericViewComponents.hpp"
#include <memory>
#include <thread>
#include "Simulation.hpp"


class MainController {
    private:
        std::unique_ptr<IMainWindow> _mainWindow;
        std::unique_ptr<IConfigView> _configView;
        std::unique_ptr<IProgressView> _progressView;

        std::unique_ptr<Simulation> _simulation;
        std::thread _workerThread;

        void transitionToSimulation(const SimulationConfig& config) {
            _mainWindow->setMainView(_progressView.get());
            _progressView->setupProgressBar(config.gameCount);

            _simulation = std::make_unique<Simulation>(config, *_progressView);
            _workerThread = std::thread([this]() {
                this->_simulation->runParallelMontecarloSimulation();
            });
    }

    public:
        MainController(IGUIFactory &guiFactory) {
            _mainWindow = guiFactory.createMainWindow();
            _configView = guiFactory.createConfigView();
            _progressView = guiFactory.createProgressView();
        };

        ~MainController() {
            if (_workerThread.joinable()) {
                _workerThread.join();
            }
        }

        void start() {
            _configView->setOnRunCallback([this](const SimulationConfig& conf) { 
                this->transitionToSimulation(conf); 
            });

            _mainWindow->setMainView(_configView.get());
            _mainWindow->display();
        }
};