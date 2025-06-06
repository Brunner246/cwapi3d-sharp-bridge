#pragma once

//using namespace System;
using namespace System::Collections::Generic;

namespace CwAPI3D
{
    namespace Interfaces
    {
        class ICwAPI3DControllerFactory;
        class ICwAPI3DElementIDList;
        class ICwAPI3DElementController;
    }
}

namespace CwAPI3D::Net::Bridge
{
    ref class Vector3D;

    public ref class ElementController
    {
        Interfaces::ICwAPI3DControllerFactory* m_controllerFactory;
        Interfaces::ICwAPI3DElementController* m_elementController;

        //TODO: move into separate utility class (wrapper)
        static List<int>^ ConvertToManagedList(Interfaces::ICwAPI3DElementIDList* nativeList);
        Interfaces::ICwAPI3DElementIDList* ConvertToNativeList(List<int>^ ids);

    public:
        explicit ElementController(Interfaces::ICwAPI3DControllerFactory* nativePtr);

        List<int>^ GetAllIdentifiableElementIDs();
        List<int>^ GetVisibleIdentifiableElementIDs();
        List<int>^ GetInvisibleIdentifiableElementIDs();
        List<int>^ GetActiveIdentifiableElementIDs();
        List<int>^ GetInactiveAllIdentifiableElementIDs();
        List<int>^ GetInactiveVisibleIdentifiableElementIDs();
        void DeleteElements(List<int>^ elementIDs);
        void JoinElements(List<int>^ elementIDs);
        void JoinTopLevelElements(List<int>^ elementIDs);


        int CreateRectangularBeamPoints(double width, double height, Vector3D^ p1, Vector3D^ p2, Vector3D^ p3);
        int CreateCircularBeamPoints(double diameter, Vector3D^ p1, Vector3D^ p2, Vector3D^ p3);
        int CreateSquareBeamPoints(double width, Vector3D^ p1, Vector3D^ p2, Vector3D^ p3);

        List<int>^ SolderElements(List<int>^ elementIDs);
        void ConvertBeamToPanel(List<int>^ elementIDs);
        void ConvertPanelToBeam(List<int>^ elementIDs);
        void SplitElements(List<int>^ elementIDs);


        void MoveElement(List<int>^ elementIDs, Vector3D^ vec);
        List<int>^ CopyElements(List<int>^ elementIDs, Vector3D^ vec);

        void MakeUndo();
        void MakeRedo();
        
        bool UnjoinElements(List<int>^ elementIDs);
        bool UnjoinTopLevelElements(List<int>^ elementIDs);
        
    };
}