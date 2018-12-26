#include <core/core.h>
#include <core/profile.h>
#include <core/util.h>
#include <naive/naive.h>

#include <memory>
#include <iostream>

int main(int argc, char** argv) {
  bob::Naive n;
  bob::Core c;
  if (argc < 2) {
    n.usage(n.OPTS);
    return EXIT_SUCCESS;
  }

  std::unique_ptr<bob::Profile> p(new bob::Profile(std::string(argv[1])));
  n.naive_sim(p);
  return EXIT_SUCCESS;
}
