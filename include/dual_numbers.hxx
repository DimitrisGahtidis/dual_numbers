#ifndef DUAL_NUMBER
#   define DUAL_NUMBER

#include <cmath>

namespace dnn
{
    

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
    };

}  /// namespace dnn

#endif  /// DUAL_NUMBER
