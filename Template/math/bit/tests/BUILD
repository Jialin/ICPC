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

cc_test(
    name = "next_pow2_32_test",
    srcs = ["next_pow2_32_test.cpp"],
    deps = [
        "//math/bit:next_pow2_32",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "submasks_test",
    srcs = ["submasks_test.cpp"],
    deps = [
        "//math/bit:submasks",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
