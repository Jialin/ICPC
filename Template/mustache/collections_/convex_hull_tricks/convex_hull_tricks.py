from math.sgn_fraction import SgnFractionMustache

from mustache import AbstractMustache


class ConvexHullTricksMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/convex_hull_tricks.mustache'

  def partials(self):
    return {'sgn_fraction': SgnFractionMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/{{#isMax}}max{{/isMax}}{{^isMax}}min{{/isMax}}_convex_hull_tricks.cpp'


JOBS = [(ConvexHullTricksMustache('collections'),
         [{'isMax': True}, {'isMax': False}])]
