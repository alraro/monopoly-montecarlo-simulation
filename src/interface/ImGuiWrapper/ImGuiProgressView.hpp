#pragma once
#include "GenericViewComponents.hpp"
#include "FullScreenWindow.hpp"
#include "imgui.h"

enum class ProgressViewState {
    Running,
    Completed,
    Cancelled
};

class ImGuiProgressView : public IProgressView {
    private:
        float               _progress = 0.0f;
        uint64_t            _totalGames = 0;
        uint64_t            _completedGames = 0;
        CancelCallback      _onCancelCallback;
        GoToConfigCallback  _onGoToConfigCallback;
        ProgressViewState   _currentState = ProgressViewState::Running;

        void _renderProgressBar() {
            ImGui::ProgressBar(_progress, ImVec2(-1.0f, 0.0f));
        }

        void _renderCancelButton() {
            if (ImGui::Button("Cancelar")) {
                _currentState = ProgressViewState::Cancelled;
                if (_onCancelCallback) {
                    _onCancelCallback();
                }
            }
        }

        void _renderGoToConfigButton() {
            if (ImGui::Button("Volver atras")) {
                if (_onGoToConfigCallback) {
                    _onGoToConfigCallback();
                }
            }
        }

        void _renderCompletedSimulationCompletionProgressText() {
            ImGui::Text("Completado %lu de %lu partidas.", _completedGames, _totalGames);
        }

        void _renderRunningState() {
            ImGui::Text("Calculando Montecarlo...");
            this->_renderCompletedSimulationCompletionProgressText();
            this->_renderProgressBar();
            this->_renderCancelButton();
            if (_progress >= 1.0f) {
                _currentState = ProgressViewState::Completed;
            }
        }

        void _renderCompletedState() {
            ImGui::Text("La simulación ha finalizado.");
            this->_renderCompletedSimulationCompletionProgressText();
            this->_renderProgressBar();
            this->_renderGoToConfigButton();
        }

        void _renderCancelledState() {
            ImGui::Text("La simulación ha sido cancelada.");
            this->_renderCompletedSimulationCompletionProgressText();
            this->_renderProgressBar();
            this->_renderGoToConfigButton();
        }

    public:
        void initializeSimulationStart(uint64_t totalGames) override {
            _progress = 0.0f;
            _currentState = ProgressViewState::Running;
            _totalGames = totalGames;
            _completedGames = 0;
        }

        void updateProgress(uint64_t completedCount) override {
            _completedGames = completedCount;
            if (_totalGames > 0) {
                _progress = static_cast<float>(_completedGames) / static_cast<float>(_totalGames);
            } else {
                _progress = 0.0f;
            }
        }

        void renderFrame() override {
            FullScreenWindow window("Progreso de la simulación");
            switch (_currentState) {
                case ProgressViewState::Running:
                    this->_renderRunningState();
                    break;
                case ProgressViewState::Completed:
                    this->_renderCompletedState();
                    break;
                case ProgressViewState::Cancelled:
                    this->_renderCancelledState();
                    break;
            }
        }

        void setOnCancelCallback(CancelCallback callback) override {
            _onCancelCallback = callback;
        }

        void setOnGoToConfigCallback(GoToConfigCallback callback) override {
            _onGoToConfigCallback = callback;
        }
};