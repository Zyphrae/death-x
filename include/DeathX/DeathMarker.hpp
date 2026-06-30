#pragma once

#include <DeathX/Settings.hpp>

#include <Geode/Geode.hpp>

namespace deathx {

class DeathMarker {
public:
    explicit DeathMarker(cocos2d::CCPoint position);

    void attachTo(cocos2d::CCNode* parent, Settings const& settings);
    void detach();
    void increaseIntensity(Settings const& settings);
    void refresh(Settings const& settings);

    [[nodiscard]] bool contains(cocos2d::CCPoint position, float radius) const;

private:
    cocos2d::CCPoint m_position;
    cocos2d::CCDrawNode* m_node = nullptr;
    cocos2d::CCDrawNode* m_glowNode = nullptr;
    int m_deathCount = 1;

    void redraw(Settings const& settings);
    void redrawGlow(Settings const& settings);
    void flashGlow(Settings const& settings);
    [[nodiscard]] cocos2d::ccColor4F color(Settings const& settings) const;
};

}
