#include "Point3D.h"

#include <cmath>
#include <CwAPI3DTypes.h>
#include <stdexcept>

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::FromNative(const CwAPI3D::vector3D& vec)
{
  return gcnew Point3D(vec.mX, vec.mY, vec.mZ);
}

CwAPI3D::vector3D CwAPI3D::Net::Bridge::Point3D::ToNative()
{
  CwAPI3D::vector3D result;
  result.mX = m_X;
  result.mY = m_Y;
  result.mZ = m_Z;
  return result;
}

double CwAPI3D::Net::Bridge::Point3D::DistanceTo(Point3D^ other)
{
  double dx = other->X - m_X;
  double dy = other->Y - m_Y;
  double dz = other->Z - m_Z;
  return System::Math::Sqrt(dx * dx + dy * dy + dz * dz);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::Add(Point3D^ other)
{
  return gcnew Point3D(m_X + other->X, m_Y + other->Y, m_Z + other->Z);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::Subtract(Point3D^ other)
{
  return gcnew Point3D(m_X - other->X, m_Y - other->Y, m_Z - other->Z);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::Multiply(double scalar)
{
  return gcnew Point3D(m_X * scalar, m_Y * scalar, m_Z * scalar);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::Divide(double scalar)
{
  constexpr double epsilon = 1e-10;  // Small value for floating-point comparison
  if (std::abs(scalar) < epsilon)
    throw gcnew System::DivideByZeroException("Cannot divide by zero.");

  return gcnew Point3D(m_X / scalar, m_Y / scalar, m_Z / scalar);
}

bool CwAPI3D::Net::Bridge::Point3D::Equals(System::Object^ obj)
{
  if (obj == nullptr || !obj->GetType()->Equals(Point3D::typeid))
    return false;

  Point3D^ other = safe_cast<Point3D^>(obj); // https://learn.microsoft.com/en-us/cpp/extensions/safe-cast-cpp-component-extensions?view=msvc-170
  constexpr double epsilon = 1e-10;

  return std::fabs(m_X - other->X) < epsilon &&
    std::fabs(m_Y - other->Y) < epsilon &&
    std::fabs(m_Z - other->Z) < epsilon;

}

int CwAPI3D::Net::Bridge::Point3D::GetHashCode()
{
  return m_X.GetHashCode() ^ m_Y.GetHashCode() ^ m_Z.GetHashCode();
}

System::String^ CwAPI3D::Net::Bridge::Point3D::ToString()
{
  return System::String::Format("({0}, {1}, {2})", m_X, m_Y, m_Z);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::operator+(Point3D^ p1, Point3D^ p2)
{
  return p1->Add(p2);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::operator-(Point3D^ p1, Point3D^ p2)
{
  return p1->Subtract(p2);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::operator*(Point3D^ p, double scalar)
{
  return p->Multiply(scalar);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::operator*(double scalar, Point3D^ p)
{
  return p->Multiply(scalar);
}

CwAPI3D::Net::Bridge::Point3D^ CwAPI3D::Net::Bridge::Point3D::operator/(Point3D^ p, double scalar)
{
  return p->Divide(scalar);
}

bool CwAPI3D::Net::Bridge::Point3D::operator==(Point3D^ p1, Point3D^ p2)
{
  if (System::Object::ReferenceEquals(p1, p2))
    return true;

  if (System::Object::ReferenceEquals(p1, nullptr) || System::Object::ReferenceEquals(p2, nullptr))
    return false;

  return p1->Equals(p2);
}

bool CwAPI3D::Net::Bridge::Point3D::operator!=(Point3D^ p1, Point3D^ p2)
{
  return !(p1 == p2);
}
