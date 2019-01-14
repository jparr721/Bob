#include <core/core.h>
#include <core/profile.h>
#include <core/util.h>
#include <naive/naive.h>

#include <memory>
#include <iostream>

int main(int argc, char** argv) {
  bob::Naive n;
  return n.simulation(argc, argv);
}
