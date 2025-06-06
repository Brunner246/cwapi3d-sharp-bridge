// CwApi3DFactory.h (C++/CLI)
#pragma once

#define CWAPI3D_PLUGIN_NAME    L"CSharpBridge"
#define CWAPI3D_AUTHOR_NAME    L"Your Name"
#define CWAPI3D_AUTHOR_EMAIL   L"your.email@example.com"

#include "CwAPI3D.h"

using namespace System;

namespace CwAPI3D::Net::Bridge
{
  ref class ElementController;

  public ref class CwApi3DFactory
  {
  private:
    CwAPI3D::ControllerFactory* mControllerFactory;

    Bridge::ElementController^ mElementController;

  public:
    explicit CwApi3DFactory(IntPtr nativeFactoryPtr);

    System::String^ GetSomething();

    static IntPtr GetNativeFactory();

    Bridge::ElementController^ GetElementController();

  };
}
