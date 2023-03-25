#include <dual_numbers.hxx>

#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;
using namespace dnn;

auto main() -> int
{
    // Here I parametrize a spiral, the code is simple as it's just a circle with increasing radius over time
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
        plt::save("./imgs/spiral.png");
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
            dual<double> t = dual<double>{1.0*i/n,1};
            dual<double> point[2] = {dnn::cos(t*(2*M_PI))*t, dnn::sin(t*(2*M_PI))*t};
            if (i%(n/samples) == 0)
            {
                // want to scale the differentials to be unit vectors?
                double magnitude = 1; // std::hypot(point[0].d(), point[1].d());
                x.at(i/(n/samples)) = point[0].re();
                y.at(i/(n/samples)) = point[1].re();
                // grab the differentials of the parametrisation
                dx.at(i/(n/samples)) = point[0].d()/magnitude;
                dy.at(i/(n/samples)) = point[1].d()/magnitude;
            }
            u.at(i) = point[0].re();
            v.at(i) = point[1].re();

        }

        plt::plot(u, v, {{"color", "#1f77b4"}});
        plt::scatter(x, y, 20, {{"color", "#1f77b4"}});
        plt::quiver(x, y, dx, dy);
        // plt::show();
        plt::save("./imgs/dual_number_spiral.png");
    }

    return 0;
}