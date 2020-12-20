load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fft_utils_test",
    srcs = ["fft_utils_test.cpp"],
    deps = [
        "//math/fft:fft_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
