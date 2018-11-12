# Bob
Bob is a compartment simulation of a diabetes patient to provide continuous inputs to a deep reinforcement learning algorithm as apart of the Lazarus research project.

## Why?
Medical data is hard to get, and you can't perform experiments on people without sufficient backing, research, and funding. As a result, I have created Bob here to suffer from diabetes and other extremely taxing health conditions to help simulate how it might look inside of a real person. The intention of this system is to develop my classifier and insulin injection pancreas replacement device.

## Getting Started With Bob
These instructions will get bob on your machine and set you up to run some basic simulations.

### Prerequisites
Currently, this has been tested only on Linux 4.18.5+ and Ubuntu 16.04 LTS.
- CMake >= 3.9
- C++ Compiler (clang was used here)
- STDC++17
- OpenMp 7+
- Cuda 9+
Supplied versions are what this system was tested on, and it may work on lower versions, but is not guaranteed.

#### Arch Linux
```
pacman -S cmake clang
```
#### Installing
This project can be cloned anywhere on your system.

CMake supports out of source builds, so we can make a build directory (referred herein as `BUILD_DIR`) you may also see a warning if you do an in source build because it's gross to do that.
```
cd <PROJECT_ROOT>
mkdir <BUILD_DIR>
```
After the place to build our system has been created we can now use CMake to generate our build structure.
```
cd <BUILD_DIR>
cmake ..
```
Once all the build files have been prepared, we can compile.
```
make
```

#### Uninstalling
To uninstall, simply execute `$ rm -r <PROJECT_ROT>` and this will remove the files.

## Roadmap
[x] - Get basic proof of concept up and running
[ ] - Add support for modular bob's and other friends
[ ] - Read biomedical data from a file and form a profile
[ ] - Differentiate between having and not having diabetes
[ ] - Return coherent data for machine learning layer

## License
This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](https://github.com/jparr721/Bob/blob/master/LICENSE) file for details.
