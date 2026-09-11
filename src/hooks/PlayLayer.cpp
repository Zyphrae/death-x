#include <DeathX/MarkerManager.hpp>
#include <DeathX/PlayLayerAccess.hpp>
#include <DeathX/Settings.hpp>

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <eclipse.eclipse-menu/include/eclipse.hpp>

using namespace geode::prelude;

namespace {
constexpr float kNoclipPollInterval = 0.1f;
}

class $modify(DeathXPlayLayer, PlayLayer) {
    struct Fields {
        deathx::MarkerManager markers;
        bool noclipUsedThisAttempt = false;
        bool deathRecordedThisAttempt = false;
        bool processingDeath = false;
        unsigned int attemptGeneration = 0;
    };

public:
    static void onModify(auto& self) {
        (void)self.setHookPriorityPre("PlayLayer::destroyPlayer", Priority::First);
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        m_fields->markers.setLayer(m_objectLayer);
        m_fields->markers.trimToLimit(deathx::Settings::load());
        pollNoclip(0.0f);
        schedule(schedule_selector(DeathXPlayLayer::pollNoclip), kNoclipPollInterval);
        return true;
    }

    void resetLevel() override {
        ++m_fields->attemptGeneration;
        m_fields->noclipUsedThisAttempt = false;
        m_fields->deathRecordedThisAttempt = false;
        PlayLayer::resetLevel();
        pollNoclip(0.0f);
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) override {
        if (m_fields->processingDeath) {
            PlayLayer::destroyPlayer(player, object);
            return;
        }

        m_fields->processingDeath = true;
        auto settings = deathx::Settings::load();
        auto const isCandidate = isDeathCandidate(player, object, settings);
        auto const noclipActive = isNoclipActive();
        auto const attemptGeneration = m_fields->attemptGeneration;
        auto const wasDead = player && player->m_isDead;
        auto const deathPosition = isCandidate ? player->getRealPosition() : CCPointZero;

        if (noclipActive) {
            m_fields->noclipUsedThisAttempt = true;
        }

        PlayLayer::destroyPlayer(player, object);
        m_fields->processingDeath = false;

        if (attemptGeneration != m_fields->attemptGeneration || !isCandidate || wasDead) {
            return;
        }

        if (!player->m_isDead) {
            if (object) {
                m_fields->noclipUsedThisAttempt = true;
            }
            return;
        }

        if (!settings.enabled || m_fields->deathRecordedThisAttempt) {
            return;
        }

        if (noclipActive && settings.pauseDuringNoclip) {
            return;
        }

        if (
            m_fields->noclipUsedThisAttempt &&
            !noclipActive &&
            !settings.countDeathAfterNoclip
        ) {
            return;
        }

        m_fields->markers.addDeath(deathPosition, settings);
        m_fields->deathRecordedThisAttempt = true;
    }

    void onQuit() {
        m_fields->markers.clear();
        PlayLayer::onQuit();
    }

    void clearDeathXMarkers() {
        m_fields->markers.clear();
    }

    void refreshDeathXMarkers() {
        auto const settings = deathx::Settings::load();
        if (!settings.enabled) {
            m_fields->markers.clear();
            return;
        }

        m_fields->markers.refresh(settings);
    }

    [[nodiscard]] bool hasDeathXMarkers() {
        return m_fields->markers.size() != 0;
    }

private:
    bool isNoclipActive() const {
        if (m_isIgnoreDamageEnabled || m_ignoreDamage) {
            return true;
        }

        return Loader::get()->isModLoaded("eclipse.eclipse-menu") &&
            eclipse::config::get<bool>("player.noclip", false);
    }

    void pollNoclip(float) {
        if (isNoclipActive()) {
            m_fields->noclipUsedThisAttempt = true;
        }
    }

    bool isDeathCandidate(PlayerObject* player, GameObject* object, deathx::Settings const& settings) {
        if (!player || object == m_anticheatSpike) {
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

bool hasActiveMarkers() {
    if (auto playLayer = PlayLayer::get()) {
        return static_cast<DeathXPlayLayer*>(playLayer)->hasDeathXMarkers();
    }

    return false;
}

}
