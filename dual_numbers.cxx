#include <iostream>
#include <cmath>
#include "matplotlibcpp.h"
#include <typeinfo>
#include <type_traits>


struct dn
{
    public:
        double re;
        double d;

        static constexpr auto id(const dn& v) -> dn;
        static constexpr auto id(const int& v) -> dn;
        static constexpr auto id(const float& v) -> dn;
        static constexpr auto id(const double& v) -> dn;

    private:
        constexpr auto add(const dn& v) -> dn
        { return dn{re + v.re, d + v.d}; }

        constexpr auto sub(const dn& v) -> dn
        { return dn{re - v.re, d - v.d}; }
        
        constexpr auto mul(const dn& v) -> dn
        { return dn{re * v.re, d*v.re + re*v.d}; }

        constexpr auto div(const dn& v) -> dn
        { return dn{re/v.re, (d*v.re - re*v.d)/(v.re*v.re)}; }

        static auto dn_pow(const dn& v, const double& n) -> dn
        { return dn{std::pow(v.re, n), n * std::pow(v.re, n-1) * v.d}; }

        static auto dn_sqrt(const dn& v) -> dn
        { return dn{std::sqrt(v.re), 0.5 * std::pow(v.re, -0.5) * v.d}; }

        static auto dn_cos(const dn& v) -> dn
        { return dn{std::cos(v.re), -std::sin(v.re) * v.d}; }

        static auto dn_sin(const dn& v) -> dn
        { return dn{std::sin(v.re), std::cos(v.re) * v.d}; }

        static auto dn_tan(const dn& v) -> dn
        { return dn{std::tan(v.re), v.d/(std::cos(v.re)*std::cos(v.re))}; }

        static auto dn_exp(const dn& v) -> dn
        { return dn{std::exp(v.re), std::exp(v.re) * v.d}; }

        static auto dn_acos(const dn& v) -> dn
        { return dn{std::acos(v.re), v.d/std::sqrt(1-v.re*v.re) }; }

        static auto dn_log(const dn& v) -> dn
        { return dn{std::log(v.re), v.d/v.re}; }

        auto dn_hypot(const dn& v) -> dn
        { return dn{std::hypot(re, v.re), (re * d + v.re * v.d)/std::hypot(re, v.re)}; }
    
    public:
        template <typename T, typename U>
        friend auto operator+ (const T& x, const U& y) -> dn
        { return dn::id(x).add(dn::id(y)); }

        template <typename T, typename U>
        friend auto operator- (const T& x, const U& y) -> dn
        { return dn::id(x).sub(dn::id(y)); }

        template <typename T, typename U>
        friend auto operator* (const T& x, const U& y) -> dn
        { return dn::id(x).mul(dn::id(y)); }

        template <typename T, typename U>
        friend auto operator/ (const T& x, const U& y) -> dn
        { return dn::id(x).div(dn::id(y)); }

        template <typename T>
        static auto pow(const T& x, const double& n) -> dn
        { return dn::dn_pow(dn::id(x), n); }

        template <typename T>
        static auto sqrt(const T& x) -> dn
        { return dn::dn_sqrt(dn::id(x)); }

        template <typename T>
        static auto cos(const T& x) -> dn
        { return dn::dn_cos(dn::id(x)); }

        template <typename T>
        static auto sin(const T& x) -> dn
        { return dn::dn_sin(dn::id(x)); }

        template <typename T>
        static auto tan(const T& x) -> dn
        { return dn::dn_tan(dn::id(x)); }

        template <typename T>
        static auto exp(const T& x) -> dn
        { return dn::dn_exp(dn::id(x)); }

        template <typename T>
        static auto acos(const T& x) -> dn
        { return dn::dn_acos(dn::id(x)); }

        template <typename T>
        static auto log(const T& x) -> dn
        { return dn::dn_log(dn::id(x)); }

        template <typename T, typename U>
        static auto log(const T& x, const U& y) -> dn
        { return dn::dn_hypot(dn::id(x), dn::id(y)); }

        friend auto operator<< (std::ostream& os, const dn& v) -> std::ostream&
        {
            os << "(" << v.re << "," << v.d << ")";
            return os;
        }

};

constexpr auto dn::id(const dn& v) -> dn
{ return v; }

