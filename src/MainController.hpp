#pragma once
#include "GenericViewComponents.hpp"
#include <memory>
#include <thread>
#include "Simulation.hpp"
#include "SimulationConfig.hpp"
#include "ConfigParser.hpp"


class MainController {
    private:
        std::unique_ptr<IMainWindow>      _mainWindow;
        std::unique_ptr<IConfigView>      _configView;
        std::unique_ptr<IProgressView>    _progressView;
        SimulationConfig                  _simulationConfig;

        std::unique_ptr<Simulation>       _simulation;
        std::thread                       _workerThread;

        void transitionToSimulation(const SimulationConfig& config) {
            _mainWindow->setMainView(_progressView.get());
            _progressView->setupProgressBar(config.gameCount);

            if (!config.isValid()) return;

            _simulation = std::make_unique<Simulation>(config, *_progressView);
            _workerThread = std::thread([this]() {
                this->_simulation->run();
            });
    }

    public:
        MainController(IGUIFactory &guiFactory, int argc, char **argv): 
            _mainWindow(guiFactory.createMainWindow()), 
            _configView(guiFactory.createConfigView()), 
            _progressView(guiFactory.createProgressView()),
            _simulationConfig(ConfigParser::configFromCommandLine(argc, argv))
        {};

        MainController(IGUIFactory &guiFactory): 
            _mainWindow(guiFactory.createMainWindow()), 
            _configView(guiFactory.createConfigView()), 
            _progressView(guiFactory.createProgressView()),
            _simulationConfig()
        {};

        ~MainController() {
            if (_workerThread.joinable()) {
                _workerThread.join();
            }
        }

        void start() {
            if (_simulationConfig.hasInterface) {
                _mainWindow->openWindow(1280, 720, "Monopoly Simulator");
                _configView->setOnRunCallback([this](const SimulationConfig& conf) { 
                    this->transitionToSimulation(conf); 
                });
                _mainWindow->setMainView(_configView.get());
                _mainWindow->display();
            } else {
                if (!this->_simulationConfig.isValid()) return;
                this->_simulation = std::make_unique<Simulation>(_simulationConfig, *_progressView);   
                this->_simulation->run();
            }
        }
};