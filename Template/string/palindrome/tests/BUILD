load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "manacher_test",
    srcs = ["manacher_test.cpp"],
    deps = [
        "//string/palindrome:manacher",
        "//string/palindrome:manacher_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
