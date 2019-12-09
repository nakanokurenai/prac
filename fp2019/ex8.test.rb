require_relative "ex8_randomized_algorithm.rb"

def test_di_square
  puts definite_integral_random(1,0,100) {|x|x}
  puts definite_integral_random(1,0,1000) {|x|x}
  puts definite_integral_random(1,0,10000) {|x|x}
end
test_di_square


