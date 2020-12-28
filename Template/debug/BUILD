load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "debug_basic",
    hdrs = ["debug_basic.h"],
)

cc_library(
    name = "debug_bigint",
    hdrs = ["debug_bigint.h"],
    deps = [
        ":debug_basic",
        "//math/bigint",
    ],
)

cc_library(
    name = "debug_complex",
    hdrs = ["debug_complex.h"],
    deps = [
        ":debug_basic",
        "//math/complex",
    ],
)

cc_library(
    name = "debug_matrix",
    hdrs = ["debug_matrix.h"],
    deps = [":debug_basic"],
)

cc_library(
    name = "debug_mod_int",
    hdrs = ["debug_mod_int.h"],
    deps = [
        ":debug_basic",
        "//math/mod:mod_int",
    ],
)

cc_library(
    name = "debug",
    hdrs = ["debug.h"],
    deps = [
        ":debug_basic",
        ":debug_bigint",
        ":debug_complex",
        ":debug_matrix",
        ":debug_mod_int",
        "@boost//:stacktrace",
    ],
)
