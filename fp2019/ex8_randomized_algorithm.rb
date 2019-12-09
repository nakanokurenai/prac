def pi_random(n)
  # n 回 1x1 領域の点を乱数で生成し、1/4 単位円に入っている点の割合を数えることで pi を求める
  count = n.times.reduce(0) do |c,_|
    x, y = rand, rand
    next c + 1 if x**2 + y**2 < 1.0
    next c
  end
  return 4 * count.to_f / n
end

def definite_integral_random(a,b,n,&f)
  # n回ランダムに生成した値で yield で表現される f(x) に対する $\int_{b}^{a} f(x) dx$ を行う
  total = n.times.reduce(0.0) do |total, _|
    x = rand((b.to_f)..(a.to_f))
    y = f.call(x)
    next total + y
  end
  return total / n
end
