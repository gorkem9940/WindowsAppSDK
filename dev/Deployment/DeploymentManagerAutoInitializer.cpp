﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <Windows.h>
#include <stdlib.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.System.h>
#include <winrt/Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>

// If any options are defined use them, else use the default
#if !defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_DEFAULT)
// Default isn't defined. Define it if no options are defined
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_NONE)
#elif defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK)
#elif defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK_IFDEBUGGERATTACHED)
#elif defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_FAILFAST)
#elif defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_SHOWUI)
#elif defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONNOPACKAGEIDENTITY_NOOP)
#else
// No options specified! Use the default
#define MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_DEFAULT
#endif
#endif

namespace Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager
{
    struct AutoInitialize
    {
        AutoInitialize()
        {
            Initialize();
        }

        ~AutoInitialize() = default;

        static ::winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions Options()
        {
            ::winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions options;
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_DEFAULT)
            // Use the default options
            options.OnError_ShowUI(true);
#elif defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_NONE)
            // No options!
#else
            // Use the specified options
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK)
            options.OnError_DebugBreak(true);
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK_IFDEBUGGERATTACHED)
            options.OnError_DebugBreak_IfDebuggerAttached(true);
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_FAILFAST)
            options.OnError_FailFast(true);
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONERROR_SHOWUI)
            options.OnError_ShowUI(true);
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_DEPLOYMENTMANAGER_AUTO_INITIALIZE_OPTIONS_ONNOPACKAGEIDENTITY_NOOP)
            options.OnNoPackageIdentity_NOOP(true);
#endif
#endif
            return options;
        }

        static void Initialize()
        {
            auto options{ Options() };
            auto deploymentResult{ ::winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager::Initialize(options) };
            if (deploymentResult.Status() != ::winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Ok)
            {
                const HRESULT hr{ deploymentResult.ExtendedError().value };
                exit(hr);
            }
        }
    };
    static AutoInitialize g_autoInitialize;
}
