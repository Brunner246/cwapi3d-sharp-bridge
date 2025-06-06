#pragma once

namespace CwAPI3D
{
  struct vector3D;
}

namespace CwAPI3D::Net::Bridge
{
  ref class Point3D;

  /// <summary>
  /// Represents a vector in 3D space with direction and magnitude.
  /// Unlike Point3D which represents a location, Vector3D represents displacement or direction.
  /// </summary>
  public ref class Vector3D
  {
  private:
    double m_X;
    double m_Y;
    double m_Z;

  public:
    /// <summary>
    /// Gets or sets the X component of the vector.
    /// </summary>
    property double X
    {
      double get() { return m_X; }
      void set(double value) { m_X = value; }
    }

    /// <summary>
    /// Gets or sets the Y component of the vector.
    /// </summary>
    property double Y
    {
      double get() { return m_Y; }
      void set(double value) { m_Y = value; }
    }

    /// <summary>
    /// Gets or sets the Z component of the vector.
    /// </summary>
    property double Z
    {
      double get() { return m_Z; }
      void set(double value) { m_Z = value; }
    }

    /// <summary>
    /// Initializes a new instance of the Vector3D class with components (0, 0, 0).
    /// </summary>
    Vector3D() : m_X(0.0), m_Y(0.0), m_Z(0.0) {}

    /// <summary>
    /// Initializes a new instance of the Vector3D class with the specified components.
    /// </summary>
    /// <param name="x">The X component.</param>
    /// <param name="y">The Y component.</param>
    /// <param name="z">The Z component.</param>
    Vector3D(double x, double y, double z) : m_X(x), m_Y(y), m_Z(z) {}

    /// <summary>
    /// Copy constructor. Initializes a new instance of the Vector3D class with the values from another Vector3D.
    /// </summary>
    /// <param name="other">Another Vector3D object whose values are copied.</param>
    Vector3D(Vector3D^ other) : m_X(other->X), m_Y(other->Y), m_Z(other->Z) {}

    /// <summary>
    /// Creates a Vector3D from two points, representing the direction from the first point to the second.
    /// </summary>
    /// <param name="from">The starting point.</param>
    /// <param name="to">The ending point.</param>
    /// <returns>A new Vector3D object representing the direction and magnitude between points.</returns>
    static Vector3D^ FromPoints(Point3D^ from, Point3D^ to);

    /// <summary>
    /// Creates a Vector3D from a native vector3D.
    /// </summary>
    /// <param name="vec">The native vector3D structure.</param>
    /// <returns>A new Vector3D object.</returns>
    static Vector3D^ FromNative(const CwAPI3D::vector3D& vec);

    /// <summary>
    /// Converts this Vector3D to a native vector3D.
    /// </summary>
    /// <returns>A native vector3D structure.</returns>
    CwAPI3D::vector3D ToNative();

    /// <summary>
    /// Converts this Vector3D to a Point3D.
    /// </summary>
    /// <returns>A Point3D with the same coordinate values.</returns>
    Point3D^ ToPoint3D();

    /// <summary>
    /// Adds another Vector3D to this vector.
    /// </summary>
    /// <param name="other">The vector to add.</param>
    /// <returns>A new Vector3D representing the sum.</returns>
    Vector3D^ Add(Vector3D^ other);

    /// <summary>
    /// Subtracts another Vector3D from this vector.
    /// </summary>
    /// <param name="other">The vector to subtract.</param>
    /// <returns>A new Vector3D representing the difference.</returns>
    Vector3D^ Subtract(Vector3D^ other);

    /// <summary>
    /// Multiplies this vector by a scalar value.
    /// </summary>
    /// <param name="scalar">The scalar value to multiply by.</param>
    /// <returns>A new Vector3D representing the product.</returns>
    Vector3D^ Multiply(double scalar);

    /// <summary>
    /// Divides this vector by a scalar value.
    /// </summary>
    /// <param name="scalar">The scalar value to divide by.</param>
    /// <returns>A new Vector3D representing the quotient.</returns>
    /// <exception cref="System::DivideByZeroException">Thrown when scalar is zero.</exception>
    Vector3D^ Divide(double scalar);

    /// <summary>
    /// Calculates the dot product of this vector and another vector.
    /// </summary>
    /// <param name="other">The other vector.</param>
    /// <returns>The dot product.</returns>
    double DotProduct(Vector3D^ other);

    /// <summary>
    /// Calculates the cross product of this vector and another vector.
    /// </summary>
    /// <param name="other">The other vector.</param>
    /// <returns>A new Vector3D representing the cross product.</returns>
    Vector3D^ CrossProduct(Vector3D^ other);

    /// <summary>
    /// Calculates the magnitude (length) of this vector.
    /// </summary>
    /// <returns>The magnitude of the vector.</returns>
    double Magnitude();

    /// <summary>
    /// Returns a normalized version of this vector (with magnitude 1).
    /// </summary>
    /// <returns>A new Vector3D representing the normalized vector.</returns>
    Vector3D^ Normalize();

    /// <summary>
    /// Calculates the angle between this vector and another vector in radians.
    /// </summary>
    /// <param name="other">The other vector.</param>
    /// <returns>The angle in radians.</returns>
    double AngleTo(Vector3D^ other);

    /// <summary>
    /// Creates the opposite direction vector.
    /// </summary>
    /// <returns>A new Vector3D pointing in the opposite direction.</returns>
    Vector3D^ Negate();

    /// <summary>
    /// Determines whether this vector is equal to another vector.
    /// </summary>
    /// <param name="obj">The object to compare with.</param>
    /// <returns>true if the vectors are equal; otherwise, false.</returns>
    bool Equals(System::Object^ obj) override;

    /// <summary>
    /// Returns a hash code for this vector.
    /// </summary>
    /// <returns>A hash code for the current Vector3D.</returns>
    int GetHashCode() override;

    /// <summary>
    /// Returns a string representation of this vector.
    /// </summary>
    /// <returns>A string representation of the vector.</returns>
    System::String^ ToString() override;

    /// <summary>
    /// Operator overload for addition.
    /// </summary>
    static Vector3D^ operator+(Vector3D^ v1, Vector3D^ v2);

    /// <summary>
    /// Operator overload for subtraction.
    /// </summary>
    static Vector3D^ operator-(Vector3D^ v1, Vector3D^ v2);

    /// <summary>
    /// Operator overload for negation.
    /// </summary>
    static Vector3D^ operator-(Vector3D^ v);

    /// <summary>
    /// Operator overload for multiplication by scalar.
    /// </summary>
    static Vector3D^ operator*(Vector3D^ v, double scalar);

    /// <summary>
    /// Operator overload for multiplication by scalar (scalar first).
    /// </summary>
    static Vector3D^ operator*(double scalar, Vector3D^ v);

    /// <summary>
    /// Operator overload for division by scalar.
    /// </summary>
    static Vector3D^ operator/(Vector3D^ v, double scalar);

    /// <summary>
    /// Operator overload for equality.
    /// </summary>
    static bool operator==(Vector3D^ v1, Vector3D^ v2);

    /// <summary>
    /// Operator overload for inequality.
    /// </summary>
    static bool operator!=(Vector3D^ v1, Vector3D^ v2);
  };
}

