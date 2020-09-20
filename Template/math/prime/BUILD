load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "divisor_use_tagger",
    hdrs = ["divisor_use_tagger.h"],
    deps = [
        ":min_prime_tagger",
    ],
)

cc_library(
    name = "divisor32",
    hdrs = ["divisor32.h"],
    deps = [
        "//debug",
    ],
)

cc_library(
    name = "divisor64",
    hdrs = ["divisor64.h"],
    deps = [
        ":miller_rabin64",
        ":rho64",
    ],
)

cc_library(
    name = "factorize",
    hdrs = ["factorize.h"],
    deps = [
        ":min_prime_tagger",
    ],
)

cc_library(
    name = "factorize_use_primes",
    hdrs = ["factorize_use_primes.h"],
    deps = [
        "//debug",
        "//math/bit:ctz",
    ],
)

cc_library(
    name = "factorize32",
    hdrs = ["factorize32.h"],
    deps = [
        ":miller_rabin32",
        ":rho32",
    ],
)

cc_library(
    name = "factorize64",
    hdrs = ["factorize64.h"],
    deps = [
        ":miller_rabin64",
        ":rho64",
    ],
)

cc_library(
    name = "factorize128",
    hdrs = ["factorize128.h"],
    deps = [
        ":miller_rabin128",
        ":rho128",
    ],
)

cc_library(
    name = "miller_rabin32",
    hdrs = ["miller_rabin32.h"],
    deps = [
        "//math/mod:exp_safe",
        "//math/mod:mul_inline_safe",
    ],
)

cc_library(
    name = "miller_rabin64",
    hdrs = ["miller_rabin64.h"],
    deps = [
        "//math/mod:exp",
        "//math/mod:fix",
    ],
)

cc_library(
    name = "miller_rabin128",
    hdrs = ["miller_rabin128.h"],
    deps = [
        "//math:ctz128",
        "//math:montgomery_mul",
        "//math/mod:exp128",
    ],
)

cc_library(
    name = "min_prime_tagger",
    hdrs = ["min_prime_tagger.h"],
)

cc_library(
    name = "phi_all",
    hdrs = ["phi_all.h"],
)

cc_library(
    name = "phi_inv32",
    hdrs = ["phi_inv32.h"],
    deps = [
        ":divisor32",
        ":miller_rabin32",
    ],
)

cc_library(
    name = "phi_inv64",
    hdrs = ["phi_inv64.h"],
    deps = [
        ":divisor64",
    ],
)

cc_library(
    name = "phi_use_primes",
    hdrs = ["phi_use_primes.h"],
    deps = [
        "//debug",
    ],
)

cc_library(
    name = "prime_checker",
    hdrs = ["prime_checker.h"],
)

cc_library(
    name = "prime_generator",
    hdrs = ["prime_generator.h"],
    deps = [
        ":prime_iterator",
    ],
)

cc_library(
    name = "prime_iterator",
    hdrs = ["prime_iterator.h"],
)

cc_library(
    name = "rho32",
    hdrs = ["rho32.h"],
    deps = [
        "//math/gcd:gcd32",
        "//math/mod:add",
        "//math/mod:mul_inline_safe",
    ],
)

cc_library(
    name = "rho64",
    hdrs = ["rho64.h"],
    deps = [
        "//math/gcd:gcd64",
        "//math/mod:fix",
        "//math/mod:mul_inline",
    ],
)

cc_library(
    name = "rho128",
    hdrs = ["rho128.h"],
    deps = [
        "//math:montgomery_mul",
        "//math/gcd:gcd128",
        "//math/mod:add",
    ],
)

cc_library(
    name = "segmented_prime_iterator",
    hdrs = ["segmented_prime_iterator.h"],
)
