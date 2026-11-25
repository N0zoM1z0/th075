// Genuine SDK overload chains and ordinary equivalents; original declarations remain unknown.
#include <cmath>
#include <cstdlib>

float ObserveCos(float value) { return std::cos(value); }
float ObserveSin(float value) { return std::sin(value); }
float ObserveAbs(float value) { return std::abs(value); }
float ObserveSqrt(float value) { return std::sqrt(value); }
float ObserveCeil(float value) { return std::ceil(value); }
long ObserveLongAbs(long value) { return std::abs(value); }

float OrdinaryCosFloat(float value) { return static_cast<float>(::cos(static_cast<double>(value))); }
float OrdinarySinFloat(float value) { return static_cast<float>(::sin(static_cast<double>(value))); }
float OrdinaryAbsFloat(float value) { return static_cast<float>(::fabs(static_cast<double>(value))); }
float OrdinarySqrtFloat(float value) { return static_cast<float>(::sqrt(static_cast<double>(value))); }
float OrdinaryCeilFloat(float value) { return static_cast<float>(::ceil(static_cast<double>(value))); }
float OrdinaryCosOverload(float value) { return OrdinaryCosFloat(value); }
float OrdinarySinOverload(float value) { return OrdinarySinFloat(value); }
float OrdinaryAbsOverload(float value) { return OrdinaryAbsFloat(value); }
float OrdinarySqrtOverload(float value) { return OrdinarySqrtFloat(value); }
float OrdinaryCeilOverload(float value) { return OrdinaryCeilFloat(value); }
long OrdinaryLongAbsOverload(long value) { return ::labs(value); }

extern "C" const unsigned long MathOverloadLayout[] = {sizeof(float), sizeof(double), sizeof(int), sizeof(long)};
