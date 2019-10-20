# ブロックで計算式を受けとる定積分関数. [a, b] の範囲で区間数 n で分割. 区間の左端を利用
def definite_integral_with_left_edge_of_section(a, b, n)
  dx = (b-a).to_f / n
  s = 0.0
  n.times do |i|
    x = a + dx * i
    y = yield(x)
    s += y * dx
  end
  s
end

# ブロックで計算式を受けとる定積分関数. [a, b] の範囲で区間数 n で分割. 区間の右端を利用
def definite_integral_with_right_edge_of_section(a,b,n)
  dx = (b-a).to_f / n
  s = 0.0
  n.times do |i|
    x = a + dx * (i+1)
    y = yield(x)
    s += y * dx
  end
  s
end

# ブロックで計算式を受けとる定積分関数. [a, b] の範囲で区間数 n で分割. 区間の中央を利用
def definite_integral_with_center_of_section(a,b,n)
  dx = (b-a).to_f / n
  half_dx = dx / 2
  s = 0.0
  n.times do |i|
    x = a + half_dx * (1 + i*2)
    y = yield(x)
    s += y * dx
  end
  s
end

puts "* Ex. 3"

def calc_definite_integral(a,b,n)
  expression = Proc.new
  puts "[#{a}, #{b}], n = #{n}"
  puts "\t=> #{definite_integral_with_left_edge_of_section(a,b,n, &expression)} (left edge)"
  puts "\t=> #{definite_integral_with_center_of_section(a,b,n, &expression)} (center)"
  puts "\t=> #{definite_integral_with_right_edge_of_section(a,b,n, &expression)} (right edge)"
end

def average_either_side_definite_integral(a,b,n)
  expression = Proc.new
  puts "[#{a}, #{b}], n = #{n}"
  left = definite_integral_with_left_edge_of_section(a,b,n, &expression)
  right = definite_integral_with_right_edge_of_section(a,b,n, &expression)
  r = (left+right)/2
  puts "\t=> #{r}"
end

def average_definite_integral(a,b,n)
  expression = Proc.new
  puts "[#{a}, #{b}], n = #{n}"
  left = definite_integral_with_left_edge_of_section(a,b,n, &expression)
  right = definite_integral_with_right_edge_of_section(a,b,n, &expression)
  center = definite_integral_with_center_of_section(a,b,n, &expression)
  r = (left+right+center)/3
  puts "\t=> #{r}"
end

puts ">> f(x) = x^2"
exp = Proc.new { |x| x ** 2 }

puts "1. 両端, 中央 でそれぞれ計算する (3.b)"
calc_definite_integral(1, 10, 100, &exp)
calc_definite_integral(1, 10, 10000, &exp)
calc_definite_integral(1, 10, 1000000, &exp)
puts "2. 両端の値を平均する (3.a)"
average_either_side_definite_integral(1, 10, 100, &exp)
average_either_side_definite_integral(1, 10, 10000, &exp)
average_either_side_definite_integral(1, 10, 1000000, &exp)
puts "3. すべてを平均する (3.c)"
average_definite_integral(1, 10, 100, &exp)
average_definite_integral(1, 10, 10000, &exp)
average_definite_integral(1, 10, 1000000, &exp)

def prime?(n)
  # 非常に愚直なアルゴリズムだが、大きな数を計算するわけではないので問題ないだろう.
  # i-1 までループしたい. times は 0 ~ i-1 なので利用できる
  n.times do |i|
    next if i < 2
    # sqrt(n) までの計算にすることで計算量を多少抑える
    return false if n % i == 0
    # 計算量を多少抑えるための break
    # i まで break せず (= false を返さず) 処理されている時点で i までの数が組みあわさる乗算は検証されているとすることができる. であるからもし解となる値があるなら i^2 より大きい乗算になることが明白である
    # この計算によって 241 などでは 241 回のループから 17 回のループに省略できる
    break if i**2 > n
  end
  true
end

puts # padding
puts "* Ex. 6"
puts ">> 素数判定"
[3,4,9,11,21,51,241].each do |i|
  puts "\t#{i}\t=> #{prime?(i)}"
end
