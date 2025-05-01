#include <random>

int rnd_int(int min_number, int max_number)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min_number, max_number);

    return distrib(gen);
}
