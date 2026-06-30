#include <DeathX/MarkerManager.hpp>

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace deathx {

namespace {
constexpr int kMarkerZOrder = 1 << 20;
}

void MarkerManager::setLayer(CCLayer* objectLayer) {
    if (m_container || !objectLayer) {
        return;
    }

    m_container = CCNode::create();
    m_container->setID("death-x-markers"_spr);
    m_container->setZOrder(kMarkerZOrder);
    objectLayer->addChild(m_container);
}

void MarkerManager::addDeath(CCPoint position, Settings const& settings) {
    if (!m_container || !settings.enabled) {
        return;
    }

    if (settings.mergeNearbyDeaths) {
        if (auto marker = findMarkerNear(position, settings.mergeRadius)) {
            marker->increaseIntensity(settings);
            return;
        }
    }

    auto& marker = m_markers.emplace_back(position);
    marker.attachTo(m_container, settings);
    trimToLimit(settings);
}

void MarkerManager::clear() {
    for (auto& marker : m_markers) {
        marker.detach();
    }

    m_markers.clear();

    if (m_container) {
        m_container->removeAllChildrenWithCleanup(true);
    }
}

void MarkerManager::trimToLimit(Settings const& settings) {
    while (static_cast<int>(m_markers.size()) > settings.maximumMarkerCount) {
        removeOldest();
    }
}

void MarkerManager::refresh(Settings const& settings) {
    for (auto& marker : m_markers) {
        marker.refresh(settings);
    }

    trimToLimit(settings);
}

bool MarkerManager::hasLayer() const {
    return m_container != nullptr;
}

std::size_t MarkerManager::size() const {
    return m_markers.size();
}

DeathMarker* MarkerManager::findMarkerNear(CCPoint position, float radius) {
    for (auto& marker : m_markers) {
        if (marker.contains(position, radius)) {
            return &marker;
        }
    }

    return nullptr;
}

void MarkerManager::removeOldest() {
    if (m_markers.empty()) {
        return;
    }

    m_markers.front().detach();
    m_markers.pop_front();
}

}
