import os
import sys
from math.sgn import JOBS as mathSgnJobs
from math.sgn_fraction import JOBS as mathSgnFractionJobs
from math.sgn_product_unsigned import JOBS as mathSgnProductUnsignedJobs

from collections_.convex_hull_tricks.convex_hull_tricks import \
    JOBS as collectionsConvexHullTricksJobs

ALL_JOBS = [collectionsConvexHullTricksJobs, mathSgnFractionJobs, mathSgnJobs,
            mathSgnProductUnsignedJobs]

for jobs in ALL_JOBS:
  for mustache, contexts in jobs:
    for context in contexts:
      mustache.genFile(context)
