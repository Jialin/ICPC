load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "treap_set_test",
    srcs = ["treap_set_test.cpp"],
    deps = [
        "//ds/treap:base_treap_macros",
        "//ds/treap:treap_set",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "treap_sum_test",
    srcs = ["treap_sum_test.cpp"],
    deps = [
        "//ds/treap:base_treap_macros",
        "//ds/treap:treap_sum",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
