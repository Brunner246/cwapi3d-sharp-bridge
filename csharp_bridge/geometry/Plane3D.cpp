#include "Plane3D.h"
#include "Point3D.h"
#include "Vector3D.h"

#include <cmath>
#include <CwAPI3DTypes.h>
#include <stdexcept>

namespace CwAPI3D::Net::Bridge
{
  void Plane3D::CalculateD()
  {
    // In the equation Ax + By + Cz + D = 0, D = -(A*x0 + B*y0 + C*z0) where (x0, y0, z0) is a point on the plane
    m_D = -(m_Normal->X * m_Point->X + m_Normal->Y * m_Point->Y + m_Normal->Z * m_Point->Z);
  }

  void Plane3D::Point::set(Point3D^ value)
  {
    if (value == nullptr)
      throw gcnew System::ArgumentNullException("value");

    m_Point = value;
    CalculateD();
  }

  void Plane3D::Normal::set(Vector3D^ value)
  {
    if (value == nullptr)
      throw gcnew System::ArgumentNullException("value");

    constexpr double epsilon = 1e-10;
    double magnitude = value->Magnitude();

    if (std::fabs(magnitude) < epsilon)
      throw gcnew System::ArgumentException("Normal vector cannot be zero length.");

    m_Normal = value->Normalize();
    CalculateD();
  }

  Plane3D::Plane3D()
  {
    m_Point = gcnew Point3D(0.0, 0.0, 0.0);
    m_Normal = gcnew Vector3D(0.0, 0.0, 1.0); // Default normal along Z-axis
    CalculateD();
  }

  Plane3D::Plane3D(Point3D^ point, Vector3D^ normal)
  {
    if (point == nullptr)
      throw gcnew System::ArgumentNullException("point");
    if (normal == nullptr)
      throw gcnew System::ArgumentNullException("normal");

    constexpr double epsilon = 1e-10;
    double magnitude = normal->Magnitude();

    if (std::fabs(magnitude) < epsilon)
      throw gcnew System::ArgumentException("Normal vector cannot be zero length.");

    m_Point = point;
    m_Normal = normal->Normalize();
    CalculateD();
  }

  Plane3D::Plane3D(Point3D^ p1, Point3D^ p2, Point3D^ p3)
  {
    if (p1 == nullptr || p2 == nullptr || p3 == nullptr)
      throw gcnew System::ArgumentNullException("Points cannot be null.");

    // Calculate vectors along the edges of the triangle
    Vector3D^ v1 = Vector3D::FromPoints(p1, p2);
    Vector3D^ v2 = Vector3D::FromPoints(p1, p3);

    Vector3D^ normal = v1->CrossProduct(v2);

    constexpr double epsilon = 1e-10;
    double magnitude = normal->Magnitude();

    if (std::fabs(magnitude) < epsilon)
      throw gcnew System::ArgumentException("Points are collinear and do not define a plane.");

    m_Point = p1;
    m_Normal = normal->Normalize();
    CalculateD();
  }

  Plane3D::Plane3D(Plane3D^ other)
  {
    if (other == nullptr)
      throw gcnew System::ArgumentNullException("other");

    m_Point = gcnew Point3D(other->Point);
    m_Normal = gcnew Vector3D(other->Normal);
    m_D = other->D;
  }

  Plane3D^ Plane3D::FromCoefficients(double a, double b, double c, double d)
  {
    constexpr double epsilon = 1e-10;
    double magnitude = std::sqrt(a * a + b * b + c * c);

    if (std::fabs(magnitude) < epsilon)
      throw gcnew System::ArgumentException("Normal vector components (A, B, C) cannot all be zero.");

    // Create the normal vector from the coefficients
    Vector3D^ normal = gcnew Vector3D(a, b, c);

    // Find a point on the plane: choose a non-zero component of the normal
    Point3D^ point;
    if (std::fabs(a) >= epsilon)
      point = gcnew Point3D(-d / a, 0.0, 0.0);
    else if (std::fabs(b) >= epsilon)
      point = gcnew Point3D(0.0, -d / b, 0.0);
    else
      point = gcnew Point3D(0.0, 0.0, -d / c);

    return gcnew Plane3D(point, normal);
  }

