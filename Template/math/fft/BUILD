load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fft_utils",
    hdrs = ["fft_utils.h"],
    deps = [
        "//math:bigint",
        "//math/bit:next_pow2_32",
    ],
)
