from math_.sgn import SgnMustache
from mustache import AbstractMustache


class SgnProductUnsignedMustache(AbstractMustache):
  def templateFile(self):
    return 'math_/sgn_product_unsigned.mustache'

  def partials(self):
    return {'sgn': SgnMustache().genText()}

  def outputFile(self):
    return 'math/sgn_product_unsigned.cpp'


JOBS = [(SgnProductUnsignedMustache('math'), [{}])]
