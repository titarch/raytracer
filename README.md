# raytracer

### Short description

This project is a quite simple (and not very optimized) raytracer.
I would say it is more useful to anyone wanting to develop a raytracer and trying to find inspiration or help
from other implementations (as I sure did from other projects (I had a very hard time with those nasty cylinders)).

But I would say it can give quite nice results and gained a rather nice interface. As a matter of fact, I used
it to render results from other projects (like [elplant](https://github.com/titarch/elplant)) and it turns out
to be very useful.

### Features

- Can load scenes from YAML files
- Handles multiples kind of object (Spheres, Planes, Cylinders, Triangles)
- Transparent (refractive) textures
- Other mostly experimental features (blobs of charged particles, ...)

### Requirements

* cmake
* SFML
* Boost (program_options)
* OpenMP
* yaml-cpp

### Build

```sh
# In project root

$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make

$ ./raytracer --help
Options: :
  --help                      Display this information
  --demo                      Run demo scene
  -s [ --save ] arg           Disable real time mode and save rendered scene to
                              a ppm (if no filename specified it uses a
                              datetime format)
  -l [ --load ] arg           Load yaml <file>
  -w [ --width ] arg (=1920)  Width of the real time display and/or saved image
  -h [ --height ] arg (=1080) Height of the real time display and/or saved
                              image
