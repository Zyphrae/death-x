#include <DeathX/PlayLayerAccess.hpp>

#include <Geode/Geode.hpp>

using namespace geode::prelude;

$execute {
    listenForAllSettingChanges([](std::string_view, std::shared_ptr<SettingV3> const&) {
        deathx::refreshActiveMarkers();
    });

    log::info("Death X loaded");
}
