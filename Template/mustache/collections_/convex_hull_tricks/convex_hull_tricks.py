from math_.floor_div import FloorDivMustache
from mustache import AbstractMustache


class ConvexHullTricksMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/convex_hull_tricks.mustache'

  def partials(self):
    return {'floor_div': FloorDivMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/{{minmax}}_convex_hull_tricks.cpp'


JOBS = [(ConvexHullTricksMustache('collections'),
         [{'MinMax': 'Min', 'minmax': 'min', 'lessgreater': 'greater', 'lessOp': '<'},
          {'MinMax': 'Max', 'minmax': 'max', 'lessgreater': 'less', 'lessOp': '>'}])]
