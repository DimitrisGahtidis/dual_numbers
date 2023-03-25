#ifndef DUAL_NUMBER
#   define DUAL_NUMBER

#include <cmath>
#include <iostream>

namespace dnn
{
    

    template<typename T>
    class dual
    {
    public:

        using base_real_type = T;

    public:

        explicit constexpr
        dual(const base_real_type& re = base_real_type{}, const base_real_type& d = base_real_type{}) noexcept
            : m_re{ re }
            , m_d{ d }
        { }

        constexpr dual(const dual&) noexcept   = default;
        constexpr dual(dual&&) noexcept        = default;

        template<typename other_real_type>
        constexpr dual(const dual<other_real_type>& dn) noexcept
            : m_re{ base_real_type{ dn.re() } }
            , m_d{ base_real_type{ dn.d() } }
        { }

        constexpr auto
        operator= (const base_real_type& v) noexcept
            -> dual&
        {
            m_re = v;
            m_d = base_real_type{};

            return *this;
        }

        constexpr auto
        re() noexcept 
            -> base_real_type&
        { return m_re; }

        constexpr auto
        re() const noexcept
            -> const base_real_type&
        { return m_re; }

        constexpr auto
        d() noexcept 
            -> base_real_type&
        { return m_d; }

        constexpr auto
        d() const noexcept
            -> const base_real_type&
        { return m_d; }

        constexpr auto
        norm() noexcept
            -> base_real_type
        { return ((base_real_type{} < m_re) - (base_real_type{} > m_re)) * m_re; }

        constexpr auto
        conj() noexcept
            -> dual<base_real_type>&
        { 
            m_d = -m_d;
            return *this; 
        }

        ///{@  dual number unary arithmetic
        constexpr auto
        operator+= (const base_real_type& v) noexcept
            -> dual&
        {
            m_re += v;
            return *this;
        }

        constexpr auto
        operator-= (const base_real_type& v) noexcept
            -> dual&
        {
            m_re -= v;
            return *this;
        }

        constexpr auto
        operator*= (const base_real_type& v) noexcept
            -> dual&
        {
            m_re *= v;
            m_d *= v;
            return *this;
        }

        constexpr auto
        operator/= (const base_real_type& v) noexcept
            -> dual&
        {
            m_re /= v;
            m_d /= v;
            return *this;
        }

        template<typename other_real_type>
        constexpr auto
        operator+= (const dual<other_real_type>& dn) noexcept
            -> dual<base_real_type>&
        {
            m_re += dn.re();
            m_d += dn.d();
            return *this;
        }

        template<typename other_real_type>
        constexpr auto
        operator-= (const dual<other_real_type>& dn) noexcept
            -> dual<base_real_type>&
        {
            m_re -= dn.re();
            m_d -= dn.d();
            return *this;
        }

        template<typename other_real_type>
        constexpr auto
        operator*= (const dual<other_real_type>& dn) noexcept
            -> dual<base_real_type>&
        {
            m_d = m_d*dn.re() + m_re*dn.d();
            m_re *= dn.re();
            return *this;
        }

        template<typename other_real_type>
        constexpr auto
        operator/= (const dual<other_real_type>& dn) noexcept
            -> dual<base_real_type>&
        {
            m_d = (m_d*dn.re() - m_re*dn.d())/(dn.re() * dn.re());
            m_re /= dn.re();
            return *this;
        }
        ///@}  dual number unary arithmetic

        ///{@  dual number arithmetic
        template<typename other_real_type>
        constexpr auto
        operator+ (const dual<other_real_type>& v)
            -> dual<base_real_type>
        {
            return dual{m_re + v.re(), m_d + v.d()};
        }

        template<typename other_real_type>
        constexpr auto
        operator- (const dual<other_real_type>& v)
            -> dual<base_real_type>
        {
            return dual{m_re - v.re(), m_d - v.d()};
        }

