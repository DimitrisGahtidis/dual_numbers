#include <matplotlibcpp.h>

#include <cmath>
#include <iostream>
#include <typeinfo>
#include <type_traits>

namespace dnn
{
    template<typename T>
    class dual_number
    {
    public:

        using value_type = T;

    public:

        

    
    private:

        double re;
        double d;

        static constexpr auto id(const dual_number& v) -> dual_number;
        static constexpr auto id(const int& v) -> dual_number;
        static constexpr auto id(const float& v) -> dual_number;
        static constexpr auto id(const double& v) -> dual_number;

    private:
        constexpr auto add(const dual_number& v) -> dual_number
        { return dual_number{re + v.re, d + v.d}; }

        constexpr auto sub(const dual_number& v) -> dual_number
        { return dual_number{re - v.re, d - v.d}; }
        
        constexpr auto mul(const dual_number& v) -> dual_number
        { return dual_number{re * v.re, d * v.re + re * v.d}; }

        constexpr auto div(const dual_number& v) -> dual_number
        { return dual_number{re / v.re, (d*v.re - re*v.d) / (v.re*v.re)}; }

        static auto dn_pow(const dual_number& v, const double& n) -> dual_number
        { return dual_number{std::pow(v.re, n), n * std::pow(v.re, n-1) * v.d}; }

        static auto dn_sqrt(const dual_number& v) -> dual_number
        { return dual_number{std::sqrt(v.re), 0.5 * std::pow(v.re, -0.5) * v.d}; }

        static auto dn_cos(const dual_number& v) -> dual_number
        { return dual_number{std::cos(v.re), -std::sin(v.re) * v.d}; }

        static auto dn_sin(const dual_number& v) -> dual_number
        { return dual_number{std::sin(v.re), std::cos(v.re) * v.d}; }

        static auto dn_tan(const dual_number& v) -> dual_number
        { return dual_number{std::tan(v.re), v.d/(std::cos(v.re)*std::cos(v.re))}; }

        static auto dn_exp(const dual_number& v) -> dual_number
        { return dual_number{std::exp(v.re), std::exp(v.re) * v.d}; }

        static auto dn_acos(const dual_number& v) -> dual_number
        { return dual_number{std::acos(v.re), v.d/std::sqrt(1-v.re*v.re) }; }

        static auto dn_log(const dual_number& v) -> dual_number
        { return dual_number{std::log(v.re), v.d/v.re}; }

        auto dn_hypot(const dual_number& v) -> dual_number
        { return dual_number{std::hypot(re, v.re), (re * d + v.re * v.d) / std::hypot(re, v.re)}; }
    
    public:
        template <typename T, typename U>
        friend auto operator+ (const T& x, const U& y) -> dual_number
        { return dual_number::id(x).add(dual_number::id(y)); }

        template <typename T, typename U>
        friend auto operator- (const T& x, const U& y) -> dual_number
        { return dual_number::id(x).sub(dual_number::id(y)); }

        template <typename T, typename U>
        friend auto operator* (const T& x, const U& y) -> dual_number
        { return dual_number::id(x).mul(dual_number::id(y)); }

        template <typename T, typename U>
        friend auto operator/ (const T& x, const U& y) -> dual_number
        { return dual_number::id(x).div(dual_number::id(y)); }

        template <typename T>
        static auto pow(const T& x, const double& n) -> dual_number
        { return dual_number::dn_pow(dual_number::id(x), n); }

        template <typename T>
        static auto sqrt(const T& x) -> dual_number
        { return dual_number::dn_sqrt(dual_number::id(x)); }

        template <typename T>
        static auto cos(const T& x) -> dual_number
        { return dual_number::dn_cos(dual_number::id(x)); }

        template <typename T>
        static auto sin(const T& x) -> dual_number
        { return dual_number::dn_sin(dual_number::id(x)); }

        template <typename T>
        static auto tan(const T& x) -> dual_number
        { return dual_number::dn_tan(dual_number::id(x)); }

        template <typename T>
        static auto exp(const T& x) -> dual_number
        { return dual_number::dn_exp(dual_number::id(x)); }

        template <typename T>
        static auto acos(const T& x) -> dual_number
        { return dual_number::dn_acos(dual_number::id(x)); }

        template <typename T>
        static auto log(const T& x) -> dual_number
        { return dual_number::dn_log(dual_number::id(x)); }

        template <typename T, typename U>
        static auto log(const T& x, const U& y) -> dual_number
        { return dual_number::dn_hypot(dual_number::id(x), dual_number::id(y)); }

        friend auto operator<< (std::ostream& os, const dual_number& v) -> std::ostream&
        {
            os << "(" << v.re << "," << v.d << ")";
            return os;
        }

};
}  /// namespace dnn


constexpr auto dual_number::id(const dual_number& v) -> dual_number
{ return v; }

constexpr auto dual_number::id(const int& v) -> dual_number
{ return dual_number{(double)v, 0}; }

constexpr auto dual_number::id(const float& v) -> dual_number
{ return dual_number{(double)v, 0}; }

constexpr auto dual_number::id(const double& v) -> dual_number
{ return dual_number{v, 0}; }

// template<typename real>
// struct dual_number
// {
//     public:
//         real re;
//         double d;

//     template<typename other_real>
//     friend class dual_number;

//     friend auto common_type

//     template <typename X, typename Y>
//     friend auto operator+ (const X& x, const Y& y) -> dual_number
//     { return dual_number<std::common_type<std::decltype(x.re),std::decltype(y.re)>>{x.re + y.re, x.d + y.d}; }

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

        plt::plot(u, v, {{"color", "#1f77b4"}});
        plt::scatter(x, y, 20, {{"color", "#1f77b4"}});
        // plt::show();
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
            dual_number t = dual_number{1.*i/n,1};
            dual_number point[2] = {dual_number::cos(t*(2*M_PI))*t, dual_number::sin(t*(2*M_PI))*t};
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

        plt::plot(u, v, {{"color", "#1f77b4"}});
        plt::scatter(x, y, 20, {{"color", "#1f77b4"}});
        plt::quiver(x, y, dx, dy);
        // plt::show();
        plt::save("dual_number_spiral.png");
    }

    // {
    //     // unit test
    //     auto x = dual_number{2,2};
    //     auto y = dual_number{M_PI,1};

    //     std::cout << x + 2 << std::endl;
    //     std::cout << x - 2 << std::endl;
    //     std::cout << x * 2 << std::endl;
    //     std::cout << x / 2 << std::endl;
    //     std::cout << 2 + x << std::endl;
    //     std::cout << 2 - x << std::endl;
    //     std::cout << 2 * x << std::endl;
    //     std::cout << 2 / x << std::endl;
    //     std::cout << x + y << std::endl;
    //     std::cout << dual_number::pow(x,3) << std::endl;
    //     std::cout << dual_number::sqrt(x) << std::endl;
    //     std::cout << dual_number::cos(y) << std::endl;
    //     std::cout << dual_number::sin(y) << std::endl;
    //     std::cout << dual_number::tan(y) << std::endl;
    //     std::cout << dual_number::exp(x) << std::endl;
    //     std::cout << dual_number::pow(2,3) << std::endl;
    //     std::cout << dual_number::sqrt(M_PI/4) << std::endl;
    //     std::cout << dual_number::cos(M_PI/4) << std::endl;
    //     std::cout << dual_number::sin(M_PI/4) << std::endl;
    //     std::cout << dual_number::tan(M_PI/4) << std::endl;
    //     std::cout << dual_number::exp(2) << std::endl;
    // }

    return 0;
}