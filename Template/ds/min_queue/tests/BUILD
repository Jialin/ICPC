load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "max_queue_test",
    srcs = ["max_queue_test.cpp"],
    deps = [
        "//ds/min_queue:base_min_queue_macros",
        "//ds/min_queue:max_queue",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
