#include <math.h>
#include <cstdlib>
#include <arrayfire.h>
#include <iostream>
#include <termcolor/termcolor.hpp>

using namespace af;
// generate millions of random samples
static long samples = 20e5;

/* Self-contained code to run host and device estimates of PI.  Note that
   each is generating its own random values, so the estimates of PI
   will differ. */
static double pi_device() {
    array x = randu(samples, f32), y = randu(samples, f32);
    return 4.0 * sum<float>(sqrt(x * x + y * y) < 1) / samples;
}

static double pi_host() {
    int count = 0;
    for (int i = 0; i < samples; ++i) {
        float x = float(rand()) / RAND_MAX;
        float y = float(rand()) / RAND_MAX;
        if (sqrt(x * x + y * y) < 1)
            count++;
    }
    return 4.0 * count / samples;
}

// void wrappers for timeit()
static void device_wrapper() { pi_device(); }

static void host_wrapper() { pi_host(); }

int main(int argc, char **argv) {
    try {
        int device = argc > 1 ? atoi(argv[1]) : 0;
        setDevice(device);
        info();
        const auto dtime = timeit(device_wrapper);
        const auto htime = timeit(host_wrapper);
        std::cout << termcolor::green << "device: " << dtime << " pi = " << pi_device() <<std::endl;
        std::cout << termcolor::blue << "host: " << htime << " pi = " << pi_host() <<std::endl;
        std::cout << termcolor::red << "difference: " << htime / dtime << std::endl;

        const array a = array(seq(1,9), 3, 3);
        std::cout << a.dims() << std::endl;
    } catch (exception &e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }
    return 0;
}