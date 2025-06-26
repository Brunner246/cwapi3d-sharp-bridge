using CwAPI3D.Net.Bridge;
using System;
using System.Linq;
using System.Windows;

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
                
                //TODO impelmentation of attribute controller
                // var filteredIDs = elementIDs.FindAll(id => attributeController.GetName(id) == "SomeAttributeName");
                
                // var ids = from id in elementIDs
                //     where attributeController.GetName(id) == "SomeAttributeName"
                //     select id;

                Point3D point1 = new Point3D(0, 0, 0);
                Point3D point2 = new Point3D(1000.0, 0.0, 0.0);
                Vector3D vec = Vector3D.FromPoints(point1, point2).Normalize();
                Console.WriteLine($@"Vector from {point1} to {point2} is {vec}");
                
                var lambda = new Func<Point3D, Point3D, Vector3D>((p1, p2) =>
                {
                    var vector = Vector3D.FromPoints(p1, p2);
                    return vector.Normalize();
                });
                
                var result = lambda(point1, point2);
                Console.WriteLine(@"Received from native factory: " + result);

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