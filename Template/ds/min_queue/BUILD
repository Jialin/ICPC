load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "base_min_queue_macros",
    hdrs = ["base_min_queue_macros.h"],
)

cc_library(
    name = "base_min_queue",
    hdrs = ["base_min_queue.h"],
    deps = ["//debug:debug_basic"],
)

cc_library(
    name = "max_queue",
    hdrs = ["max_queue.h"],
    deps = [":base_min_queue"],
)