constexpr auto dn::id(const int& v) -> dn
{ return dn{(double)v, 0}; }

constexpr auto dn::id(const float& v) -> dn
{ return dn{(double)v, 0}; }

constexpr auto dn::id(const double& v) -> dn
{ return dn{v, 0}; }

// template<typename real>
// struct dn
// {
//     public:
//         real re;
//         double d;

//     template<typename other_real>
//     friend class dn;

//     friend auto common_type

//     template <typename X, typename Y>
//     friend auto operator+ (const X& x, const Y& y) -> dn
//     { return dn<std::common_type<std::decltype(x.re),std::decltype(y.re)>>{x.re + y.re, x.d + y.d}; }

// };


namespace plt = matplotlibcpp;
auto main() -> int
{
    // Here I parametrize a spiral the code is simple as it's just a circle with increasing radius over time
    {
        plt::backend("tkagg");
        int n = 1000;
        int samples = 20;

        std::vector<double> u(n), v(n);
        std::vector<double> x(samples), y(samples), dx(samples), dy(samples);
        for (int i = 0; i < n; ++i)
        {
            double t = double{1.*i/n};
            double point[2] = {std::cos(t*(2*M_PI))*t, std::sin(t*(2*M_PI))*t};
            if (i%(n/samples) == 0)
            {
                x.at(i/(n/samples)) = point[0];
                y.at(i/(n/samples)) = point[1];
            }
            u.at(i) = point[0];
            v.at(i) = point[1];

        }

        plt::plot(u, v);
        plt::scatter(x, y, 20);
        plt::show();
        plt::save("spiral.png");
    }

    // Here I change the above code in order to extract the tangent vector information from the sampled points.
    // We can see that there is very little code alteration, by design the old code should look similar to the new one.
    {
        plt::backend("tkagg");
        int n = 1000;
        int samples = 20;

        std::vector<double> u(n), v(n);
        std::vector<double> x(samples), y(samples), dx(samples), dy(samples);
        for (int i = 0; i < n; ++i)
        {
            dn t = dn{1.*i/n,1};
            dn point[2] = {dn::cos(t*(2*M_PI))*t, dn::sin(t*(2*M_PI))*t};
            if (i%(n/samples) == 0)
            {
                double magnitude = 1; // std::hypot(point[0].d, point[1].d);
                x.at(i/(n/samples)) = point[0].re;
                y.at(i/(n/samples)) = point[1].re;
                dx.at(i/(n/samples)) = point[0].d/magnitude;
                dy.at(i/(n/samples)) = point[1].d/magnitude;
            }
            u.at(i) = point[0].re;
            v.at(i) = point[1].re;

        }

        plt::plot(u, v);
        plt::scatter(x, y, 20);
        plt::quiver(x, y, dx, dy);
        plt::show();
        plt::save("dual_number_spiral.png");
    }

    // {
    //     // unit test
    //     auto x = dn{2,2};
    //     auto y = dn{M_PI,1};

    //     std::cout << x + 2 << std::endl;
    //     std::cout << x - 2 << std::endl;
    //     std::cout << x * 2 << std::endl;
    //     std::cout << x / 2 << std::endl;
    //     std::cout << 2 + x << std::endl;
    //     std::cout << 2 - x << std::endl;
    //     std::cout << 2 * x << std::endl;
    //     std::cout << 2 / x << std::endl;
    //     std::cout << x + y << std::endl;
    //     std::cout << dn::pow(x,3) << std::endl;
    //     std::cout << dn::sqrt(x) << std::endl;
    //     std::cout << dn::cos(y) << std::endl;
    //     std::cout << dn::sin(y) << std::endl;
    //     std::cout << dn::tan(y) << std::endl;
    //     std::cout << dn::exp(x) << std::endl;
    //     std::cout << dn::pow(2,3) << std::endl;
    //     std::cout << dn::sqrt(M_PI/4) << std::endl;
    //     std::cout << dn::cos(M_PI/4) << std::endl;
    //     std::cout << dn::sin(M_PI/4) << std::endl;
    //     std::cout << dn::tan(M_PI/4) << std::endl;
    //     std::cout << dn::exp(2) << std::endl;
    // }

    return 0;
}