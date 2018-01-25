#ifndef ParamArray_HPP
#define ParamArray_HPP

#include <math.h>
#include <array>

namespace ParamWorld
{
template <int D>
class ParamArray
{
   public:
    ParamArray();
    ParamArray(float repeatElement);
    ParamArray<D> operator+(ParamArray<D> a) const;
    ParamArray<D> operator-(ParamArray<D> a) const;
    ParamArray<D> multiplyElement(ParamArray<D> a) const;
    ParamArray<D> divideElement(ParamArray<D> a) const;
    ParamArray<D> operator/(float c) const;
    ParamArray<D> operator*(float c) const;

    float l2_norm() const;

    float operator[](int index) const;
    float &operator[](int index);

   private:
    std::array<float, D> params;
};

template <int D>
ParamArray<D>::ParamArray()
{
}

template <int D>
ParamArray<D>::ParamArray(float repeatElement)
{
    for (int i = 0; i < D; i++) {
        params[i] = repeatElement;
    }
}

template <int D>
ParamArray<D> ParamArray<D>::operator+(ParamArray<D> a) const
{
    ParamArray<D> toReturn;
    for (int i = 0; i < D; i++) {
        toReturn[i] = (*this)[i] + a[i];
    }
    return toReturn;
}

template <int D>
ParamArray<D> ParamArray<D>::operator-(ParamArray<D> a) const
{
    ParamArray<D> toReturn;
    for (int i = 0; i < D; i++) {
        toReturn[i] = (*this)[i] - a[i];
    }
    return toReturn;
}

template <int D>
ParamArray<D> ParamArray<D>::multiplyElement(ParamArray<D> a) const
{
    ParamArray<D> toReturn;
    for (int i = 0; i < D; i++) {
        toReturn[i] = (*this)[i] * a[i];
    }
    return toReturn;
}

template <int D>
ParamArray<D> ParamArray<D>::divideElement(ParamArray<D> a) const
{
    ParamArray<D> toReturn;
    for (int i = 0; i < D; i++) {
        toReturn[i] = (*this)[i] * a[i];
    }
    return toReturn;
}

template <int D>
ParamArray<D> ParamArray<D>::operator/(float c) const
{
    ParamArray<D> toReturn;
    for (int i = 0; i < D; i++) {
        toReturn[i] = (*this)[i] / c;
    }
    return toReturn;
}

template <int D>
ParamArray<D> ParamArray<D>::operator*(float c) const
{
    ParamArray<D> toReturn;
    for (int i = 0; i < D; i++) {
        toReturn[i] = (*this)[i] * c;
    }
    return toReturn;
}

template <int D>
float ParamArray<D>::l2_norm() const
{
    float sum = 0.0f;
    for (int i = 0; i < D; i++) {
        sum += (*this)[i] * (*this)[i];
    }
    return sqrt(sum);
}

template <int D>
float ParamArray<D>::operator[](int index) const
{
    return params[index];
}

template <int D>
float &ParamArray<D>::operator[](int index)
{
    return params[index];
}
}

#endif
