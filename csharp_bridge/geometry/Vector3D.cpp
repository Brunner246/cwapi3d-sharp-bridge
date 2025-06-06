#include "Vector3D.h"
#include "Point3D.h"

#include <cmath>
#include <CwAPI3DTypes.h>
#include <stdexcept>

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::FromPoints(Point3D^ from, Point3D^ to)
{
  return gcnew Vector3D(
    to->X - from->X,
    to->Y - from->Y,
    to->Z - from->Z
  );
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::FromNative(const CwAPI3D::vector3D& vec)
{
  return gcnew Vector3D(vec.mX, vec.mY, vec.mZ);
}

CwAPI3D::vector3D CwAPI3D::Net::Bridge::Vector3D::ToNative()
{
  CwAPI3D::vector3D result;
  result.mX = m_X;
  result.mY = m_Y;
  result.mZ = m_Z;
  return result;
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Vector3D::ToPoint3D()
{
  return gcnew Point3D(m_X, m_Y, m_Z);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::Add(Vector3D^ other)
{
  return gcnew Vector3D(m_X + other->X, m_Y + other->Y, m_Z + other->Z);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::Subtract(Vector3D^ other)
{
  return gcnew Vector3D(m_X - other->X, m_Y - other->Y, m_Z - other->Z);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::Multiply(double scalar)
{
  return gcnew Vector3D(m_X * scalar, m_Y * scalar, m_Z * scalar);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::Divide(double scalar)
{
  constexpr double epsilon = 1e-10;  // Small value for floating-point comparison
  if (std::fabs(scalar) < epsilon)
    throw gcnew System::DivideByZeroException("Cannot divide by near-zero value.");

  return gcnew Vector3D(m_X / scalar, m_Y / scalar, m_Z / scalar);
}

double CwAPI3D::Net::Bridge::Vector3D::DotProduct(Vector3D^ other)
{
  return m_X * other->X + m_Y * other->Y + m_Z * other->Z;
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::CrossProduct(Vector3D^ other)
{
  return gcnew Vector3D(
    m_Y * other->Z - m_Z * other->Y,
    m_Z * other->X - m_X * other->Z,
    m_X * other->Y - m_Y * other->X
  );
}

double CwAPI3D::Net::Bridge::Vector3D::Magnitude()
{
  return System::Math::Sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::Normalize()
{
  double magnitude = Magnitude();
  constexpr double epsilon = 1e-10;

  if (std::fabs(magnitude) < epsilon)
    return gcnew Vector3D(0.0, 0.0, 0.0);

  return Divide(magnitude);
}

double CwAPI3D::Net::Bridge::Vector3D::AngleTo(Vector3D^ other)
{
  double magnitude1 = Magnitude();
  double magnitude2 = other->Magnitude();
  constexpr double epsilon = 1e-10;

  if (std::fabs(magnitude1) < epsilon || std::fabs(magnitude2) < epsilon)
    return 0.0;

  double dotProduct = DotProduct(other);
  double cosAngle = dotProduct / (magnitude1 * magnitude2);

  // Clamp cosAngle to the valid range for acos
  if (cosAngle > 1.0) cosAngle = 1.0;
  if (cosAngle < -1.0) cosAngle = -1.0;

  return System::Math::Acos(cosAngle);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::Negate()
{
  return gcnew Vector3D(-m_X, -m_Y, -m_Z);
}

bool CwAPI3D::Net::Bridge::Vector3D::Equals(System::Object^ obj)
{
  if (obj == nullptr || !obj->GetType()->Equals(Vector3D::typeid))
    return false;

  Vector3D^ other = safe_cast<Vector3D^>(obj);
  constexpr double epsilon = 1e-10;

  return std::fabs(m_X - other->X) < epsilon &&
    std::fabs(m_Y - other->Y) < epsilon &&
    std::fabs(m_Z - other->Z) < epsilon;
}

int CwAPI3D::Net::Bridge::Vector3D::GetHashCode()
{
  return m_X.GetHashCode() ^ m_Y.GetHashCode() ^ m_Z.GetHashCode();
}

System::String^ CwAPI3D::Net::Bridge::Vector3D::ToString()
{
  return System::String::Format("({0}, {1}, {2})", m_X, m_Y, m_Z);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::operator+(Vector3D^ v1, Vector3D^ v2)
{
  return v1->Add(v2);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::operator-(Vector3D^ v1, Vector3D^ v2)
{
  return v1->Subtract(v2);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::operator-(Vector3D^ v)
{
  return v->Negate();
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::operator*(Vector3D^ v, double scalar)
{
  return v->Multiply(scalar);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::operator*(double scalar, Vector3D^ v)
{
  return v->Multiply(scalar);
}

CwAPI3D::Net::Bridge::Vector3D^ CwAPI3D::Net::Bridge::Vector3D::operator/(Vector3D^ v, double scalar)
{
  return v->Divide(scalar);
}

bool CwAPI3D::Net::Bridge::Vector3D::operator==(Vector3D^ v1, Vector3D^ v2)
{
  if (System::Object::ReferenceEquals(v1, v2))
    return true;

  if (System::Object::ReferenceEquals(v1, nullptr) || System::Object::ReferenceEquals(v2, nullptr))
    return false;

  return v1->Equals(v2);
}

bool CwAPI3D::Net::Bridge::Vector3D::operator!=(Vector3D^ v1, Vector3D^ v2)
{
  return !(v1 == v2);
}
