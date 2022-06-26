#include "doctest.h"
#include "function.h"

TEST_CASE ("Generation-cleaning-1") {
    std::vector<int> v = {0, 1, 0, 1, 1, 0, 2, 3, 3, 2};
    cleaning(v);
    std::vector<int> v_clean = {0, 1, 2, 3};
            REQUIRE(v == v_clean);
}

TEST_CASE ("Generation-cleaning-2") {
    std::vector<int> v = {0, 1, 1, 2, 2, 3};
    cleaning(v);
    std::vector<int> v_clean = {0, 1, 1, 2, 2, 3};
            REQUIRE(v == v_clean);
}

TEST_CASE ("Generation-cleaning-3") {
    std::vector<int> v = {0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};
    cleaning(v);
    std::vector<int> v_clean = {0, 1};
            REQUIRE(v == v_clean);
}

TEST_CASE ("Generation-comparison-1") {
    bool top = false;
    bool bot = false;
    bool right = false;
    bool left = false;
    bool forw = false;
    bool back = false;
    std::vector<int> c = {};
    compare(c, back, right, forw, left, bot, top);
    std::vector<int> c_comp = {};
            REQUIRE(c == c_comp);
}

TEST_CASE ("Generation-comparison-2") {
    bool top = true;
    bool bot = true;
    bool right = true;
    bool left = true;
    bool forw = true;
    bool back = true;
    std::vector<int> c = {};
    compare(c, back, right, forw, left, bot, top);
    std::vector<int> c_comp = {3, 0, 4, 4, 7, 3, 0, 1, 5, 5, 4, 0, 1, 2, 6, 6, 5, 1, 2, 3, 7, 7, 6, 2, 3, 0, 1, 1, 2, 3,
                               7, 4, 5, 5, 6, 7};
            REQUIRE(c == c_comp);
}

TEST_CASE ("Generation-comparison-3") {
    bool top = true;
    bool bot = false;
    bool right = true;
    bool left = false;
    bool forw = true;
    bool back = false;
    std::vector<int> c = {};
    compare(c, back, right, forw, left, bot, top);
    std::vector<int> c_comp = {0, 1, 5, 5, 4, 0, 1, 2, 6, 6, 5, 1, 7, 4, 5, 5, 6, 7};
            REQUIRE(c == c_comp);
}


