load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fft_utils_macros",
    hdrs = ["fft_utils_macros.h"],
    deps = ["//math/complex:complex_macros"],
)

cc_library(
    name = "fft_utils",
    hdrs = ["fft_utils.h"],
    deps = [
        ":fft_utils_macros",
        "//math/bit:next_pow2_32",
        "//math/complex",
        "//math/constants:pi",
        "//math/mod:mod_int",
    ],
)

cc_library(
    name = "ntt_utils_fix_macros",
    hdrs = ["ntt_utils_fix_macros.h"],
    deps = ["//math/mod:mod_int_macros"],
)

cc_library(
    name = "ntt_utils_fix",
    hdrs = ["ntt_utils_fix.h"],
    deps = [
        ":ntt_utils_fix_macros",
        "//math/bit:next_pow2_32",
        "//math/mod:mod_int",
    ],
)

cc_library(
    name = "ntt_utils_macros",
    hdrs = ["ntt_utils_macros.h"],
)

cc_library(
    name = "ntt_utils",
    hdrs = ["ntt_utils.h"],
    deps = [
        ":ntt_utils_macros",
        "//debug",
        "//math/bit:next_pow2_32",
        "//math/mod:add",
        "//math/mod:exp",
        "//math/mod:inv",
        "//math/mod:mul",
        "//math/mod:sub",
    ],
)
