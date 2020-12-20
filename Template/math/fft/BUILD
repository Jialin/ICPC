load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fft_utils_macros",
    hdrs = ["fft_utils_macros.h"],
)

cc_library(
    name = "fft_utils",
    hdrs = ["fft_utils.h"],
    deps = [
        ":fft_utils_macros",
        "//math/bigint",
        "//math/bit:next_pow2_32",
    ],
)
