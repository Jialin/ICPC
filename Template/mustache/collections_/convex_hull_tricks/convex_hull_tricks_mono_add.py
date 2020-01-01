from math_.floor_div import FloorDivMustache
from mustache import AbstractMustache


class ConvexHullTricksMonoAddMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/' \
        'convex_hull_tricks_mono_add.mustache'

  def partials(self):
    return {'floor_div': FloorDivMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/' \
        '{{minmax.lower}}_convex_hull_tricks_add_{{incdec.lower}}.cpp'


def variables(minmax, incdec):
  return {'minmax': {'lower': 'min', 'cap': 'Min', '-inf': 'max', 'cmp': '<'} if minmax else {'lower': 'max', 'cap': 'Max', '-inf': 'min', 'cmp': '>'},
          'incdec': {'lower': 'increasing', 'cap': 'Increasing'} if incdec else {'lower': 'decreasing', 'cap': 'Decreasing'},
          'reverse': {'v': False, 'inf': 'min', 'cmp': '<'} if minmax ^ incdec else {'v': True, 'inf': 'max', 'cmp': '>'}}


JOBS = [(ConvexHullTricksMonoAddMustache('collections'),
         [variables(minmax=False, incdec=False),
          variables(minmax=False, incdec=True),
          variables(minmax=True, incdec=False),
          variables(minmax=True, incdec=True)])]
