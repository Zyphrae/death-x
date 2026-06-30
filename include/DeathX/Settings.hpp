#pragma once

namespace deathx {

struct Settings {
    bool enabled = true;
    int maximumMarkerCount = 50;
    bool mergeNearbyDeaths = false;
    float mergeRadius = 18.0f;
    float ignoreStartSeconds = 0.5f;
    int colorStepDeaths = 5;
    float markerSize = 9.0f;
    int markerOpacity = 220;

    static Settings load();
};

}
