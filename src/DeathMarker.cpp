#include <DeathX/DeathMarker.hpp>

#include <algorithm>
#include <array>

using namespace geode::prelude;

namespace deathx {

namespace {
constexpr float kStrokeWidthRatio = 0.22f;
constexpr int kGlowActionTag = 7401;

constexpr std::array<ccColor4F, 11> kColorSteps = {{
    {1.0f, 0.04f, 0.04f, 1.0f},
    {1.0f, 0.20f, 0.00f, 1.0f},
    {1.0f, 0.34f, 0.00f, 1.0f},
    {1.0f, 0.48f, 0.00f, 1.0f},
    {1.0f, 0.62f, 0.00f, 1.0f},
    {1.0f, 0.76f, 0.00f, 1.0f},
    {1.0f, 0.90f, 0.06f, 1.0f},
    {1.0f, 1.0f, 0.18f, 1.0f},
    {1.0f, 1.0f, 0.40f, 1.0f},
    {1.0f, 1.0f, 0.68f, 1.0f},
    {1.0f, 1.0f, 0.95f, 1.0f},
}};

ccColor4F colorForDeathCount(int deathCount, int colorStepDeaths, float alpha) {
    auto const step = std::clamp(colorStepDeaths, 1, 10);
    auto const index = std::clamp((std::max(1, deathCount) - 1) / step, 0, 10);
    auto color = kColorSteps[static_cast<std::size_t>(index)];
    color.a = alpha;
    return color;
}
}

DeathMarker::DeathMarker(CCPoint position) : m_position(position) {}

void DeathMarker::attachTo(CCNode* parent, Settings const& settings) {
    if (m_node || !parent) {
        return;
    }

    m_glowNode = CCDrawNode::create();
    m_glowNode->setPosition(m_position);
    m_glowNode->setAnchorPoint(ccp(0.5f, 0.5f));
    m_glowNode->setVisible(false);
    parent->addChild(m_glowNode);

    m_node = CCDrawNode::create();
    m_node->setPosition(m_position);
    m_node->setAnchorPoint(ccp(0.5f, 0.5f));
    parent->addChild(m_node);
    redraw(settings);
}

void DeathMarker::detach() {
    if (m_glowNode) {
        m_glowNode->removeFromParentAndCleanup(true);
        m_glowNode = nullptr;
    }

    if (!m_node) {
        return;
    }

    m_node->removeFromParentAndCleanup(true);
    m_node = nullptr;
}

void DeathMarker::increaseIntensity(Settings const& settings) {
    ++m_deathCount;
    redraw(settings);
    flashGlow(settings);
}

void DeathMarker::refresh(Settings const& settings) {
    redraw(settings);
}

bool DeathMarker::contains(CCPoint position, float radius) const {
    auto const dx = m_position.x - position.x;
    auto const dy = m_position.y - position.y;
    return (dx * dx) + (dy * dy) <= radius * radius;
}

void DeathMarker::redraw(Settings const& settings) {
    if (!m_node) {
        return;
    }

    auto const halfSize = settings.markerSize * 0.5f;
    auto const strokeWidth = std::max(1.0f, settings.markerSize * kStrokeWidthRatio);
    auto const markerColor = color(settings);

    m_node->clear();
    m_node->drawSegment(ccp(-halfSize, -halfSize), ccp(halfSize, halfSize), strokeWidth, markerColor);
    m_node->drawSegment(ccp(-halfSize, halfSize), ccp(halfSize, -halfSize), strokeWidth, markerColor);
    redrawGlow(settings);
}

void DeathMarker::redrawGlow(Settings const& settings) {
    if (!m_glowNode) {
        return;
    }

    auto const halfSize = settings.markerSize * 0.5f;
    auto const strokeWidth = std::max(2.0f, settings.markerSize * 0.5f);
    auto glowColor = color(settings);
    glowColor.a = 0.65f;

    m_glowNode->clear();
    m_glowNode->drawSegment(ccp(-halfSize, -halfSize), ccp(halfSize, halfSize), strokeWidth, glowColor);
    m_glowNode->drawSegment(ccp(-halfSize, halfSize), ccp(halfSize, -halfSize), strokeWidth, glowColor);
}

void DeathMarker::flashGlow(Settings const& settings) {
    if (!m_glowNode) {
        return;
    }

    redrawGlow(settings);
    m_glowNode->stopActionByTag(kGlowActionTag);
    m_glowNode->setVisible(true);
    m_glowNode->setOpacity(190);

    auto action = CCSequence::createWithTwoActions(
        CCFadeOut::create(0.45f),
        CCHide::create()
    );
    action->setTag(kGlowActionTag);
    m_glowNode->runAction(action);
}

ccColor4F DeathMarker::color(Settings const& settings) const {
    auto const alpha = static_cast<float>(settings.markerOpacity) / 255.0f;
    return colorForDeathCount(m_deathCount, settings.colorStepDeaths, alpha);
}

}
