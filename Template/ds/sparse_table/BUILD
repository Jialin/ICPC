load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_sparse_table_2d_array",
    hdrs = ["base_sparse_table_2d_array.h"],
    deps = [
        "//common:macros",
        "//debug:debug_basic",
    ],
)

cc_library(
    name = "base_sparse_table_2d",
    hdrs = ["base_sparse_table_2d.h"],
    deps = [
        "//common:macros",
        "//debug:debug_basic",
    ],
)

cc_library(
    name = "base_sparse_table_macros",
    hdrs = ["base_sparse_table_macros.h"],
)

cc_library(
    name = "base_sparse_table",
    hdrs = ["base_sparse_table.h"],
    deps = [
        ":base_sparse_table_macros",
        "//common:macros",
        "//debug:debug_basic",
    ],
)

cc_library(
    name = "max_sparse_table_2d_array",
    hdrs = ["max_sparse_table_2d_array.h"],
    deps = [":base_sparse_table_2d_array"],
)

cc_library(
    name = "max_sparse_table_2d",
    hdrs = ["max_sparse_table_2d.h"],
    deps = [":base_sparse_table_2d"],
)

cc_library(
    name = "max_sparse_table",
    hdrs = ["max_sparse_table.h"],
    deps = [":base_sparse_table"],
)

cc_library(
    name = "min_sparse_table",
    hdrs = ["min_sparse_table.h"],
    deps = [":base_sparse_table"],
)
