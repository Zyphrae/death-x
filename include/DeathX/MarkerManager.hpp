#pragma once

#include <DeathX/DeathMarker.hpp>

#include <deque>

namespace deathx {

class MarkerManager {
public:
    void setLayer(cocos2d::CCLayer* objectLayer);
    void addDeath(cocos2d::CCPoint position, Settings const& settings);
    void clear();
    void trimToLimit(Settings const& settings);
    void refresh(Settings const& settings);

    [[nodiscard]] bool hasLayer() const;
    [[nodiscard]] std::size_t size() const;

private:
    cocos2d::CCNode* m_container = nullptr;
    std::deque<DeathMarker> m_markers;

    [[nodiscard]] DeathMarker* findMarkerNear(cocos2d::CCPoint position, float radius);
    void removeOldest();
};

}
