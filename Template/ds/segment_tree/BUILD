load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_compact_segment_tree_macros",
    hdrs = ["base_compact_segment_tree_macros.h"],
)

cc_library(
    name = "base_compact_segment_tree",
    hdrs = ["base_compact_segment_tree.h"],
)

cc_library(
    name = "base_lazy_compact_segment_tree_macros",
    hdrs = ["base_lazy_compact_segment_tree_macros.h"],
)

cc_library(
    name = "base_lazy_compact_segment_tree",
    hdrs = ["base_lazy_compact_segment_tree.h"],
)

cc_library(
    name = "lazy_compact_segment_tree_min",
    hdrs = ["lazy_compact_segment_tree_min.h"],
    deps = [
        ":base_lazy_compact_segment_tree",
        "//common:macros",
    ],
)
