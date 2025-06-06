
#include "csharp_bridge.h"

#include <stdexcept>

#include "controller/ElementController.h"

CwAPI3D::Net::Bridge::CwApi3DFactory::CwApi3DFactory(IntPtr nativeFactoryPtr)
{
  mControllerFactory = static_cast<CwAPI3D::ControllerFactory*>(nativeFactoryPtr.ToPointer());
  if (!mControllerFactory)
  {
    throw std::runtime_error("Failed to initialize CwApi3DFactory: nativeFactoryPtr is null.");
  }
  mElementController = gcnew ElementController(mControllerFactory);
}

System::String^ CwAPI3D::Net::Bridge::CwApi3DFactory::GetSomething()
{
  if (!mControllerFactory)
  {
    throw std::runtime_error("ControllerFactory is not initialized.");
  }
  const auto text = mControllerFactory->getUtilityController()->get3DFilePath()->narrowData();
  const auto textToString = gcnew System::String(text);
  return textToString;
}

IntPtr CwAPI3D::Net::Bridge::CwApi3DFactory::GetNativeFactory()
{
  throw std::runtime_error("GetNativeFactory is not implemented in this example.");
}

CwAPI3D::Net::Bridge::ElementController^ CwAPI3D::Net::Bridge::CwApi3DFactory::GetElementController()
{

  if (!mControllerFactory)
  {
    throw std::runtime_error("ControllerFactory is not initialized.");
  }
  return gcnew ElementController(mControllerFactory);

}
