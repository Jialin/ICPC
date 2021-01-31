load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fft_mul_mod_utils_test",
    srcs = ["fft_mul_mod_utils_test.cpp"],
    deps = [
        "//math/fft:fft_mul_mod_utils",
        "//math/poly:fft_poly_mod_int",
        "//math/poly:fft_poly_mod_int_macros",
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
    name = "fft_online_mod_utils_test",
    srcs = ["fft_online_mod_utils_test.cpp"],
    deps = [
        "//math/fft:fft_online_mod_utils",
        "//math/poly:fft_poly_mod_int",
        "//math/poly:fft_poly_mod_int_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "ntt_mul_utils_test",
    srcs = ["ntt_mul_utils_test.cpp"],
    deps = [
        "//math/fft:ntt_mul_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "ntt_online_utils_test",
    srcs = ["ntt_online_utils_test.cpp"],
    deps = [
        "//math/fft:ntt_online_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
