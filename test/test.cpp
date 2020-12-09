#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/libs/Array.hpp"

TEST_CASE("construct with vector should work", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    std::vector out = array.to_vector();
    REQUIRE(out[0] == 1);
    REQUIRE(out[1] == 2);
    REQUIRE(out[2] == 3);
}

TEST_CASE("construct with length should work", "[Vector]")
{
    AddonTemplate::Array array(3);
    std::vector out = array.to_vector();
    REQUIRE(out.size() == 3);
}

TEST_CASE("fill should replace exist elements", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    std::vector out = array.fill(3).to_vector();
    REQUIRE(out[0] == 3);
    REQUIRE(out[1] == 3);
    REQUIRE(out[2] == 3);
}

TEST_CASE("fill can worker with length", "[Vector]")
{
    AddonTemplate::Array array(3.0);
    std::vector out = array.fill("1").to_vector();
    REQUIRE(strcmp(out[0], "1") == 0);
    REQUIRE(strcmp(out[1], "1") == 0);
    REQUIRE(strcmp(out[2], "1") == 0);
}

TEST_CASE("some should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    bool result = array.some([](int ele, int index) {
        return ele == 2;
    });
    bool result2 = array.some([](int ele, int index) {
        return ele == 4;
    });
    REQUIRE(result == true);
    REQUIRE(result2 == false);
}

TEST_CASE("filter should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    std::vector result = array.filter([](int ele, int index) {
                                  return ele == 2 || ele == 3;
                              })
                             .to_vector();
    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 3);
}

TEST_CASE("find should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    int result = array.find([](int ele, int index) {
        return ele == 2 || ele == 3;
    });
    REQUIRE(result == 2);
    int result2 = array.find([](int ele, int index) {
        return ele == 4;
    });
    REQUIRE(result2 == NULL);
}

TEST_CASE("includes should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    int result = array.includes(3);
    REQUIRE(result == true);
    int result2 = array.includes(4);
    REQUIRE(result2 == false);
}

TEST_CASE("findIndex should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    int result = array.findIndex([](int ele, int index) {
        return ele == 3;
    });
    REQUIRE(result == 2);
    int result2 = array.findIndex([](int ele, int index) {
        return ele == 4;
    });
    REQUIRE(result2 == -1);
}

TEST_CASE("indexOf should worker", "[Vector]")
{
    std::vector test = {1, 2, 2};
    AddonTemplate::Array array(test);
    int result = array.indexOf(2);
    REQUIRE(result == 1);
}

TEST_CASE("push should worker", "[Vector]")
{
    std::vector test = {1, 2, 2};
    AddonTemplate::Array array(test);
    int result = array.push(4);
    REQUIRE(result == 4);
    REQUIRE(array.to_vector()[3] == 4);
}

TEST_CASE("push multi params should worker", "[Vector]")
{
    std::vector test = {1, 2, 2};
    AddonTemplate::Array array(test);
    int result = array.push(4, 5);
    REQUIRE(result == 5);
    REQUIRE(array.to_vector()[3] == 4);
    REQUIRE(array.to_vector()[4] == 5);
}

TEST_CASE("pop should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    array.pop();
    REQUIRE(array.length() == 2);
    REQUIRE(array.to_vector()[0] == 1);
    REQUIRE(array.to_vector()[1] == 2);
}

TEST_CASE("shift should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    array.shift();
    REQUIRE(array.length() == 2);
    REQUIRE(array.to_vector()[0] == 2);
    REQUIRE(array.to_vector()[1] == 3);
}

TEST_CASE("unshift should worker", "[Vector]")
{
    std::vector test = {1, 2, 3};
    AddonTemplate::Array array(test);
    int result = array.unshift(0);
    REQUIRE(result == 4);
    REQUIRE(array.to_vector()[0] == 0);
    REQUIRE(array.to_vector()[1] == 1);
    REQUIRE(array.to_vector()[2] == 2);
    REQUIRE(array.to_vector()[3] == 3);
}

TEST_CASE("concat should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    std::vector t2 = {4, 5, 6};
    AddonTemplate::Array a1(t1);
    AddonTemplate::Array a2(t2);
    std::vector result = a1.concat(a2).to_vector();
    REQUIRE(result.size() == 6);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 2);
    REQUIRE(result[2] == 3);
    REQUIRE(result[3] == 4);
    REQUIRE(result[4] == 5);
    REQUIRE(result[5] == 6);
}

TEST_CASE("forEach should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    AddonTemplate::Array a1(t1);
    a1.forEach([](int element, int index) {
        REQUIRE(element == (index + 1));
    });
}

TEST_CASE("reduce should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    AddonTemplate::Array a1(t1);
    int result = a1.reduce([](int out, int value, int index) {
        out += value;
        return out;
    },
                           0);
    REQUIRE(result == 6);
}

TEST_CASE("map should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    AddonTemplate::Array a1(t1);
    std::vector result = a1.map([](int value, int index) {
                               return value + 1;
                           }).to_vector();
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 3);
    REQUIRE(result[2] == 4);
}

TEST_CASE("map to different type should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    AddonTemplate::Array a1(t1);
    std::vector result = a1.map([](int value, int index) {
                               return "1";
                           }).to_vector();
    REQUIRE(result.size() == 3);
    REQUIRE(strcmp(result[0], "1") == 0);
    REQUIRE(strcmp(result[1], "1") == 0);
    REQUIRE(strcmp(result[2], "1") == 0);
}

TEST_CASE("slice should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    AddonTemplate::Array a1(t1);
    std::vector result = a1.slice(0, 1).to_vector();
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 1);
    std::vector result2 = a1.slice(2, 1).to_vector();
    REQUIRE(result2.size() == 0);
    std::vector result3 = a1.slice(-2, 3).to_vector();
    REQUIRE(result3.size() == 2);
}

TEST_CASE("reverse should worker", "[Vector]")
{
    std::vector t1 = {1, 2, 3};
    AddonTemplate::Array a1(t1);
    std::vector result = a1.reverse().to_vector();
    REQUIRE(result[0] == 3);
    REQUIRE(result[1] == 2);
    REQUIRE(result[2] == 1);
}