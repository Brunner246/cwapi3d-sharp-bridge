using CwAPI3D.Net.Bridge;
using System;
using System.Windows; // Add this for WPF types

namespace sharpLib
{
  public class Initializer
  {
    public static bool Run(IntPtr nativeFactory)
    {
      try
      {
        var wrapper = new CwApi3DFactory(nativeFactory);
        var text = wrapper.GetSomething();
        Console.WriteLine(@"Received from native factory: " + text);

        var elementController = wrapper.GetElementController();
        var elementIDs = elementController.GetVisibleIdentifiableElementIDs();

        elementIDs.ForEach(id => Console.WriteLine($@"element with DB id {id}"));

        //var window = new WpfApp.MainWindow();
        //window.Show();

        Console.WriteLine(@"Managed code executed successfully.");
        return true;
      }
      catch (Exception ex)
      {
        Console.WriteLine(@"Managed initialization failed: " + ex.Message);
        return false;
      }
    }
  }
}