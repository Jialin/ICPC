load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "kitamasa_and_xor_test",
    srcs = ["kitamasa_and_xor_test.cpp"],
    deps = [
        "//math/kitamasa:kitamasa_and_xor",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "kitamasa_once_test",
    srcs = ["kitamasa_once_test.cpp"],
    deps = [
        "//math/kitamasa:kitamasa_once",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "kitamasa_test",
    srcs = ["kitamasa_test.cpp"],
    deps = [
        "//math/kitamasa",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
