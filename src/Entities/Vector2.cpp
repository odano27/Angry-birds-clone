#include "Vector2.h"

Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, double t) {
  return a * t + (1.0 - t) * b;
}

Vector2::operator sf::Vector2f() const {
  return {static_cast<float>(x), static_cast<float>(y)};
}

Vector2 Vector2::operator+(const Vector2& a) const {
  return {x + a.x, y + a.y};
}

Vector2 Vector2::operator+(const sf::Vector2f& a) const {
  return {x + a.x, y + a.y};
}

Vector2 Vector2::operator-(const sf::Vector2f& a) const {
  return {x - a.x, y - a.y};
}

Vector2 Vector2::operator-(const Vector2& a) const {
  return {x - a.x, y - a.y};
}

Vector2 Vector2::operator-(float a) const { return {x - a, y - a}; }

Vector2 Vector2::operator/(int a) const { return {x / a, y / a}; }

Vector2 operator*(double a, const Vector2& b) { return {a * b.x, a * b.y}; }

Vector2 operator*(const Vector2& a, double b) { return {a.x * b, a.y * b}; }

Vector2 operator+(double a, const Vector2& b) { return {b.x + a, b.y + a}; }

Vector2 operator+(const Vector2& a, double b) { return {a.x + b, a.y + b}; }

std::ostream& operator<<(std::ostream& out, const Vector2& a) {
  out << "(" << a.x << ", " << a.y << ")";
  return out;
}
