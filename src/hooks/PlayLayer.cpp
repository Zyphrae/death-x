#include <DeathX/MarkerManager.hpp>
#include <DeathX/PlayLayerAccess.hpp>
#include <DeathX/Settings.hpp>

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(DeathXPlayLayer, PlayLayer) {
    struct Fields {
        deathx::MarkerManager markers;
    };

public:
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        m_fields->markers.setLayer(m_objectLayer);
        m_fields->markers.trimToLimit(deathx::Settings::load());
        return true;
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) override {
        auto settings = deathx::Settings::load();
        if (shouldTrackDeath(player, object, settings)) {
            m_fields->markers.addDeath(player->getRealPosition(), settings);
        }

        PlayLayer::destroyPlayer(player, object);
    }

    void onQuit() {
        m_fields->markers.clear();
        PlayLayer::onQuit();
    }

    void clearDeathXMarkers() {
        m_fields->markers.clear();
    }

    void refreshDeathXMarkers() {
        m_fields->markers.refresh(deathx::Settings::load());
    }

private:
    bool shouldTrackDeath(PlayerObject* player, GameObject* object, deathx::Settings const& settings) {
        if (!settings.enabled || !player || object == m_anticheatSpike) {
            return false;
        }

        if (m_playerDied || !m_started || m_isPaused) {
            return false;
        }

        if (player != m_player1 && player != m_player2) {
            return false;
        }

        if (m_attemptTime <= settings.ignoreStartSeconds || !isGameplayActive()) {
            return false;
        }

        return true;
    }
};

namespace deathx {

void clearActiveMarkers() {
    if (auto playLayer = PlayLayer::get()) {
        static_cast<DeathXPlayLayer*>(playLayer)->clearDeathXMarkers();
    }
}

void refreshActiveMarkers() {
    if (auto playLayer = PlayLayer::get()) {
        static_cast<DeathXPlayLayer*>(playLayer)->refreshDeathXMarkers();
    }
}

}