  double Plane3D::DistanceTo(Point3D^ point)
  {
    if (point == nullptr)
      throw gcnew System::ArgumentNullException("point");

    // Distance = (Ax + By + Cz + D) / sqrt(A² + B² + C²)
    // Since our normal is already normalized, the denominator is 1
    return m_Normal->X * point->X + m_Normal->Y * point->Y + m_Normal->Z * point->Z + m_D;
  }

  bool Plane3D::ContainsPoint(Point3D^ point, double epsilon)
  {
    if (point == nullptr)
      throw gcnew System::ArgumentNullException("point");

    return std::fabs(DistanceTo(point)) < epsilon;
  }

  bool Plane3D::ContainsPoint(Point3D^ point)
  {
    constexpr double epsilon = 1e-10;
    return ContainsPoint(point, epsilon);
  }

  Point3D^ Plane3D::ProjectPoint(Point3D^ point)
  {
    if (point == nullptr)
      throw gcnew System::ArgumentNullException("point");

    double distance = DistanceTo(point);

    // Project the point onto the plane by moving it along the normal vector
    Vector3D^ projection = m_Normal->Multiply(-distance);

    double x = point->X + projection->X;
    double y = point->Y + projection->Y;
    double z = point->Z + projection->Z;

    return gcnew Point3D(x, y, z);
  }

  bool Plane3D::IntersectLine(Point3D^ lineStart, Point3D^ lineEnd, Point3D^% intersectionPoint)
  {
    if (lineStart == nullptr || lineEnd == nullptr)
      throw gcnew System::ArgumentNullException("Line points cannot be null.");

    // Create direction vector of the line
    Vector3D^ lineDirection = Vector3D::FromPoints(lineStart, lineEnd);
    double lineLength = lineDirection->Magnitude();

    constexpr double epsilon = 1e-10;
    if (std::fabs(lineLength) < epsilon)
      throw gcnew System::ArgumentException("Line has zero length.");

    // Normalize the line direction
    lineDirection = lineDirection->Divide(lineLength);

    // Calculate denominator: dot product of normal and line direction
    double denominator = m_Normal->DotProduct(lineDirection);

    // If denominator is zero (or very close), the line is parallel to the plane
    if (std::fabs(denominator) < epsilon)
    {
      intersectionPoint = nullptr;
      return false;
    }

    // Calculate the signed distance from lineStart to the plane
    double distanceToStart = DistanceTo(lineStart);

    // Calculate t, the parameter along the line where intersection occurs
    double t = -distanceToStart / denominator;

    // If t is outside the line segment [0, lineLength], there's no intersection with the segment
    if (t < 0 || t > lineLength)
    {
      intersectionPoint = nullptr;
      return false;
    }

    // Calculate intersection point: lineStart + t * lineDirection
    intersectionPoint = gcnew Point3D(
      lineStart->X + t * lineDirection->X,
      lineStart->Y + t * lineDirection->Y,
      lineStart->Z + t * lineDirection->Z
    );

    return true;
  }

  bool Plane3D::IsParallelTo(Plane3D^ other, double epsilon)
  {
    if (other == nullptr)
      throw gcnew System::ArgumentNullException("other");

    // Two planes are parallel if their normal vectors are parallel
    // Check if cross product magnitude is near zero
    Vector3D^ crossProduct = m_Normal->CrossProduct(other->Normal);
    double magnitude = crossProduct->Magnitude();

    return magnitude < epsilon;
  }

  bool Plane3D::IsParallelTo(Plane3D^ other)
  {
    constexpr double epsilon = 1e-10;
    return IsParallelTo(other, epsilon);
  }

