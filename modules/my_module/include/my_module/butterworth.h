#pragma once
#include <my_module/common.h>
#include <complex>
#include <vector>

class Butterworth
{
public:
    Butterworth(int order, double cutoff, double fs);
    std::vector<double> filter(std::vector<double> x);

private:
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> oldSamplesX;
    std::vector<double> oldSamplesY;

    friend std::vector<std::complex<double>> operator*(const std::vector<std::complex<double>>& p,
                                                       const std::vector<std::complex<double>>& q);
    std::vector<std::complex<double>> poly(std::vector<std::complex<double>> roots);
    std::complex<double> sum(const std::vector<std::complex<double>>& v);

    void butter(int order, double cutoff, double fs);
};
