// Implementation based on:
// https://thecodehound.com/butterworth-filter-design-in-c/

#define _USE_MATH_DEFINES

#include <assert.h>
#include <my_module/butterworth.h>
#include <cmath>
#include <iostream>
#include <numeric>

Butterworth::Butterworth(int order, double cutoff, double fs)
{
    // Calculate the coefficients
    butter(order, cutoff, fs);

    // Print coefficients
    std::cout << "a: " << std::endl;
    for (int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "b: " << std::endl;
    for (int i = 0; i < b.size(); i++)
    {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;

    // History of samples
    oldSamplesX = std::vector<double>(a.size());
    oldSamplesY = std::vector<double>(a.size());
}

std::vector<std::complex<double>> operator*(const std::vector<std::complex<double>>& p, const std::vector<std::complex<double>>& q)
{
    size_t n = p.size() + q.size() - 1;
    std::vector<std::complex<double>> result(n);
    for (size_t i = 0; i < p.size(); i++)
        for (size_t j = 0; j < q.size(); j++)
            result[i + j] += p[i] * q[j];
    return result;
}

// Emulate Matlab 'poly' function: Calculate the coefficients of the polynomial with the specified roots
std::vector<std::complex<double>> Butterworth::poly(std::vector<std::complex<double>> roots)
{
    std::vector<std::complex<double>> result{1.0};
    for (auto root : roots)
    {
        std::vector<std::complex<double>> factor({-root, 1.0});
        result = result * factor;
    }

    // Matlab returns the highest order coefficients first
    std::reverse(result.begin(), result.end());
    return result;
}

// Emulate Matlab 'sum' function
std::complex<double> Butterworth::sum(const std::vector<std::complex<double>>& v)
{
    return std::accumulate(v.begin(), v.end(), std::complex<double>(0.0, 0.0));
}

// Get the coefficients
void Butterworth::butter(int order, double cutoff, double fs)
{
    std::cout << std::endl << "BUTTER CALLED:" << std::endl << "order : " << order << " cutoff : " << cutoff << " fs : " << fs << std::endl;

    std::vector<std::complex<double>> pa(order);
    std::vector<std::complex<double>> p(order);
    std::vector<std::complex<double>> q(order, -1.0);
    assert(cutoff < fs / 2);  // Cutoff frequency must be less that fs/2

    // I. Find poles of analog filter
    for (int i = 0; i < order; i++)
    {
        int k = i + 1;
        double theta = (2 * k - 1) * M_PI / (2 * order);
        pa[i] = -sin(theta) + std::complex<double>(0.0, 1.0) * cos(theta);
    }

    // II. Scale poles in frequency
    double Fc = fs / M_PI * tan(M_PI * cutoff / fs);
    for (size_t i = 0; i < pa.size(); i++)
        pa[i] *= 2 * M_PI * Fc;

    // III. Find coeffs of digital filter poles and zeros in the z plane
    for (size_t i = 0; i < order; i++)
        p[i] = (1.0 + pa[i] / (2 * fs)) / (1.0 - pa[i] / (2 * fs));

    auto A = poly(p);
    for (size_t i = 0; i < A.size(); i++)
        A[i] = A[i].real();

    auto B = poly(q);
    auto K = sum(A) / sum(B);
    for (size_t i = 0; i < B.size(); i++)
        B[i] *= K;

    for (auto coeff : A)
        a.push_back(coeff.real());
    for (auto coeff : B)
        b.push_back(coeff.real());
}

std::vector<double> Butterworth::filter(std::vector<double> x)
{
    // ASSUMES THE SIZE OF INPUT DATA VECTOR IS LARGER THAN FILTER ORDER

    std::vector<double> y(x.size());

    for (int n = 0; n < x.size(); n++)
    {
        for (int i = 0; i < b.size(); i++)
        {
            if (n - i < 0)
                y[n] += b[i] * oldSamplesX[n - i + oldSamplesX.size()];
            else
                y[n] += b[i] * x[n - i];
        }
        for (int i = 1; i < a.size(); i++)
        {
            if (n - i < 0)
                y[n] -= a[i] * oldSamplesY[n - i + oldSamplesY.size()];
            else
                y[n] -= a[i] * y[n - i];
        }
    }

    // Save old samples (history)
    oldSamplesX = {x.end() - oldSamplesX.size(), x.end()};
    oldSamplesY = {y.end() - oldSamplesY.size(), y.end()};

    return y;
}
