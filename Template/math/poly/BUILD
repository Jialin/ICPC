load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fft_poly_mod_int_macros",
    hdrs = ["fft_poly_mod_int_macros.h"],
    deps = [
        "//math/fft:fft_mul_mod_utils_macros",
        "//math/fft:fft_online_mod_utils_macros",
    ],
)

cc_library(
    name = "fft_poly_mod_int",
    hdrs = ["fft_poly_mod_int.h"],
    deps = [
        ":fft_poly_mod_int_macros",
        ":poly",
        "//math/fft:fft_mul_mod_utils",
        "//math/fft:fft_online_mod_utils",
    ],
)

cc_library(
    name = "ntt_poly_mod_int_macros",
    hdrs = ["ntt_poly_mod_int_macros.h"],
    deps = [
        "//math/fft:ntt_mul_utils_macros",
        "//math/fft:ntt_online_utils_macros",
    ],
)

cc_library(
    name = "ntt_poly_mod_int",
    hdrs = ["ntt_poly_mod_int.h"],
    deps = [
        ":ntt_poly_mod_int_macros",
        "//math/fft:ntt_mul_utils",
        "//math/fft:ntt_online_utils",
    ],
)

cc_library(
    name = "poly_macros",
    hdrs = ["poly_macros.h"],
)

cc_library(
    name = "poly",
    hdrs = ["poly.h"],
    deps = [
        ":poly_macros",
        "//common:macros",
    ],
)
