load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "z_function_test",
    srcs = ["z_function_test.cpp"],
    deps = [
        "//string/kmp:z_function",
        "//string/kmp:z_function_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
