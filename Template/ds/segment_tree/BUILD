load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_lazy_compact_segment_tree_macros",
    hdrs = ["base_lazy_compact_segment_tree_macros.h"],
)

cc_library(
    name = "base_lazy_compact_segment_tree",
    hdrs = ["base_lazy_compact_segment_tree.h"],
    deps = [
        "//math/bit:next_pow2_32",
    ],
)

cc_library(
    name = "base_segment_tree_macros",
    hdrs = ["base_segment_tree_macros.h"],
)

cc_library(
    name = "base_segment_tree",
    hdrs = ["base_segment_tree.h"],
)

cc_library(
    name = "base_lazy_segment_tree_macros",
    hdrs = ["base_lazy_segment_tree_macros.h"],
)

cc_library(
    name = "base_lazy_segment_tree",
    hdrs = ["base_lazy_segment_tree.h"],
)

cc_library(
    name = "lazy_compact_segment_tree_update_set_sum",
    hdrs = ["lazy_compact_segment_tree_update_set_sum.h"],
    deps = [
        ":base_lazy_compact_segment_tree",
        "//common:macros",
    ],
)

cc_library(
    name = "lazy_segment_tree_update_min",
    hdrs = ["lazy_segment_tree_update_min.h"],
    deps = [
        ":base_lazy_segment_tree",
        "//common:macros",
    ],
)

cc_library(
    name = "lazy_segment_tree_update_set_sum",
    hdrs = ["lazy_segment_tree_update_set_sum.h"],
    deps = [
        ":base_lazy_segment_tree",
        "//common:macros",
    ],
)
