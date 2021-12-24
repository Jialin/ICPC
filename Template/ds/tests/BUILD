load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "base_valued_interval_container_test",
    srcs = ["base_valued_interval_container_test.cpp"],
    deps = [
        "//ds:base_valued_interval_container",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "stair_container_test",
    srcs = ["stair_container_test.cpp"],
    deps = [
        "//ds:stair_container",
        "//ds:stair_container_macros",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
