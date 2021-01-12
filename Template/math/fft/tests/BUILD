load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fft_mixed_utils_test",
    srcs = ["fft_mixed_utils_test.cpp"],
    deps = [
        "//math/fft:fft_mixed_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fft_mul_utils_test",
    srcs = ["fft_mul_utils_test.cpp"],
    deps = [
        "//math/fft:fft_mul_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "ntt_utils_fix_test",
    srcs = ["ntt_utils_fix_test.cpp"],
    deps = [
        "//math/fft:ntt_utils_fix",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "ntt_utils_test",
    srcs = ["ntt_utils_test.cpp"],
    deps = [
        "//math/fft:ntt_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