  bool Plane3D::IntersectPlane(Plane3D^ other, Point3D^% linePoint, Vector3D^% lineDirection)
  {
    if (other == nullptr)
      throw gcnew System::ArgumentNullException("other");

    constexpr double epsilon = 1e-10;
    if (IsParallelTo(other, epsilon))
    {
      linePoint = nullptr;
      lineDirection = nullptr;
      return false;
    }

    // Calculate the direction of the intersection line using cross product of normals
    lineDirection = m_Normal->CrossProduct(other->Normal)->Normalize();

    // Calculate a point on the intersection line
    // Set up a system of equations for the point coordinates:
    //   n1·p + d1 = 0  (equation for this plane)
    //   n2·p + d2 = 0  (equation for other plane)
    //   p·v = 0        (arbitrary constraint, pick a component of p to be zero)

    // For numerical stability, we'll set to zero the smallest component of lineDirection
    int zeroComponent;
    if (std::fabs(lineDirection->X) <= std::fabs(lineDirection->Y) &&
      std::fabs(lineDirection->X) <= std::fabs(lineDirection->Z))
      zeroComponent = 0; // Set x = 0
    else if (std::fabs(lineDirection->Y) <= std::fabs(lineDirection->X) &&
      std::fabs(lineDirection->Y) <= std::fabs(lineDirection->Z))
      zeroComponent = 1; // Set y = 0
    else
      zeroComponent = 2; // Set z = 0

    // Solve the system of equations based on which component we're setting to zero
    double a1 = m_Normal->X;
    double b1 = m_Normal->Y;
    double c1 = m_Normal->Z;
    double d1 = m_D;

    double a2 = other->Normal->X;
    double b2 = other->Normal->Y;
    double c2 = other->Normal->Z;
    double d2 = other->D;

    double x = 0, y = 0, z = 0;

    if (zeroComponent == 0)
    {
      x = 0.0;

      // Solve for y and z using the two plane equations
      double det = b1 * c2 - b2 * c1;
      if (std::fabs(det) < epsilon)
      {
        // Fall back to a different approach if this system is singular
        zeroComponent = 1; // Try setting y = 0 instead
      }
      else
      {
        y = (c1 * d2 - c2 * d1) / det;
        z = (b2 * d1 - b1 * d2) / det;
      }
    }

    if (zeroComponent == 1)
    {
      y = 0.0;

      // Solve for x and z using the two plane equations
      double det = a1 * c2 - a2 * c1;
      if (std::fabs(det) < epsilon)
      {
        // Fall back to setting z = 0
        zeroComponent = 2;
      }
      else
      {
        x = (c1 * d2 - c2 * d1) / det;
        z = (a2 * d1 - a1 * d2) / det;
      }
    }

    if (zeroComponent == 2)
    {
      z = 0.0;

      // Solve for x and y using the two plane equations
      double det = a1 * b2 - a2 * b1;
      if (std::fabs(det) < epsilon)
      {
        // This shouldn't happen if planes aren't parallel
        linePoint = nullptr;
        lineDirection = nullptr;
        return false;
      }

      x = (b1 * d2 - b2 * d1) / det;
      y = (a2 * d1 - a1 * d2) / det;
    }

    linePoint = gcnew Point3D(x, y, z);
    return true;
  }

  bool Plane3D::Equals(System::Object^ obj)
  {
    if (obj == nullptr || !obj->GetType()->Equals(Plane3D::typeid))
      return false;

    Plane3D^ other = safe_cast<Plane3D^>(obj);
    constexpr double epsilon = 1e-10;

    // Check if the planes have parallel normals
    if (!IsParallelTo(other, epsilon))
      return false;

    // Check if both planes contain the same point
    return ContainsPoint(other->Point, epsilon);
  }

  int Plane3D::GetHashCode()
  {
    return m_Normal->GetHashCode() ^ m_D.GetHashCode();
  }

  System::String^ Plane3D::ToString()
  {
    return System::String::Format("Plane: {0}x + {1}y + {2}z + {3} = 0",
      m_Normal->X, m_Normal->Y, m_Normal->Z, m_D);
  }

  bool Plane3D::operator==(Plane3D^ p1, Plane3D^ p2)
  {
    if (System::Object::ReferenceEquals(p1, p2))
      return true;

    if (System::Object::ReferenceEquals(p1, nullptr) || System::Object::ReferenceEquals(p2, nullptr))
      return false;

    return p1->Equals(p2);
  }

  bool Plane3D::operator!=(Plane3D^ p1, Plane3D^ p2)
  {
    return !(p1 == p2);
  }
}
