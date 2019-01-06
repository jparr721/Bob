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
  std::vector<bob::Reading> outputs = n.naive_sim(p);
  std::for_each(outputs.begin(), outputs.end(), [&](const auto& reading) {
    std::cout << reading << std::endl;
  });
  return EXIT_SUCCESS;
}
