#pragma once

#include <SFML/System.hpp>
#include <iostream>

struct Vector2 {
  double x;
  double y;

  static Vector2 zero() { return {0.0, 0.0}; }
  static Vector2 one() { return {1.0, 1.0}; }
  static Vector2 up() { return {0.0, 1.0}; }
  static Vector2 down() { return {0.0, -1.0}; }
  static Vector2 left() { return {-1.0, 0.0}; }
  static Vector2 right() { return {1.0, 0.0}; }

  static Vector2 lerp(const Vector2& a, const Vector2& b, double t);

  operator sf::Vector2f() const;

  Vector2 operator+(const Vector2& a) const;
  Vector2 operator-(const Vector2& a) const;
  Vector2 operator-(float a) const;
  Vector2 operator/(int a) const;

  friend Vector2 operator*(double a, const Vector2& b);
  friend Vector2 operator*(const Vector2& a, double b);

  friend Vector2 operator+(double a, const Vector2& b);
  friend Vector2 operator+(const Vector2& a, double b);

  friend std::ostream& operator<<(std::ostream& out, const Vector2& a);
};