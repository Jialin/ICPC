load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "chinese_remainder_test",
    srcs = ["chinese_remainder_test.cpp"],
    deps = [
        "//math:chinese_remainder",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "linear_diophantine_test",
    srcs = ["linear_diophantine_test.cpp"],
    deps = [
        "//math:linear_diophantine",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "montgomery_mul_test",
    srcs = ["montgomery_mul_test.cpp"],
    deps = [
        "//math:montgomery_mul",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "uint256_test",
    srcs = ["uint256_test.cpp"],
    deps = [
        "//math:uint256",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
