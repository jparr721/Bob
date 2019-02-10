# Bob -- Deprecated, Research is now in [simglucose](https://github.com/jxx123/simglucose) inside of [Lazarus](https://github.com/jparr721/Lazarus)
Bob is a compartment simulation of a diabetes patient to provide continuous inputs to a deep reinforcement learning algorithm as apart of the Lazarus research project. Bob also allows for the modular generation of two-compartment data via the use of base functionality that can be extended to different circumstances. You can also simply define profiles and take the outputs for study if you'd prefer to do it that way.

## Why?
Medical data is hard to get, and you can't perform experiments on people without sufficient backing, research, and funding. As a result, I have created Bob here to suffer from diabetes and other extremely taxing health conditions to help simulate how it might look inside of a real person. The intention of this system is to develop my classifier and insulin injection pancreas replacement device.

## Some Abbreviations

Some abbreviations are used in the code and in the docs here, they are as follows:

`irr -> Insulin Release Rate`

`gly_idx(and other spellings) -> Glycemic Index`

## Working With Profiles

Profiles are handled via the profiles directory. In their current state they go along with the following syntax:

Line One:

`<time> <initial_meal_size(g of carbs)> <intial_glucose(mg/dl)> <irr> <gly_idx> <interval> <has_diabetes(0, 1)>`

This line lays out the standard operational syntax for supporting a particular profile. Modeling people in various stages of diabetes just requires tweaking the variables to fit that profile, you can also run the simulation with default levels for 'healthy' people. Those are: `0.0224 mg/dl irr` and `0.0453 mg/dl gly idx`.

Following that, on every subsequent line, we lay out the meals, right now the interval between meals is set by the line-one profile description in the `time` variable. Meals are laid out as the following:

```
For a time of 180 minutes
100 // 8 am 50  // 11 am 100 // 2 pm 10  // 5 pm
```

Where the time in between each is dictated by the time specified in line one. All times are considered in minutes.

### Example Patient Profile

```
$ cat profiles/bob
180 127.7 75 0.0224 0.0453 30
50 70 120 30 10
```

This represents a 180 minute time with 30 minute intervals. The interval serves as a simple way to extract values by this, and will be printed to the console based on this. Logging to files will also follow this interval. All times will be recorded in minutes.

## Visual Model

The visual model features a representation of a human body with multiple concurrent simulations running with different multipliers on the glucose levels. This allows for the accurate representation of how glucose functions when distributed across the human body and also represents the expected fluctuations from body region to body region.

IMPLEMENTATION PENDING

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
pacman -S cmake clang openmp cuda
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

Following this, we can find out executables for our model types and compile them

```
cd <BIN_DIR>
./model-name <PARAMS> // Params are laid out in the documentation for each model
```



#### Uninstalling

To uninstall, simply execute `$ rm -r <PROJECT_ROOT>` and this will remove the files.

## Road map
- [x] - Get basic proof of concept up and running
- [x] - Add support for modular bobs and other friends
- [x] - Read biomedical data from a file and form a profile
- [x] - Differentiate between having and not having diabetes
- [x] - Implement naive model for reactive insulin fluctuation
- [ ] - Implement neural model for predictive insulin fluctuation
- [ ] - Document all executables
- [ ] - Return coherent data for machine learning layer
- [ ] - Visual Implementation

## License
This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](https://github.com/jparr721/Bob/blob/master/LICENSE) file for details.
