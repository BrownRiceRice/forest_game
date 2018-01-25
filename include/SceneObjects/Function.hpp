#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cmath>

namespace ParamWorld
{
class Function
{
   public:
    virtual double at(double x) const = 0;
};

// Always at Size 1.0.
class Constant : public Function
{
   public:
    double at(double x) const { return 1.0; }
    Constant() {}
};

class Linear : public Function
{
   public:
    Linear(double root, double oneIntersect) : _root(root), _oneIntersect(oneIntersect) {}
    double at(double x) const { return std::min((x - _root) * (1 / (_oneIntersect - _root)), 1.0); }
   private:
    double _root;
    double _oneIntersect;
};

class Logistic : public Function
{
   public:
    Logistic(double midpoint, double steepness) : _midpoint(midpoint), _steepness(steepness) {}
    double at(double x) const { return 1 / (1 + exp(-_steepness * (x - _midpoint))); }
   private:
    double _midpoint;
    double _steepness;
};
}

#endif
