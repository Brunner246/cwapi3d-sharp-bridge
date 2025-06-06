#pragma once

namespace CwAPI3D
{
  struct vector3D;
}

namespace CwAPI3D::Net::Bridge
{
  /// <summary>
    /// Represents a point or vector in 3D space with X, Y, and Z coordinates.
    /// </summary>
  public ref class Point3D
  {
  private:
    double m_X;
    double m_Y;
    double m_Z;

  public:
    /// <summary>
    /// Gets or sets the X coordinate.
    /// </summary>
    property double X
    {
      double get() { return m_X; }
      void set(double value) { m_X = value; }
    }

    /// <summary>
    /// Gets or sets the Y coordinate.
    /// </summary>
    property double Y
    {
      double get() { return m_Y; }
      void set(double value) { m_Y = value; }
    }

    /// <summary>
    /// Gets or sets the Z coordinate.
    /// </summary>
    property double Z
    {
      double get() { return m_Z; }
      void set(double value) { m_Z = value; }
    }

    /// <summary>
    /// Initializes a new instance of the Point3D class with coordinates (0, 0, 0).
    /// </summary>
    Point3D() : m_X(0.0), m_Y(0.0), m_Z(0.0) {}

    /// <summary>
    /// Initializes a new instance of the Point3D class with the specified coordinates.
    /// </summary>
    /// <param name="x">The X coordinate.</param>
    /// <param name="y">The Y coordinate.</param>
    /// <param name="z">The Z coordinate.</param>
    Point3D(double x, double y, double z) : m_X(x), m_Y(y), m_Z(z) {}

    /// <summary>
    /// Copy constructor. Initializes a new instance of the Point3D class with the values from another Point3D.
    /// </summary>
    /// <param name="other">Another Point3D object whose values are copied.</param>
    Point3D(Point3D^ other) : m_X(other->X), m_Y(other->Y), m_Z(other->Z) {}

    /// <summary>
    /// Creates a Point3D from a native vector3D.
    /// </summary>
    /// <param name="vec">The native vector3D structure.</param>
    /// <returns>A new Point3D object.</returns>
    static Point3D^ FromNative(const CwAPI3D::vector3D& vec);

    /// <summary>
    /// Converts this Point3D to a native vector3D.
    /// </summary>
    /// <returns>A native vector3D structure.</returns>
    CwAPI3D::vector3D ToNative();

    /// <summary>
    /// Calculates the distance between this point and another point.
    /// </summary>
    /// <param name="other">The other point.</param>
    /// <returns>The distance between the two points.</returns>
    double DistanceTo(Point3D^ other);

    /// <summary>
    /// Adds another Point3D to this point.
    /// </summary>
    /// <param name="other">The point to add.</param>
    /// <returns>A new Point3D representing the sum.</returns>
    Point3D^ Add(Point3D^ other);

    /// <summary>
    /// Subtracts another Point3D from this point.
    /// </summary>
    /// <param name="other">The point to subtract.</param>
    /// <returns>A new Point3D representing the difference.</returns>
    Point3D^ Subtract(Point3D^ other);

    /// <summary>
    /// Multiplies this point by a scalar value.
    /// </summary>
    /// <param name="scalar">The scalar value to multiply by.</param>
    /// <returns>A new Point3D representing the product.</returns>
    Point3D^ Multiply(double scalar);

    /// <summary>
    /// Divides this point by a scalar value.
    /// </summary>
    /// <param name="scalar">The scalar value to divide by.</param>
    /// <returns>A new Point3D representing the quotient.</returns>
    /// <exception cref="System::DivideByZeroException">Thrown when scalar is zero.</exception>
    Point3D^ Divide(double scalar);

    /// <summary>
    /// Determines whether this point is equal to another point.
    /// </summary>
    /// <param name="obj">The object to compare with.</param>
    /// <returns>true if the points are equal; otherwise, false.</returns>
    bool Equals(System::Object^ obj) override;

    /// <summary>
    /// Returns a hash code for this point.
    /// </summary>
    /// <returns>A hash code for the current Point3D.</returns>
    int GetHashCode() override;

    /// <summary>
    /// Returns a string representation of this point.
    /// </summary>
    /// <returns>A string representation of the point.</returns>
    System::String^ ToString() override;

    /// <summary>
    /// Operator overload for addition.
    /// </summary>
    static Point3D^ operator+(Point3D^ p1, Point3D^ p2);

    /// <summary>
    /// Operator overload for subtraction.
    /// </summary>
    static Point3D^ operator-(Point3D^ p1, Point3D^ p2);

    /// <summary>
    /// Operator overload for multiplication by scalar.
    /// </summary>
    static Point3D^ operator*(Point3D^ p, double scalar);

    /// <summary>
    /// Operator overload for multiplication by scalar (scalar first).
    /// </summary>
    static Point3D^ operator*(double scalar, Point3D^ p);

    /// <summary>
    /// Operator overload for division by scalar.
    /// </summary>
    static Point3D^ operator/(Point3D^ p, double scalar);

    /// <summary>
    /// Operator overload for equality.
    /// </summary>
    static bool operator==(Point3D^ p1, Point3D^ p2);

    /// <summary>
    /// Operator overload for inequality.
    /// </summary>
    static bool operator!=(Point3D^ p1, Point3D^ p2);
  };
}
