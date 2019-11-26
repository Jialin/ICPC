from math.sgn_product_unsigned import SgnProductUnsignedMustache

from mustache import AbstractMustache


class SgnFractionMustache(AbstractMustache):
  def templateFile(self):
    return 'math/sgn_fraction.mustache'

  def partials(self):
    return {'sgn_product_unsigned': SgnProductUnsignedMustache().genText()}

  def outputFile(self):
    return 'math/sgn_fraction.cpp'


JOBS = [(SgnFractionMustache('math'), [{}])]
