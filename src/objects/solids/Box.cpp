//
// Created by bparsy on 7/14/20.
//

#include "Box.h"

double Box::intersects(Line const& line) const {
    auto tmin = (bound_min_ - line.o) / line.d;
    auto tmax = (bound_max_ - line.o) / line.d;

    for (auto i = 0u; i < 3u; ++i)
        if (tmin[i] > tmax[i])
            std::swap(tmin[i], tmax[i]);

    if (tmin.x() > tmax.y() || tmin.y() > tmax.x()) return Inf;
    if (tmin.y() < tmin.x()) tmin[0] = tmin.y();
    if (tmax.y() < tmax.x()) tmax[0] = tmax.y();

    


}

Line Box::get_normal(Point const& p) const {
    return Line(Vector(), Vector());
}

TexPixel Box::get_tex(Point const& p) const {
    return TexPixel(Color(), 0, 0, 0);
}
