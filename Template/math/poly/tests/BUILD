load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "fft_poly_mod_int_test",
    srcs = ["fft_poly_mod_int_test.cpp"],
    deps = [
        "//math/poly:fft_poly_mod_int",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "ntt_poly_mod_int_test",
    srcs = ["ntt_poly_mod_int_test.cpp"],
    deps = [
        "//math/poly:ntt_poly_mod_int",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
