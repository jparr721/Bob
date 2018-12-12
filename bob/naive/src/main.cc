#include <naive/naive.h>

#include <iostream>

int main(int argc, char** argv) {
  bob::Naive n;
  if (argc < 2) {
    n.usage(n.OPTS);
    return EXIT_SUCCESS;
  }

  std::string path(argv[1]);
  n.simulate(path);
  return EXIT_SUCCESS;
}
