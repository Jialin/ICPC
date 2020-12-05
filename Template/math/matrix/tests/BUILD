load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "kitamasa_once_test",
    srcs = ["kitamasa_once_test.cpp"],
    deps = [
        "//math/matrix:kitamasa_once",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "kitamasa_test",
    srcs = ["kitamasa_test.cpp"],
    deps = [
        "//math/matrix:kitamasa",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "matrix_fix_inline_test",
    srcs = ["matrix_fix_inline_test.cpp"],
    deps = [
        "//math/matrix:matrix_fix_inline",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "matrix_mod_exp_utils_test",
    srcs = ["matrix_mod_exp_utils_test.cpp"],
    deps = [
        "//math/matrix:matrix_mod_exp_utils",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "matrix_mul_inline_test",
    srcs = ["matrix_mul_inline_test.cpp"],
    deps = [
        "//math/matrix:matrix_mul_inline",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
