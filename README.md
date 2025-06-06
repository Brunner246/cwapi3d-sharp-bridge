# CwAPI3D C# Bridge

This project provides a managed C# wrapper around the native CwAPI3D C++ API, allowing .NET applications to interact
with the CwAPI3D library.

## Project Overview

The C# bridge uses C++/CLI to create a wrapper layer that translates between the managed .NET world and the unmanaged
C++ API. This allows C# applications to use the CwAPI3D functionality through a clean, type-safe interface.

## Setup Instructions

### Prerequisites

- Visual Studio 2019 or newer with:
    - Desktop development with C++ workload
    - .NET desktop development workload
    - C++/CLI support component
- CwAPI3D (ensure you have the headers)

### Project Configuration

1. **Clone the repository**

   ```
   git clone <repository-url>
   cd csharp_bridge
   ```

2. **Configure include and library paths**

    - Open the solution in Visual Studio
    - Right-click on the `csharp_bridge` project and select "Properties"
    - Navigate to C/C++ > General > Additional Include Directories
    - Add the path to the CwAPI3D headers
    - Navigate to Linker > General > Additional Library Directories
    - Add the path to the CwAPI3D libraries

3. **Set the correct runtime library**

    - In project properties, go to C/C++ > Code Generation > Runtime Library
    - Select the appropriate option (e.g., Multi-threaded DLL (/MD))

4. **Build the solution**

    - Select the appropriate configuration (Debug/Release) and platform
    - Build the solution (F7 or Ctrl+Shift+B)

## Debugging the Project

### Debugging the C++/CLI Project

### TODO

### Debugging Tips

- **Watch for memory leaks**: Since you're bridging between managed and unmanaged code, carefully monitor memory
  management.
- **Use the Locals and Watch windows**: These help track the state of variables as you step through the code.
- **Use the Call Stack window**: Helpful for understanding the flow of execution between managed and native code.
- **Check Output window**: Look for any runtime errors or messages.

## Basic Usage

To use the CwAPI3D bridge in your C# project:

1. Add a reference to the `csharp_bridge.dll`
2. Initialize the API:

```csharp
using CwAPI3D.Net.Bridge;

public class Initializer
    {
        public static bool Run(IntPtr nativeFactory)
        {
            
            // ....
            // Initialize API
            var wrapper = new CwApi3DFactory(nativeFactory);
            var text = wrapper.GetSomething();
            Console.WriteLine(@"Received from native factory: " + text);
            
            // Get specific controller
            var elementController = apiInstance.GetElementController();
            
            // Use the controller
            var allElements = elementController.GetAllIdentifiableElementIDs();
   }
}
```

## Class Structure

- `CwAPI3DFactory`: Main entry point for creating an API instance
- `ElementController`: Wrapper for element management functions
- Additional controllers for other API functionality

## Common Issues and Troubleshooting

- **DllNotFoundException**: Ensure all native DLLs are in the path or in the same directory as your executable
- **AccessViolationException**: Often indicates a memory issue, check pointer handling

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## License

### TODO
