#include "doctest.h"
#include "function.h"

TEST_CASE("Generation-cleaning-1") {
    std::vector<int> v = {0, 1, 0, 1, 1, 0, 2, 3, 3, 2};
    cleaning(v);
    std::vector<int> v_clean = {0, 1, 2, 3};
    REQUIRE(v == v_clean);
}
TEST_CASE("Generation-cleaning-2") {
    std::vector<int> v = {0, 1, 1, 2, 2, 3};
    cleaning(v);
    std::vector<int> v_clean = {0, 1, 1, 2, 2, 3};
    REQUIRE(v == v_clean);
}
TEST_CASE("Generation-cleaning-3") {
    std::vector<int> v = {0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};
    cleaning(v);
    std::vector<int> v_clean = {0, 1};
    REQUIRE(v == v_clean);
}


