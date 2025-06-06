#include <matplot/matplot.h>
#include <map>
#include <vector>

using namespace matplot;

void plot_values(const std::vector<std::pair<std::map<double, double>, std::string>>& plots) {
    auto fig = figure(true);
    auto ax = gca();
    ax->hold(on); 

    std::vector<std::string> labels;

    for (const auto& [values, label] : plots) {
        std::vector<double> xs, ys;
        for (const auto& [x, y] : values) {
            xs.push_back(x);
            ys.push_back(y);
        }

        auto p = plot(ax, xs, ys);
        p->line_width(2);
        labels.push_back(label); 
    }

    xlabel("x");
    ylabel("y");
    title("Knot Layered Plot");

    matplot::legend(labels); 
    grid(ax, on);
    show();
}
