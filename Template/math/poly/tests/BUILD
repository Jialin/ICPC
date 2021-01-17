load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "ntt_poly_mod_int_test",
    srcs = ["ntt_poly_mod_int_test.cpp"],
    deps = [
        "//math/poly:ntt_poly_mod_int",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "poly_int_test",
    srcs = ["poly_int_test.cpp"],
    deps = [
        "//math/poly:poly_int",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "poly_mod_int_test",
    srcs = ["poly_mod_int_test.cpp"],
    deps = [
        "//math/poly:poly_mod_int",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
