#include "PCH.h"
#include "Version.h"

bool isLoaded = false;

void InitializeLog()
{
#ifndef NDEBUG
    auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
    auto path = logger::log_directory();
    if (!path) {
        SKSE::stl::report_and_fail("Failed to find standard logging directory"sv);
    }
    *path /= fmt::format("{}.log", Version::PROJECT);
    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

    auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
    log->set_level(spdlog::level::trace);
    log->flush_on(spdlog::level::trace);
#else
    log->set_level(spdlog::level::info);
    log->flush_on(spdlog::level::info);
#endif

    spdlog::set_default_logger(std::move(log));
    spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

    logger::info(FMT_STRING("{} v{}"), Version::PROJECT, Version::NAME);
}

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
    switch (a_msg->type) {
    case SKSE::MessagingInterface::kDataLoaded:
        logger::info("Game data loaded");
        break;
    }
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
    InitializeLog();
    logger::info("Game version: {}", a_skse->RuntimeVersion().string());

    SKSE::Init(a_skse);

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener("SKSE", MessageHandler)) {
        return false;
    }

    logger::info("ENBHelperSE loaded");

    // WORKAROUND NOTE: Set isLoaded to true immediately for compatibility with ENB
    isLoaded = true;

    return true;
}
