#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cmath>

namespace ParamWorld
{

/**
 * A function that returns a y value for a particular x value.
 */
class Function
{
   public:
    virtual double at(double x) const = 0;
    virtual ~Function()=default;
};

/**
 * Always returns 1.0, despite of the current x.
 */
class Constant : public Function
{
   public:
    double at(double /*unused*/) const { return 1.0; }
    Constant()=default;
};

/**
 * A function that is a linear/constart piecewise.
 */
class Linear : public Function
{
   public:
   /**
    * @brief Constructor
    * @param root when x = root, y is 0.0
    * @param oneIntersect when x = oneIntersect, y is 1.0.
    * In between root and oneIntersect, y is a linear interpolation between 0 and 1.
    */
    Linear(double root, double oneIntersect) : _root(root), _oneIntersect(oneIntersect) {}
    ~Linear()=default;
    double at(double x) const 
    {
        return std::fmin((x - _root) * (1 / (_oneIntersect - _root)), 1.0);
    }
   private:
    double _root;
    double _oneIntersect;
};

/**
 * A logistic function, approaching 1.0.
 */
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
