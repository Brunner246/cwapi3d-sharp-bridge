#include "ElementController.h"
#include "../geometry/Point3D.h"
#include "../geometry/Vector3D.h"

#include <ICwAPI3DControllerFactory.h>
#include <ICwAPI3DElementController.h>
#include <ICwAPI3DElementIDList.h>
#include <stdexcept>


List<int>^ CwAPI3D::Net::Bridge::ElementController::ConvertToManagedList(CwAPI3D::Interfaces::ICwAPI3DElementIDList* nativeList)
{
  auto managedList = gcnew List<int>();
  if (!nativeList) return managedList;

  const size_t count = nativeList->count();
  for (size_t i = 0; i < count; ++i)
  {
    managedList->Add(static_cast<int>(nativeList->at(static_cast<uint32_t>(i))));
  }
  return managedList;
}

CwAPI3D::Interfaces::ICwAPI3DElementIDList* CwAPI3D::Net::Bridge::ElementController::ConvertToNativeList(List<int>^ ids)
{
  const auto nativeList = m_controllerFactory->createEmptyElementIDList();
  for each (int id in ids)
  {
    if (id < 0)
    {
      throw std::invalid_argument("Element ID cannot be negative.");
    }
    nativeList->append(static_cast<elementID>(id));
  }


  return nativeList;
}

CwAPI3D::Net::Bridge::ElementController::ElementController(Interfaces::ICwAPI3DControllerFactory* nativePtr)
{
  m_controllerFactory = nativePtr;
  m_elementController = m_controllerFactory->getElementController();
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::GetAllIdentifiableElementIDs()
{
  return ConvertToManagedList(m_elementController->getAllIdentifiableElementIDs());
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::GetVisibleIdentifiableElementIDs()
{
  return ConvertToManagedList(m_elementController->getVisibleIdentifiableElementIDs());
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::GetInvisibleIdentifiableElementIDs()
{
  return ConvertToManagedList(m_elementController->getInvisibleIdentifiableElementIDs());
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::GetActiveIdentifiableElementIDs()
{
  return ConvertToManagedList(m_elementController->getActiveIdentifiableElementIDs());
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::GetInactiveAllIdentifiableElementIDs()
{
  return ConvertToManagedList(m_elementController->getInactiveAllIdentifiableElementIDs());
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::GetInactiveVisibleIdentifiableElementIDs()
{
  return ConvertToManagedList(m_elementController->getInactiveVisibleIdentifiableElementIDs());
}


void CwAPI3D::Net::Bridge::ElementController::DeleteElements(List<int>^ elementIDs)
{
  m_elementController->deleteElements(this->ConvertToNativeList(elementIDs));
}

void CwAPI3D::Net::Bridge::ElementController::JoinElements(List<int>^ elementIDs)
{
  m_elementController->joinElements(this->ConvertToNativeList(elementIDs));
}

void CwAPI3D::Net::Bridge::ElementController::JoinTopLevelElements(List<int>^ elementIDs)
{
  m_elementController->joinTopLevelElements(this->ConvertToNativeList(elementIDs));
}

int CwAPI3D::Net::Bridge::ElementController::CreateRectangularBeamPoints(double width, double height, Vector3D^ p1, Vector3D^ p2, Vector3D^ p3)
{
    return static_cast<int>(m_elementController->createRectangularBeamPoints(
        width, height, p1->ToNative(), p2->ToNative(), p3->ToNative()));
}

int CwAPI3D::Net::Bridge::ElementController::CreateCircularBeamPoints(double diameter, Vector3D^ p1, Vector3D^ p2, Vector3D^ p3)
{
    return static_cast<int>(m_elementController->createCircularBeamPoints(
        diameter, p1->ToNative(), p2->ToNative(), p3->ToNative()));
}

int CwAPI3D::Net::Bridge::ElementController::CreateSquareBeamPoints(double width, Vector3D^ p1, Vector3D^ p2, Vector3D^ p3)
{
    return static_cast<int>(m_elementController->createSquareBeamPoints(
        width, p1->ToNative(), p2->ToNative(), p3->ToNative()));
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::SolderElements(List<int>^ elementIDs)
{
    return ConvertToManagedList(m_elementController->solderElements(this->ConvertToNativeList(elementIDs)));
}

void CwAPI3D::Net::Bridge::ElementController::ConvertBeamToPanel(List<int>^ elementIDs)
{
    m_elementController->convertBeamToPanel(this->ConvertToNativeList(elementIDs));
}

void CwAPI3D::Net::Bridge::ElementController::ConvertPanelToBeam(List<int>^ elementIDs)
{
    m_elementController->convertPanelToBeam(this->ConvertToNativeList(elementIDs));
}

void CwAPI3D::Net::Bridge::ElementController::SplitElements(List<int>^ elementIDs)
{
    m_elementController->splitElements(this->ConvertToNativeList(elementIDs));
}

void CwAPI3D::Net::Bridge::ElementController::MoveElement(List<int>^ elementIDs, Vector3D^ vec)
{
    m_elementController->moveElement(this->ConvertToNativeList(elementIDs), vec->ToNative());
}

List<int>^ CwAPI3D::Net::Bridge::ElementController::CopyElements(List<int>^ elementIDs, Vector3D^ vec)
{
    return ConvertToManagedList(m_elementController->copyElements(this->ConvertToNativeList(elementIDs), vec->ToNative()));
}

void CwAPI3D::Net::Bridge::ElementController::MakeUndo()
{
    m_elementController->makeUndo();
}

void CwAPI3D::Net::Bridge::ElementController::MakeRedo()
{
    m_elementController->makeRedo();
}

bool CwAPI3D::Net::Bridge::ElementController::UnjoinElements(List<int>^ elementIDs)
{
    return m_elementController->unjoinElements(this->ConvertToNativeList(elementIDs));
}

bool CwAPI3D::Net::Bridge::ElementController::UnjoinTopLevelElements(List<int>^ elementIDs)
{
    return m_elementController->unjoinTopLevelElements(this->ConvertToNativeList(elementIDs));
}