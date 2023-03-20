#include <matplotlibcpp.h>

#include <cmath>
#include <iostream>
#include <typeinfo>
#include <type_traits>

namespace dnn
{
    /// @brief 
    /// @tparam T 
    template<typename T>
    class dual_number
    {
    public:

        using value_type = T;

    public:

        explicit constexpr
        dual_number(const value_type& real = value_type{}, const value_type& diff = value_type{}) noexcept
            : m_real{ real }
            , m_diff{ diff }
        { }

        constexpr dual_number(const dual_number&) noexcept   = default;
        constexpr dual_number(dual_number&&) noexcept        = default;

        template<typename U>
        constexpr dual_number(const dual_number<U>& dn) noexcept
            : m_real{ value_type{ dn.real() } }
            , m_diff{ value_type{ dn.diff() } }
        { }

        constexpr auto
        operator= (const value_type& v) noexcept
            -> dual_number&
        {
            m_real { v };
            m_diff { value_type{} };

            return *this;
        }

        constexpr auto
        real() noexcept 
            -> value_type&
        { return m_real; }

        constexpr auto
        real() const noexcept
            -> const value_type&
        { return m_real; }

        constexpr auto
        diff() noexcept 
            -> value_type&
        { return m_diff; }

        constexpr auto
        diff() const noexcept
            -> const value_type&
        { return m_diff; }

        constexpr auto
        operator+= (const value_type& v) noexcept
            -> dual_number&
        {
            m_real += v;
            return *this;
        }

        constexpr auto
        operator-= (const value_type& v) noexcept
            -> dual_number&
        {
            m_real -= v;
            return *this;
        }

        constexpr auto
        operator*= (const value_type& v) noexcept
            -> dual_number&
        {
            m_real *= v;
            m_diff *= v;
            return *this;
        }

        constexpr auto
        operator/= (const value_type& v) noexcept
            -> dual_number&
        {
            m_real /= v;
            m_diff /= v;
            return *this;
        }

        template<typename U>
        constexpr auto
        operator+= (const dual_number<U>& dn) noexcept
            -> dual_number<T>&
        {
            m_real += dn.real();
            m_diff += dn.diff();
            return *this;
        }

        template<typename U>
        constexpr auto
        operator-= (const dual_number<U>& dn) noexcept
            -> dual_number<T>&
        {
            m_real -= dn.real();
            m_diff -= dn.diff();
            return *this;
        }

        template<typename U>
        constexpr auto
        operator*= (const dual_number<U>& dn) noexcept
            -> dual_number<T>&
        {
            
            return *this;
        }

        template<typename U>
        constexpr auto
        operator/= (const dual_number<U>& dn) noexcept
            -> dual_number<T>&
        {
            
            return *this;
        }
    
    private:

        value_type m_real;
        value_type m_diff;
}  /// namespace dnn

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