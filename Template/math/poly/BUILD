load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "poly_int_macros",
    hdrs = ["poly_int_macros.h"],
    deps = ["//math/fft:fft_mixed_utils_macros"],
)

cc_library(
    name = "poly_int",
    hdrs = ["poly_int.h"],
    deps = [
        ":poly_int_macros",
        "//math/fft:fft_mixed_utils",
    ],
)

cc_library(
    name = "poly_mod_int_macros",
    hdrs = ["poly_mod_int_macros.h"],
    deps = ["//math/fft:ntt_utils_fix_macros"],
)

cc_library(
    name = "poly_mod_int",
    hdrs = ["poly_mod_int.h"],
    deps = [
        ":poly_mod_int_macros",
        "//math/fft:fft_mixed_utils",
        "//math/fft:ntt_utils_fix",
    ],
)
