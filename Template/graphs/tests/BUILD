load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "topological_sorter_test",
    srcs = ["topological_sorter_test.cpp"],
    deps = [
        "//graphs:topological_sorter",
        "//graphs/forward_star",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
