# include <dual_numbers.hxx>

using namespace dnn;

auto main() -> int
{
    // unit test
    {   // default constructor
        std::cout << "--default constructor--" << std::endl;
        std::cout << dual<int>{} << std::endl;
        std::cout << dual<double>{} << std::endl;
        std::cout << "--default constructor--" << std::endl;
    }   // default constructor
    
    {   // singe variable constructor
        std::cout << "--single variable constructor--" << std::endl;
        std::cout << dual<int>{1} << std::endl;
        std::cout << dual<double>{1} << std::endl;
        std::cout << "--single variable constructor--" << std::endl;
    }   // singe variable constructor

    {   // dual number specific functions
        std::cout << "--dual number specific functions--" << std::endl;
        auto x = dual<double>{-1,1};
        std::cout << "auto x = dual<double>{-1,1}: " << std::endl;
        std::cout << "re(x): " << (dnn::equiv(x.re(), -1) ? "passed" : "failed") << std::endl;
        std::cout << "d(x): " << (dnn::equiv(dual<double>{-1, 1}.d(), 1) ? "passed" : "failed") << std::endl;
        std::cout << "norm(x)): " << (dnn::equiv(dual<double>{-1, 1}.norm(), 1) ? "passed" : "failed") << std::endl;
        std::cout << "conj(x): " << (dnn::equiv(dual<double>{-1, 1}.conj(), dual<double>{-1, -1}) ? "passed" : "failed") << std::endl;
        std::cout << "--dual number specific functions--" << std::endl;
    }   // dual number specific functions
    
    {   // unary arithmetic
        std::cout << "--unary arithmetic--" << std::endl;
        {
            auto x = dual<int>{1, 1};
            std::cout << "auto x = dual<int>{1,1}" << std::endl;
            std::cout << "(x += 2): " << (dnn::equiv((x += 2), dual<int>{3, 1}) ? "passed" : "failed") << std::endl;
            std::cout << "(x -= 2): " << (dnn::equiv((x -= 2), dual<int>{1, 1}) ? "passed" : "failed") << std::endl;
            std::cout << "(x /= 2): " << (dnn::equiv((x /= 2), dual<int>{0, 0}) ? "passed" : "failed") << std::endl;
            std::cout << "(x *= 2): " << (dnn::equiv((x *= 2), dual<int>{0, 0}) ? "passed" : "failed") << std::endl;
        }

        {
            auto x = dual<double>{1, 1};
            std::cout << "auto x = dual<double>{1,1}" << std::endl;
            std::cout << "(x += 2): " << (dnn::equiv((x += 2), dual<double>{3, 1}) ? "passed" : "failed") << std::endl;
            std::cout << "(x -= 2): " << (dnn::equiv((x -= 2), dual<double>{1, 1}) ? "passed" : "failed") << std::endl;
            std::cout << "(x /= 2): " << (dnn::equiv((x /= 2), dual<double>{0.5, 0.5}) ? "passed" : "failed") << std::endl;
            std::cout << "(x *= 2): " << (dnn::equiv((x *= 2), dual<double>{1, 1}) ? "passed" : "failed") << std::endl;
        }

        {
            auto x = dual<int>{1, 2};
            auto y = dual<int>{3, 4};
            std::cout << "auto x = dual<int>{1,2}" << std::endl;
            std::cout << "auto y = dual<int>{3,4}" << std::endl;
            std::cout << "(x += y): " << (dnn::equiv((x += y), dual<int>{4, 6}) ? "passed" : "failed") << std::endl;
            std::cout << "(x -= y): " << (dnn::equiv((x -= y), dual<int>{1, 2}) ? "passed" : "failed") << std::endl;
            std::cout << "(x /= y): " << (dnn::equiv((x /= y), dual<int>{0, 0}) ? "passed" : "failed") << std::endl;
            std::cout << "(x *= y): " << (dnn::equiv((x *= y), dual<int>{0, 0}) ? "passed" : "failed") << std::endl;
        }

        {
            auto x = dual<double>{1, 2};
            auto y = dual<double>{3, 4};
            std::cout << "auto x = dual<double>{1,2}" << std::endl;
            std::cout << "auto y = dual<double>{3,4}" << std::endl;
            std::cout << "(x += y): " << (dnn::equiv((x += y), dual<double>{4, 6}) ? "passed" : "failed") << std::endl;
            std::cout << "(x -= y): " << (dnn::equiv((x -= y), dual<double>{1, 2}) ? "passed" : "failed") << std::endl;
            std::cout << "(x /= y): " << (dnn::equiv((x /= y), dual<double>{1.0/3, 2.0/9}) ? "passed" : "failed") << std::endl;
            std::cout << "(x *= y): " << (dnn::equiv((x *= y), dual<double>{1, 2}) ? "passed" : "failed") << std::endl;
        }
        {
            auto x = dual<double>{1, 2};
            auto y = dual<int>{3, 4};
            std::cout << "auto x = dual<double>{1,2}" << std::endl;
            std::cout << "auto y = dual<int>{3,4}" << std::endl;
            std::cout << "(x += y): " << (dnn::equiv((x += y), dual<double>{4, 6}) ? "passed" : "failed") << std::endl;
            std::cout << "(x -= y): " << (dnn::equiv((x -= y), dual<double>{1, 2}) ? "passed" : "failed") << std::endl;
            std::cout << "(x /= y): " << (dnn::equiv((x /= y), dual<double>{1.0/3, 2.0/9}) ? "passed" : "failed") << std::endl;
            std::cout << "(x *= y): " << (dnn::equiv((x *= y), dual<double>{1, 2}) ? "passed" : "failed") << std::endl;
        }
        {
            auto x = dual<int>{1, 2};
            auto y = dual<double>{3.0, 4.0};
            std::cout << "auto x = dual<int>{1,2}" << std::endl;
            std::cout << "auto y = dual<double>{3,4}" << std::endl;
            std::cout << "(x += y): " << (dnn::equiv((x += y), dual<int>{4, 6}) ? "passed" : "failed") << std::endl;
            std::cout << "(x -= y): " << (dnn::equiv((x -= y), dual<int>{1, 2}) ? "passed" : "failed") << std::endl;
            // --unexpected behaviour--
            std::cout << "(x /= y): " << (dnn::equiv((x /= y), dual<int>{0, 0}) ? "passed" : "failed") << std::endl;
            //
            // /= yields an integer type in this case
            // This mirrors the default cpp behaviour
            // for example:
            //
            // int z = 1;
            // std::cout << (z /= 3.0) << std::endl
            //
            // the above yields the result as integer division
            // one would instead expect the result to be floating point division.
            // --unexpected behaviour--
            std::cout << "(x *= y): " << (dnn::equiv((x *= y), dual<int>{0, 0}) ? "passed" : "failed") << std::endl;
        }

        std::cout << "--unary arithmetic--" << std::endl;
    }   // unary arithmetic

    {   // elementary functions
        std::cout << "--elementary functions--" << std::endl;
        auto x = dual<int>{2, 2};
        auto y = dual<double>{0.5, 2};
        std::cout << "pow: " << (dnn::equiv( dnn::pow(x, 0.5), dual<double>{dnn::pow(x.re(), 0.5), 0.5 * dnn::pow(x.re(), -0.5) * x.d()} ) ? "passed" : "failed") << std::endl; 
        std::cout << "pow: " << (dnn::equiv( dnn::pow(0.5, x), dual<double>{dnn::pow(0.5, x.re()), dnn::log(0.5) * dnn::pow(0.5, x.re()) * x.d()} ) ? "passed" : "failed") << std::endl;
        std::cout << "pow: " << (dnn::equiv( dnn::pow(x, y), dual<double>{dnn::pow(x.re(), y.re()), y.re() * dnn::pow(x.re(), y.re()-1) * x.d() + std::log(x.re()) * std::pow(x.re(), y.re()) * y.d()}) ? "passed" : "failed") << std::endl;
        std::cout << "sqrt: " << (dnn::equiv( dnn::sqrt(x), dual<double>{dnn::sqrt(x.re()), 0.5 * dnn::pow(x.re(), -0.5) * x.d()} ) ? "passed" : "failed") << std::endl;
        std::cout << "cos: " << (dnn::equiv( dnn::cos(x), dual<double>{dnn::cos(x.re()), -dnn::sin(x.re()) * x.d()} ) ? "passed" : "failed") << std::endl;
        std::cout << "sin: " << (dnn::equiv( dnn::sin(x), dual<double>{dnn::sin(x.re()), dnn::cos(x.re()) * x.d()} ) ? "passed" : "failed") << std::endl;
        // be careful of the arc-trig function domains, they are quite small
        std::cout << "acos: " << (dnn::equiv( dnn::acos(y), dual<double>{dnn::acos(y.re()), -y.d()/dnn::sqrt(1-y.re()*y.re())} ) ? "passed" : "failed") << std::endl;
        std::cout << "asin: " << (dnn::equiv( dnn::asin(y), dual<double>{dnn::asin(y.re()), y.d()/dnn::sqrt(1-y.re()*y.re())} ) ? "passed" : "failed") << std::endl;
        std::cout << "atan: " << (dnn::equiv( dnn::atan(y), dual<double>{dnn::atan(y.re()), y.d()/(1+y.re()*y.re())} ) ? "passed" : "failed") << std::endl;
        std::cout << "--elementary functions--" << std::endl;
    }   // elementary functions

    {   // elementary functions (general)
        std::cout << "--elementary functions (general)--" << std::endl;
        auto x = dual<int>{-2, 2};
        auto y = dual<double>{2, 0.5};
        auto z = dual<int>{0,1};
        std::cout << "sgn: " << (dnn::equiv( dnn::sgn(x), -1) ? "passed" : "failed") << std::endl; 
        std::cout << "sgn: " << (dnn::equiv( dnn::sgn(y), 1) ? "passed" : "failed") << std::endl;
        std::cout << "sgn: " << (dnn::equiv( dnn::sgn(z), 0) ? "passed" : "failed") << std::endl;
        std::cout << "abs: " << (dnn::equiv( dnn::abs(x), dual<double>{2, -2}) ? "passed" : "failed") << std::endl; 
        std::cout << "abs: " << (dnn::equiv( dnn::abs(y), dual<double>{2, 0.5}) ? "passed" : "failed") << std::endl;
        std::cout << "abs: " << (dnn::equiv( dnn::abs(z), 0) ? "passed" : "failed") << std::endl;
        std::cout << "--elementary functions (general)--" << std::endl;
    }   // elementary functions (general)


}