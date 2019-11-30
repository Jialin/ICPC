import os
import sys

from collections_.convex_hull_tricks.convex_hull_tricks import \
    JOBS as collectionsConvexHullTricksJobs
from collections_.convex_hull_tricks.convex_hull_tricks_mono_add_query import \
    JOBS as collectionsConvexHullTricksMonoAddQueryJobs
from math_.floor_div import JOBS as mathFloorDivJobs
from math_.sgn import JOBS as mathSgnJobs
from math_.sgn_fraction import JOBS as mathSgnFractionJobs
from math_.sgn_product_unsigned import JOBS as mathSgnProductUnsignedJobs

ALL_JOBS = [collectionsConvexHullTricksJobs,
            collectionsConvexHullTricksMonoAddQueryJobs,
            mathFloorDivJobs,
            mathSgnFractionJobs,
            mathSgnJobs,
            mathSgnProductUnsignedJobs]

for jobs in ALL_JOBS:
  for mustache, contexts in jobs:
    for context in contexts:
      mustache.genFile(context)
