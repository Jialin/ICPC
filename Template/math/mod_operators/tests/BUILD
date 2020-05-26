load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "exp_test",
    srcs = ["exp_test.cpp"],
    deps = [
        "//math/mod_operators:exp",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "fix_inline_test",
    srcs = ["fix_inline_test.cpp"],
    deps = [
        "//math/mod_operators:fix_inline",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "mul_test",
    srcs = ["mul_test.cpp"],
    deps = [
        "//math/mod_operators:mul",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "slight_fix_inline_test",
    srcs = ["slight_fix_inline_test.cpp"],
    deps = [
        "//math/mod_operators:slight_fix_inline",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
