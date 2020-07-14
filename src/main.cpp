#include <iostream>
#include <boost/program_options.hpp>
#include "utils/Vector.h"
#include "engine/Scene.h"
#include "lights/PointLight.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    unsigned width, height;

    po::options_description desc("Options: ");
    desc.add_options()
            ("help", "Display this information")
            ("demo", "Run demo scene")
            ("save,s", po::value<std::string>()->implicit_value(""),
             "Disable real time mode and save rendered scene to a ppm (if no filename specified it uses a datetime format)")
            ("load,l", po::value<std::string>(), "Load yaml <file>")
            ("width,w", po::value<unsigned>(&width)->default_value(1920),
             "Width of the real time display and/or saved image")
            ("height,h", po::value<unsigned>(&height)->default_value(1080),
             "Height of the real time display and/or saved image");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error const& e) {
        std::cerr << "Option error: " << e.what() << std::endl;
        return 2;
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    Scene* scene;
    if (vm.count("load"))
        scene = new Scene(Scene::load(vm["load"].as<std::string>()));
    else if (vm.count("demo"))
        scene = new Scene(Scene::demo());
    else {
        std::cerr
                << "raytracer: fatal error: at least --demo or --load <file> options should be provided (or --help for more info)"
                << std::endl;
        return 3;
    }

    if (scene->dark()) {
        scene->emplace_light<PointLight>(Vector::left() * 100 + Vector::up() * 25);
    }

    if (vm.count("save")) {
        auto filename = vm["save"].as<std::string>();
        if (filename.empty())
            scene->render(width, height).save_now();
        else
            scene->render(width, height).save_ppm(vm["save"].as<std::string>());
    } else
        scene->render_rt(width, height);

    return 0;
}