        template<typename other_real_type>
        constexpr auto
        operator* (const dual<other_real_type>& v)
            -> dual<base_real_type>
        {
            return dual{m_re * v.re(), m_d * v.re() + m_re * v.d()};
        }

        template<typename other_real_type>
        constexpr auto
        operator/ (const dual<other_real_type>& v)
            -> dual<base_real_type>
        {
            return dual{m_re / v.re(), (m_d * m_re - m_re * v.d()) / (v.re() * v.re())};
        }

        template<typename other_real_type>
        constexpr auto
        operator+ (const other_real_type& v)
            -> dual<base_real_type>
        {
            return dual{m_re + v, m_d};
        }

        template<typename other_real_type>
        constexpr auto
        operator- (const other_real_type& v)
            -> dual<base_real_type>
        {
            return dual{m_re - v, m_d};
        }

        template<typename other_real_type>
        constexpr auto
        operator* (const other_real_type& v)
            -> dual<base_real_type>
        {
            return dual{m_re * v, m_d * v};
        }

        template<typename other_real_type>
        constexpr auto
        operator/ (const other_real_type& v)
            -> dual<base_real_type>
        {
            return dual{m_re / v, m_d / v};
        }
        ///@}  dual number arithmetic

        // We interpret the == operator as the kronecker delta function
        // that is, f(x,y) = 1 iff x = y and 0 else.
        // The kronecker delta has partial derivatives 0 everywhere
        // except at x = y where it is undefined. Even if we define
        // the derivative at x = y using dirac delta functions in
        // the sense of distributions, the distributional derivative
        // evaluates to 0.
        // To see this set f(x,y) = H(x - y) + H(y - x) - 1
        // and take the distributional derivative.
        // H is the heaviside function with the convention H(0)=1
        // and H'(x) = delta(x) as a distributional derivative.
        
        ///{@   dual number comparison operators
        template<typename other_real_type>
        constexpr auto
        operator==(const other_real_type& v)
            -> const bool
        {
            return m_re == v;
        }

        template<typename other_real_type>
        constexpr auto
        operator!=(const other_real_type& v)
            -> const bool
        {
            return m_re != v;
        }
        
        template<typename other_real_type>
        constexpr auto
        operator<(const other_real_type& v)
            -> const bool
        {
            return m_re < v;
        }

        template<typename other_real_type>
        constexpr auto
        operator>(const other_real_type& v)
            -> const bool
        {
            return m_re > v;
        }

        template<typename other_real_type>
        constexpr auto
        operator<=(const other_real_type& v)
            -> const bool
        {
            return m_re <= v;
        }

        template<typename other_real_type>
        constexpr auto
        operator>=(const other_real_type& v)
            -> const bool
        {
            return m_re >= v;
        }

        template<typename other_real_type>
        constexpr auto
        operator==(const dual<other_real_type>& v)
            -> const bool
        {
            return m_re == v.re();
        }

        template<typename other_real_type>
        constexpr auto
        operator!=(const dual<other_real_type>& v)
            -> const bool
        {
            return m_re != v.re();
        }
        
        template<typename other_real_type>
        constexpr auto
        operator<(const dual<other_real_type>& v)
            -> const bool
        {
            return m_re < v.re();
        }

        template<typename other_real_type>
        constexpr auto
        operator>(const dual<other_real_type>& v)
            -> const bool
        {
            return m_re > v.re();
        }

        template<typename other_real_type>
        constexpr auto
        operator<=(const dual<other_real_type>& v)
            -> const bool
        {
            return m_re <= v.re();
        }

        template<typename other_real_type>
        constexpr auto
        operator>=(const dual<other_real_type>& v)
            -> const bool
        {
            return m_re >= v.re();
        }
        ///@}   dual number comparison operators
    
    private:

