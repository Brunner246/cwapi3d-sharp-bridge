#pragma once

namespace CwAPI3D
{
  struct vector3D;
}

namespace CwAPI3D::Net::Bridge
{
  ref class Point3D;
  ref class Vector3D;

  /// <summary>
  /// Represents a plane in 3D space defined by a point and a normal vector.
  /// </summary>
  public ref class Plane3D
  {
  private:
    Point3D^ m_Point;
    Vector3D^ m_Normal;
    double m_D; // Distance from origin in the plane equation: Ax + By + Cz + D = 0

    void CalculateD();

  public:
    /// <summary>
    /// Gets or sets a point on the plane.
    /// </summary>
    property Point3D^ Point
    {
      Point3D^ get() { return m_Point; }
      void set(Point3D^ value);
    }

    /// <summary>
    /// Gets or sets the normal vector of the plane.
    /// </summary>
    property Vector3D^ Normal
    {
      Vector3D^ get() { return m_Normal; }
      void set(Vector3D^ value);
    }

    /// <summary>
    /// Gets the D component of the plane equation: Ax + By + Cz + D = 0,
    /// where A, B, and C are the components of the normal vector.
    /// </summary>
    property double D
    {
      double get() { return m_D; }
    }

    /// <summary>
    /// Initializes a new instance of the Plane3D class with default values.
    /// Point at the origin and normal along the Z-axis.
    /// </summary>
    Plane3D();

    /// <summary>
    /// Initializes a new instance of the Plane3D class with the specified point and normal.
    /// </summary>
    /// <param name="point">A point on the plane.</param>
    /// <param name="normal">The normal vector of the plane.</param>
    Plane3D(Point3D^ point, Vector3D^ normal);

    /// <summary>
    /// Initializes a new instance of the Plane3D class with three points.
    /// </summary>
    /// <param name="p1">First point on the plane.</param>
    /// <param name="p2">Second point on the plane.</param>
    /// <param name="p3">Third point on the plane.</param>
    /// <exception cref="System::ArgumentException">Thrown when the points are collinear.</exception>
    Plane3D(Point3D^ p1, Point3D^ p2, Point3D^ p3);

    /// <summary>
    /// Copy constructor. Initializes a new instance of the Plane3D class with the values from another Plane3D.
    /// </summary>
    /// <param name="other">Another Plane3D object whose values are copied.</param>
    Plane3D(Plane3D^ other);

    /// <summary>
    /// Creates a plane from the coefficients of the plane equation: Ax + By + Cz + D = 0.
    /// </summary>
    /// <param name="a">A coefficient (normal X component).</param>
    /// <param name="b">B coefficient (normal Y component).</param>
    /// <param name="c">C coefficient (normal Z component).</param>
    /// <param name="d">D coefficient.</param>
    /// <returns>A new Plane3D object.</returns>
    static Plane3D^ FromCoefficients(double a, double b, double c, double d);

    /// <summary>
    /// Calculates the distance from a point to this plane (signed distance).
    /// </summary>
    /// <param name="point">The point to calculate distance from.</param>
    /// <returns>The signed distance from the point to the plane.</returns>
    double DistanceTo(Point3D^ point);

    /// <summary>
    /// Determines whether a point lies on this plane within the specified epsilon.
    /// </summary>
    /// <param name="point">The point to check.</param>
    /// <param name="epsilon">The tolerance value.</param>
    /// <returns>true if the point lies on the plane; otherwise, false.</returns>
    bool ContainsPoint(Point3D^ point, double epsilon);

    /// <summary>
    /// Determines whether a point lies on this plane using default epsilon.
    /// </summary>
    /// <param name="point">The point to check.</param>
    /// <returns>true if the point lies on the plane; otherwise, false.</returns>
    bool ContainsPoint(Point3D^ point);

    /// <summary>
    /// Projects a point onto this plane.
    /// </summary>
    /// <param name="point">The point to project.</param>
    /// <returns>The projected point.</returns>
    Point3D^ ProjectPoint(Point3D^ point);

    /// <summary>
    /// Determines the intersection point of a line with this plane.
    /// </summary>
    /// <param name="lineStart">The start point of the line.</param>
    /// <param name="lineEnd">The end point of the line.</param>
    /// <param name="intersectionPoint">When this method returns, contains the intersection point if successful.</param>
    /// <returns>true if the line intersects the plane; otherwise, false.</returns>
    bool IntersectLine(Point3D^ lineStart, Point3D^ lineEnd, Point3D^% intersectionPoint);

    /// <summary>
    /// Determines whether this plane is parallel to another plane.
    /// </summary>
    /// <param name="other">The other plane to check.</param>
    /// <param name="epsilon">The tolerance value.</param>
    /// <returns>true if the planes are parallel; otherwise, false.</returns>
    bool IsParallelTo(Plane3D^ other, double epsilon);

    /// <summary>
    /// Determines whether this plane is parallel to another plane using default epsilon.
    /// </summary>
    /// <param name="other">The other plane to check.</param>
    /// <returns>true if the planes are parallel; otherwise, false.</returns>
    bool IsParallelTo(Plane3D^ other);

    /// <summary>
    /// Calculates the line of intersection between this plane and another plane.
    /// </summary>
    /// <param name="other">The other plane.</param>
    /// <param name="linePoint">When this method returns, contains a point on the intersection line if successful.</param>
    /// <param name="lineDirection">When this method returns, contains the direction vector of the intersection line if successful.</param>
    /// <returns>true if the planes intersect; otherwise, false (when planes are parallel).</returns>
    bool IntersectPlane(Plane3D^ other, Point3D^% linePoint, Vector3D^% lineDirection);

    /// <summary>
    /// Determines whether this plane is equal to another plane.
    /// </summary>
    /// <param name="obj">The object to compare with.</param>
    /// <returns>true if the planes are equal; otherwise, false.</returns>
    bool Equals(System::Object^ obj) override;

    /// <summary>
    /// Returns a hash code for this plane.
    /// </summary>
    /// <returns>A hash code for the current Plane3D.</returns>
    int GetHashCode() override;

    /// <summary>
    /// Returns a string representation of this plane.
    /// </summary>
    /// <returns>A string representation of the plane.</returns>
    System::String^ ToString() override;

    /// <summary>
    /// Operator overload for equality.
    /// </summary>
    static bool operator==(Plane3D^ p1, Plane3D^ p2);

    /// <summary>
    /// Operator overload for inequality.
    /// </summary>
    static bool operator!=(Plane3D^ p1, Plane3D^ p2);
  };
}
