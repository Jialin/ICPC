load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "poly_int_macros",
    hdrs = ["poly_int_macros.h"],
    deps = ["//math/fft:fft_utils_macros"],
)

cc_library(
    name = "poly_int",
    hdrs = ["poly_int.h"],
    deps = [
        ":poly_int_macros",
        "//math/fft:fft_utils",
    ],
)
