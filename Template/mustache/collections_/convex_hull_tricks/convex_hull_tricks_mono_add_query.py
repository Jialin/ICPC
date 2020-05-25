from math_.floor_div import FloorDivMustache
from mustache import AbstractMustache


class ConvexHullTricksMonoAddQueryMustache(AbstractMustache):
  def templateFile(self):
    return 'collections_/convex_hull_tricks/'\
        'convex_hull_tricks_mono_add_query.mustache'

  def partials(self):
    return {'floor_div': FloorDivMustache().genText()}

  def outputFile(self):
    return 'collections/convex_hull_tricks/' \
        '{{minmax.lower}}_convex_hull_tricks_'\
        'add_{{addincdec.lower}}_'\
        'query_{{queryincdec.lower}}.cpp'


def variables(minmax, addincdec, queryincdec):
  return {'minmax': {'lower': 'min', 'cap': 'Min', '-inf': 'max', 'cmp': '<'} if minmax else {'lower': 'max', 'cap': 'Max', '-inf': 'min', 'cmp': '>'},
          'addincdec': {'lower': 'increasing', 'cap': 'Increasing'} if addincdec else {'lower': 'decreasing', 'cap': 'Decreasing'},
          'queryincdec': {'v': True, 'lower': 'increasing', 'cap': 'Increasing'} if queryincdec else {'v': False, 'lower': 'decreasing', 'cap': 'Decreasing'},
          'addreverse': {'v': False, 'inf': 'min', 'cmp': '<'} if minmax ^ addincdec else {'v': True, 'inf': 'max', 'cmp': '>'}}


JOBS = [(ConvexHullTricksMonoAddQueryMustache('collections'),
         [variables(minmax=False, addincdec=False, queryincdec=False),
          variables(minmax=False, addincdec=False, queryincdec=True),
          variables(minmax=False, addincdec=True, queryincdec=False),
          variables(minmax=False, addincdec=True, queryincdec=True),
          variables(minmax=True, addincdec=False, queryincdec=False),
          variables(minmax=True, addincdec=False, queryincdec=True),
          variables(minmax=True, addincdec=True, queryincdec=False),
          variables(minmax=True, addincdec=True, queryincdec=True)])]
