#include <DeathX/Settings.hpp>

#include <Geode/Geode.hpp>

#include <algorithm>

using namespace geode::prelude;

namespace deathx {

namespace {
constexpr int kMinimumMarkerCount = 1;
constexpr int kMaximumMarkerCount = 250;
constexpr int kMaximumManualMarkerCount = 10000;
constexpr float kMinimumMergeRadius = 4.0f;
constexpr float kMaximumMergeRadius = 90.0f;
constexpr float kMinimumIgnoreStartSeconds = 0.0f;
constexpr float kMaximumIgnoreStartSeconds = 5.0f;
constexpr int kMinimumColorStepDeaths = 1;
constexpr int kMaximumColorStepDeaths = 10;
constexpr float kMinimumMarkerSize = 4.0f;
constexpr float kMaximumMarkerSize = 24.0f;
constexpr int kMinimumOpacity = 0;
constexpr int kMaximumOpacity = 255;
}

Settings Settings::load() {
    auto mod = Mod::get();

    Settings settings;
    settings.enabled = mod->getSettingValue<bool>("enabled");
    auto const sliderMarkerCount = std::clamp(
        mod->getSettingValue<int>("maximum-marker-count"),
        kMinimumMarkerCount,
        kMaximumMarkerCount
    );
    auto const manualMarkerCount = std::clamp(
        mod->getSettingValue<int>("maximum-marker-count-override"),
        0,
        kMaximumManualMarkerCount
    );
    settings.maximumMarkerCount = manualMarkerCount > 0 ? manualMarkerCount : sliderMarkerCount;
    settings.mergeNearbyDeaths = mod->getSettingValue<bool>("merge-nearby-deaths");
    settings.mergeRadius = std::clamp(
        mod->getSettingValue<float>("merge-radius"),
        kMinimumMergeRadius,
        kMaximumMergeRadius
    );
    settings.ignoreStartSeconds = std::clamp(
        mod->getSettingValue<float>("ignore-start-seconds"),
        kMinimumIgnoreStartSeconds,
        kMaximumIgnoreStartSeconds
    );
    settings.colorStepDeaths = std::clamp(
        mod->getSettingValue<int>("color-step-deaths"),
        kMinimumColorStepDeaths,
        kMaximumColorStepDeaths
    );
    settings.markerSize = std::clamp(
        mod->getSettingValue<float>("marker-size"),
        kMinimumMarkerSize,
        kMaximumMarkerSize
    );
    settings.markerOpacity = std::clamp(
        mod->getSettingValue<int>("marker-opacity"),
        kMinimumOpacity,
        kMaximumOpacity
    );

    return settings;
}

}
