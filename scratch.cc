#include <thread>
#include <iostream>
#include <atomic>

int main(int argc, char** argv) {
    std::atomic<double> doublerino{0.0};
    std::atomic<bool> running{true};

    // Polls stdin for doubles until running is false and assigns doublerino to what was read.
    std::thread stdin_poll([&doublerino, &running] {
     while (running.load()) {
       double new_value;
       std::cin >> new_value;
       doublerino = new_value;
     }
    });

    for (std::size_t i = 0; i < 100; ++i) {
      // Do stuff with value. Output is the latest loaded value from stdin.
      std::cout << "Current value: " << doublerino.load() << std::endl;
    }

    running = false;
    stdin_poll.join();
    return 0;
}
