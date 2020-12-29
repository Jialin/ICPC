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

cc_test(
    name = "ntt_utils_fix_prime_test",
    srcs = ["ntt_utils_fix_prime_test.cpp"],
    deps = [
        "//math/fft:ntt_utils_fix_prime",
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
