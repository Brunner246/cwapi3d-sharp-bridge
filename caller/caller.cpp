
#define CWAPI3D_PLUGIN_NAME    L"CSharpBridge"
#define CWAPI3D_AUTHOR_NAME    L"Your Name"
#define CWAPI3D_AUTHOR_EMAIL   L"your.email@example.com"

#include "CwAPI3D.h"
#include <string>
#include <format>
#include <iostream>


using namespace System;
using namespace System::IO;
using namespace System::Reflection;

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory* aFactory);

//TODO: config via JSON or similar
constexpr const char* NetAssemblyName = "sharpLib";
constexpr const char* InitializerType = "sharpLib.Initializer";
constexpr const char* InitializerMethod = "Run";

Type^ LoadInitializerType(const std::string& pluginDir)
{
  auto netDllPath = std::format("{}\\{}.dll", pluginDir, NetAssemblyName);
  Console::WriteLine("Loading: " + gcnew String(netDllPath.c_str()));
  Assembly^ assembly = Assembly::LoadFrom(gcnew String(netDllPath.c_str()));
  return assembly->GetType(gcnew String(InitializerType));

}

bool CallRun(Type^ type, CwAPI3D::ControllerFactory* factory)
{
  array<Object^>^ args = gcnew array<Object^>(1) { IntPtr(factory) };
  Object^ result = type->InvokeMember(gcnew String(InitializerMethod),
    BindingFlags::InvokeMethod | BindingFlags::Static | BindingFlags::Public,
    nullptr,
    nullptr,
    args);
  return result != nullptr && safe_cast<bool>(result);
}


bool plugin_x64_init(CwAPI3D::ControllerFactory* aFactory)
{
  if (!aFactory) return false;

  auto path = aFactory->getUtilityController()->getPluginPath()->narrowData();
  std::cout << "Plugin path: " << path << std::endl;

  try
  {
    Type^ t = LoadInitializerType(path);
    if (t != nullptr)
      return CallRun(t, aFactory);
  }
  catch (Exception^ e)
  {
    Console::WriteLine("Error: " + e->Message);
  }

  return false;
}

