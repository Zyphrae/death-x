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
        if (!menu || !deathx::hasActiveMarkers() || menu->getChildByID("clear-markers-button"_spr)) {
            return;
        }

        auto clearSprite = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
        if (!clearSprite) {
            return;
        }

        clearSprite->setScale(0.48f);
        auto clearButton = CCMenuItemExt::createSpriteExtra(
            clearSprite,
            [](CCNode* sender) {
                deathx::clearActiveMarkers();

                if (sender) {
                    sender->setVisible(false);
                    if (auto parent = sender->getParent()) {
                        parent->updateLayout(true);
                    }
                }
            }
        );
        if (!clearButton) {
            return;
        }

        clearButton->setID("clear-markers-button"_spr);
        menu->addChild(clearButton);

        menu->updateLayout(true);
    }
};
