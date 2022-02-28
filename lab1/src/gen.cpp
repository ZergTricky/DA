#include "iostream"
#include "random"
#include "chrono"

template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to) {
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
            <
                    std::is_integral<Numeric>::value, std::uniform_int_distribution<Numeric>, std::uniform_real_distribution<Numeric>
            >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N = 100;
    int LENGTH = 200;
    if (argc > 1) {
        N = std::stoi(argv[1]);
    }
    if (argc > 2) {
        LENGTH = std::stoi(argv[2]);
    }
    for (int i = 0; i < N; ++i) {
        double key = random<double>(-100.0, 100.0);
        std::string value;
        size_t string_size = random<size_t>(1, LENGTH);
        for (int j = 0; j < string_size; ++j) {
            value += random<char>('a', 'z');
        }
        std::cout << key << "\t" << value << "\n";
    }
}