#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "lcs.h"

std::string random_string_dop(int size, const std::string& alphabet) {
    std::string result;
    auto random_char = [&]() { return alphabet[rand() % alphabet.size()]; };
    std::generate_n(std::back_inserter(result), size, random_char);
    return result;
}

std::string random_string(int size) {
    static const std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return random_string_dop(size, alphabet);
}

int main(int argc, char* argv[]) {
    int N = 10;
    int result = Catch::Session().run(argc, argv);
    std::string str1, str2;
    std::string points = random_string(N);

    auto t1 = std::chrono::high_resolution_clock::now();
    str1 = lcs(points, points);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time for upgraded algorythm " << N << " : " << time << " sec." << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    str2 = lcs_naiv(points, points);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration<double>(t4 - t3).count();
    std::cout << "Time for standart algorythm " << N << " : " << time1 << " sec." << std::endl;

    return result;
}