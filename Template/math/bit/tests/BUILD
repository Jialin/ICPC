load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "ctz_test",
    srcs = ["ctz_test.cpp"],
    deps = [
        "//math/bit:ctz",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "ctz128_test",
    srcs = ["ctz128_test.cpp"],
    deps = [
        "//math/bit:ctz128",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "gray_code_test",
    srcs = ["gray_code_test.cpp"],
    deps = [
        "//math/bit:gray_code",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "inv_gray_code_test",
    srcs = ["inv_gray_code_test.cpp"],
    deps = [
        "//math/bit:inv_gray_code",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
