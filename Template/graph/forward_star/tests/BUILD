load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "forward_star_edge_weighted_test",
    srcs = ["forward_star_edge_weighted_test.cpp"],
    deps = [
        "//graph/forward_star:forward_star_edge_weighted",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "forward_star_test",
    srcs = ["forward_star_test.cpp"],
    deps = [
        "//graph/forward_star",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
