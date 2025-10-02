extern "C" DLLEXPORT bool IsLoaded()
{
    return isLoaded;
}

extern "C" DLLEXPORT bool GetCurrentWeather(std::uint32_t& currentWeatherFormID)
{
    const auto* skyPtr = RE::Sky::GetSingleton();
    if (skyPtr && skyPtr->currentWeather) {
        currentWeatherFormID = skyPtr->currentWeather->formID;
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetOutgoingWeather(std::uint32_t& outgoingWeatherFormID)
{
    const auto* skyPtr = RE::Sky::GetSingleton();
    if (skyPtr && skyPtr->lastWeather) {
        outgoingWeatherFormID = skyPtr->lastWeather->formID;
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetWeatherTransition(float& weatherTransition)
{
    const auto* skyPtr = RE::Sky::GetSingleton();
    if (skyPtr) {
        weatherTransition = skyPtr->currentWeatherPct;
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetSkyMode(std::uint32_t& skyMode)
{
    const auto* skyPtr = RE::Sky::GetSingleton();
    if (skyPtr) {
        skyMode = skyPtr->mode.underlying();
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetTime(float& time)
{
    // CHANGE: Use the Calendar singleton, which is a better source for time.
    const auto* calendar = RE::Calendar::GetSingleton();
    if (calendar) {
        time = calendar->GetHour();
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetCurrentLocationID(std::uint32_t& locationFormID)
{
    const auto* playerPtr = RE::PlayerCharacter::GetSingleton();
    if (const auto* location = playerPtr ? playerPtr->GetCurrentLocation() : nullptr; location) {
        locationFormID = location->formID;
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetWorldSpaceID(std::uint32_t& worldSpaceFormID)
{
    const auto* playerPtr = RE::PlayerCharacter::GetSingleton();
    if (!playerPtr) {
        return false;
    }

    if (const auto* parentCell = playerPtr->GetParentCell(); parentCell && parentCell->IsInteriorCell()) {
        worldSpaceFormID = 0x0;
        return true;
    }

    if (const auto* worldSpace = playerPtr->GetWorldspace(); worldSpace) {
        worldSpaceFormID = worldSpace->formID;
        return true;
    }
    return false;
}


extern "C" DLLEXPORT int32_t GetClassification(RE::TESWeather* weather)
{
    using Flags = RE::TESWeather::WeatherDataFlag;

    const auto flags = weather->data.flags;

    if (flags.any(Flags::kPleasant))
        return 0;
    if (flags.any(Flags::kCloudy))
        return 1;
    if (flags.any(Flags::kRainy))
        return 2;
    if (flags.any(Flags::kSnow))
        return 3;

    return -1;  
}

extern "C" DLLEXPORT bool GetCurrentWeatherClassification(int32_t& classification)
{
    const auto* skyPtr = RE::Sky::GetSingleton();
    if (skyPtr && skyPtr->currentWeather) {
        classification = GetClassification(skyPtr->currentWeather);
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetOutgoingWeatherClassification(int32_t& classification)
{
    const auto* skyPtr = RE::Sky::GetSingleton();
    if (skyPtr && skyPtr->lastWeather) {
        classification = GetClassification(skyPtr->lastWeather);
        return true;
    }
    return false;
}

extern "C" DLLEXPORT bool GetPlayerCameraTransformMatrices(RE::NiTransform& m_Local, RE::NiTransform& m_World, RE::NiTransform& m_OldWorld)
{
    const auto* playerCamera = RE::PlayerCamera::GetSingleton();
    // CHANGE: Use smart pointer .get() and direct assignment instead of memcpy.
    if (const auto* cameraNode = playerCamera ? playerCamera->cameraRoot.get() : nullptr; cameraNode && cameraNode->world.scale != 0.0f) {
        m_Local = cameraNode->local;
        m_World = cameraNode->world;
        m_OldWorld = cameraNode->previousWorld;
        return true;
    }
    return false;
}
