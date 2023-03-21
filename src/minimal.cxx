#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

int main()
{
    plt::backend("tkagg");
    plt::plot({1,3,2,4});
    plt::show();
}