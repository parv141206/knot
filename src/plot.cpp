#include <iostream>
#include <matplot/matplot.h>
#include <map>
#include <vector>

using namespace matplot;

void plot_values(const std::map<double, double>& values , std::string title_) {
    std::vector<double> xs;
    std::vector<double> ys;

    for (const auto& [x, y] : values) {
        xs.push_back(x);
        ys.push_back(y);
    }

    // Create the plot
    plot(xs, ys)->line_width(2);

    xlabel("x");
    ylabel("y");
    title(title_);
    grid(on);

    show();
}
