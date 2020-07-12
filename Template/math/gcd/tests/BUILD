load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "ext_gcd_test",
    srcs = ["ext_gcd_test.cpp"],
    deps = [
        "//math/gcd:ext_gcd",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "gcd32_test",
    srcs = ["gcd32_test.cpp"],
    deps = [
        "//math/gcd:gcd32",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "gcd64_test",
    srcs = ["gcd64_test.cpp"],
    deps = [
        "//math/gcd:gcd64",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "gcd128_test",
    srcs = ["gcd128_test.cpp"],
    deps = [
        "//math/gcd:gcd128",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
