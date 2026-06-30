#include <DeathX/PlayLayerAccess.hpp>

#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(DeathXPauseLayer, PauseLayer) {
    void customSetup() override {
        PauseLayer::customSetup();
        addDeathXButtons();
    }

    void addDeathXButtons() {
        auto menu = getChildByID("left-button-menu");
        if (!menu) {
            return;
        }

        auto clearSprite = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
        clearSprite->setScale(0.48f);
        auto clearButton = CCMenuItemExt::createSpriteExtra(
            clearSprite,
            [](CCNode*) {
                deathx::clearActiveMarkers();
            }
        );
        clearButton->setID("clear-markers-button"_spr);
        menu->addChild(clearButton);

        menu->updateLayout(true);
    }
};
