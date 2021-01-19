load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fft_mixed_utils_macros",
    hdrs = ["fft_mixed_utils_macros.h"],
    deps = ["//math/complex:complex_macros"],
)

cc_library(
    name = "fft_mixed_utils",
    hdrs = ["fft_mixed_utils.h"],
    deps = [
        ":fft_mixed_utils_macros",
        "//math/bit:next_pow2_32",
        "//math/complex",
        "//math/constants:pi",
        "//math/mod:mod_int",
    ],
)

cc_library(
    name = "fft_mul_mod_utils_macros",
    hdrs = ["fft_mul_mod_utils_macros.h"],
    deps = [
        ":fft_utils_macros",
        "//math/mod:mod_int_macros",
    ],
)

cc_library(
    name = "fft_mul_mod_utils",
    hdrs = ["fft_mul_mod_utils.h"],
    deps = [
        ":fft_mul_mod_utils_macros",
        ":fft_utils",
        "//math/bit:next_pow2_32",
        "//math/mod:mod_int",
    ],
)

cc_library(
    name = "fft_mul_utils_macros",
    hdrs = ["fft_mul_utils_macros.h"],
    deps = [":fft_utils_macros"],
)

cc_library(
    name = "fft_mul_utils",
    hdrs = ["fft_mul_utils.h"],
    deps = [
        ":fft_mul_utils_macros",
        ":fft_utils",
        "//math/bit:next_pow2_32",
        "//math/complex",
    ],
)

cc_library(
    name = "fft_online_mod_utils_macros",
    hdrs = ["fft_online_mod_utils_macros.h"],
)

cc_library(
    name = "fft_online_mod_utils",
    hdrs = ["fft_online_mod_utils.h"],
    deps = [
        ":fft_online_mod_utils_macros",
        "//common:macros",
    ],
)

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
        "//math/complex",
        "//math/constants:pi",
    ],
)

cc_library(
    name = "ntt_mul_utils_macros",
    hdrs = ["ntt_mul_utils_macros.h"],
    deps = [":ntt_utils_macros"],
)

cc_library(
    name = "ntt_mul_utils",
    hdrs = ["ntt_mul_utils.h"],
    deps = [
        ":ntt_mul_utils_macros",
        ":ntt_utils",
        "//common:macros",
        "//math/bit:next_pow2_32",
    ],
)

cc_library(
    name = "ntt_online_utils_macros",
    hdrs = ["ntt_online_utils_macros.h"],
    deps = [":ntt_mul_utils_macros"],
)

cc_library(
    name = "ntt_online_utils",
    hdrs = ["ntt_online_utils.h"],
    deps = [
        ":ntt_online_utils_macros",
        "//common:macros",
        "//math/fft:ntt_mul_utils",
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
    deps = ["//math/mod:mod_int_macros"],
)

cc_library(
    name = "ntt_utils",
    hdrs = ["ntt_utils.h"],
    deps = [
        ":ntt_utils_macros",
        "//math/mod:mod_int",
    ],
)
