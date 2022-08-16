﻿// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>
#include <NotificationTelemetryHelper.h>

DECLARE_TRACELOGGING_CLASS(PushNotificationTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.PushNotificationTelemetry",
    // {7c1b07ef-a7c0-56d1-5456-385ebd4412b2}
    (0x7c1b07ef, 0xa7c0, 0x56d1, 0x54, 0x56, 0x38, 0x5e, 0xbd, 0x44, 0x12, 0xb2));


class PushNotificationTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PushNotificationTelemetry, PushNotificationTelemetryProvider);

public:
    DEFINE_EVENT_METHOD(LogCreateChannelAsync)(
        winrt::hresult hr,
        const winrt::guid& remoteId) noexcept try
    {
        if (m_helper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "CreateChannelAsync",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingGuid(remoteId, "RemoteId"),
                TraceLoggingBool(m_helper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_helper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogCloseChannel)(
        winrt::hresult hr) noexcept try
    {
        if (m_helper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "CloseChannel",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(m_helper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_helper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogRegister)(
        winrt::hresult hr) noexcept try
    {
        if (m_helper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "Register",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance), 
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(m_helper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_helper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregister)(
        winrt::hresult hr) noexcept try
    {
        if (m_helper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "Unregister",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(m_helper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_helper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

    DEFINE_EVENT_METHOD(LogUnregisterAll)(
        winrt::hresult hr) noexcept try
    {
        if (m_helper.ShouldLogEvent())
        {
            TraceLoggingClassWriteMeasure(
                "UnregisterAll",
                TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingHexUInt32(hr, "OperationResult"),
                TraceLoggingBool(m_helper.IsPackagedApp(), "IsAppPackaged"),
                TraceLoggingWideString(m_helper.GetAppName().c_str(), "AppName"));
        }
    }
    CATCH_LOG()

private:
    NotificationTelemetryHelper m_helper;

};