        base_real_type m_re;
        base_real_type m_d;
    };
    ///@{  scalar arithmetic
    
    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator+ (const base_real_type& u, const dual<other_real_type>& v)
        -> dual<other_real_type>
    {
        return dual{u + v.re(), v.d()};
    }
    
    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator- (const base_real_type& u, const dual<other_real_type>& v)
        -> dual<other_real_type>
    {
        return dual{u - v.re(), -v.d()};
    }
    
    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator* (const base_real_type& u, const dual<other_real_type>& v)
        -> dual<other_real_type>
    {
        return dual{u * v.re(), u * v.d()};
    }
    
    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator/ (const base_real_type& u, const dual<other_real_type>& v)
        -> dual<other_real_type>
    {
        return dual{u / v.re(), - u * v.d()/(v.re()*v.re())};
    }
    
    ///{@   elementary functions with at least one dual number
    
    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    pow(const dual<base_real_type>& u, const dual<other_real_type>& n) 
    {
        return dual{std::pow(u.re(), n.re()), n.re() * std::pow(u.re(), n.re()-1) * u.d() + std::log(u.re()) * std::pow(u.re(), n.re()) * n.d()}; 
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    pow(const dual<base_real_type>& u, const other_real_type& n) 
    { 
        return dual{std::pow(u.re(), n), n * std::pow(u.re(), n-1) * u.d()}; 
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    pow(const base_real_type& u, const dual<other_real_type>& n) 
    { 
        return dual{std::pow(u, n.re()), std::log(u) * std::pow(u, n.re()) * n.d()}; 
    }
    
    template<typename base_real_type>
    constexpr auto 
    sqrt(const dual<base_real_type>& dn) 
    { 
        return dual{std::sqrt(dn.re()), 0.5 * std::pow(dn.re(), -0.5) * dn.d()}; 
    }

    template<typename base_real_type>
    constexpr auto 
    cos(const dual<base_real_type>& dn) 
    { 
        return dual{std::cos(dn.re()), -std::sin(dn.re()) * dn.d()}; 
    }

    template<typename base_real_type>
    constexpr auto 
    sin(const dual<base_real_type>& dn) 
    { 
        return dual{std::sin(dn.re()), std::cos(dn.re()) * dn.d()}; 
    }

    template<typename base_real_type>
    constexpr auto 
    tan(const dual<base_real_type>& dn) 
    { 
        return dual{std::tan(dn.re()), dn.d()/(std::cos(dn.re())*std::cos(dn.re()))}; 
    }

    template<typename base_real_type>
    constexpr auto 
    exp(const dual<base_real_type>& dn) 
    { 
        return dual{std::exp(dn.re()), std::exp(dn.re()) * dn.d()}; 
    }

    template<typename base_real_type>
    constexpr auto 
    acos(const dual<base_real_type>& dn) 
    { 
        return dual{std::acos(dn.re()), -dn.d()/std::sqrt(1-dn.re()*dn.re()) }; 
    }

    template<typename base_real_type>
    constexpr auto 
    asin(const dual<base_real_type>& dn) 
    { 
        return dual{std::asin(dn.re()), dn.d()/std::sqrt(1-dn.re()*dn.re()) }; 
    }

    template<typename base_real_type>
    constexpr auto 
    atan(const dual<base_real_type>& dn) 
    { 
        return dual{std::atan(dn.re()), 1.0*dn.d()/(1+dn.re()*dn.re()) }; 
    }

    template<typename base_real_type>
    constexpr auto 
    log(const dual<base_real_type>& dn) 
    { 
        return dual{std::log(dn.re()), 1.0*dn.d()/dn.re()}; 
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    hypot(const dual<base_real_type>& u, const dual<other_real_type>& v) 
    { 
        return dual{std::hypot(u.re(), v.re()), (u.re() * u.d() + v.re() * v.d())/std::hypot(u.re(), v.re())}; 
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    hypot(const dual<base_real_type>& u, const other_real_type& v) 
    { 
        return dual{std::hypot(u.re(), v), (u.re() * u.d())/std::hypot(u.re(), v)}; 
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    hypot(const base_real_type& u, const dual<other_real_type>& v) 
    { 
        return dual{std::hypot(u, v.re()), (v.re() * v.d())/std::hypot(u, v.re())}; 
    }
    ///@}   elementary functions with at least one dual number

    ///{@   elementary functions on scalars
    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    pow(const base_real_type& u, const other_real_type& n) 
    {
        return std::pow(u, n); 
    }
    
    template<typename base_real_type>
    constexpr auto 
    sqrt(const base_real_type& u) 
    { 
        return std::sqrt(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    cos(const base_real_type& u) 
    { 
        return std::cos(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    sin(const base_real_type& u) 
    { 
        return std::sin(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    tan(const base_real_type& u) 
    { 
        return std::tan(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    exp(const base_real_type& u)
    { 
        return std::exp(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    acos(const base_real_type& u)
    { 
        return std::acos(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    asin(const base_real_type& u) 
    { 
        return std::asin(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    atan(const base_real_type& u) 
    { 
        return std::atan(u); 
    }

    template<typename base_real_type>
    constexpr auto 
    log(const base_real_type& u) 
    { 
        return std::log(u); 
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto 
    hypot(const base_real_type& u, const other_real_type& v) 
    { 
        return std::hypot(u,v); 
    }
    ///@}   elementary functions on scalars

    ///{@   elemenntary functions (general)
    template<typename ordered_type>
    constexpr auto
    sgn(const ordered_type& u)
        -> int
    {
        return (ordered_type{} < u) - (ordered_type{} > u.re());
    }

    template<typename ordered_type>
    constexpr auto
    abs(const ordered_type& u)
        -> ordered_type
    {
        return sgn(u) * u;
    }

    ///@}   elementary functions (general)

    ///{@   scalar comparison operators
    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator==(const base_real_type& u, const dual<other_real_type>& v)
        -> const bool
    {
        return u == v.re();
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator!=(const base_real_type& u, const dual<other_real_type>& v)
        -> const bool
    {
        return u != v.re();
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator<(const base_real_type& u, const dual<other_real_type>& v)
        -> const bool
    {
        return u < v.re();
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator>(const base_real_type& u, const dual<other_real_type>& v)
        -> const bool
    {
        return u > v.re();
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator<=(const base_real_type& u, const dual<other_real_type>& v)
        -> const bool
    {
        return u <= v.re();
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    operator>=(const base_real_type& u, const dual<other_real_type>& v)
        -> const bool
    {
        return u >= v.re();
    }
    ///@}   scalar comparison operators

    ///{@   literals
    constexpr dual<long double> operator ""_eps(const long double v)
    {
        return dual<long double>{0, v};
    }
    ///{@   literals

    ///{@   ostream
    template<typename base_real_type>
    constexpr auto
    operator<<(std::ostream& os, dual<base_real_type> v)
        -> std::ostream&
    {
        os << v.re() << " + " << v.d() << "_eps";
        return os;
    }
    ///{@   ostream

    ///{@   misc
    template<typename base_real_type, typename other_real_type>
    constexpr auto
    equiv(dual<base_real_type> u, dual<other_real_type> v)
        -> const bool
    {
        return ( (u.re() == v.re()) && (u.d() == v.d()));
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    equiv(base_real_type u, dual<other_real_type> v)
        -> const bool
    {
        return ( (u == v.re()) && (base_real_type{} == v.d()));
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    equiv(dual<base_real_type> u, other_real_type v)
        -> const bool
    {
        return ( (u.re() == v) && (u.d() == other_real_type{}));
    }

    template<typename base_real_type, typename other_real_type>
    constexpr auto
    equiv(base_real_type u, other_real_type v)
        -> const bool
    {
        return (u == v);
    }
    ///@}   misc
    
}  /// namespace dnn

#endif  /// DUAL_NUMBER
