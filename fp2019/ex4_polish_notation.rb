def op?(c)
  operations = ["+", "-", "*", "/", "^"]
  operations.include?(c)
end
def calculate(op, *args)
  left, right = args
  case op
  when "+"
    left + right
  when "-"
    left - right
  when "*"
    left * right
  when "/"
    left / right
  when "^"
    left ** right
  end
end
def grouping(a)
  return [a.first.to_i, 1] unless op?(a.first)
  seek = 1
  lv, ls = grouping(a[seek..a.size])
  seek += ls
  rv, rs = grouping(a[seek..a.size])
  seek += rs
  [[a.first, lv, rv], seek]
end
def visit(tree)
  op = tree.first
  calculate(
    op,
    tree[1].is_a?(Array) ? visit(tree[1]) : tree[1],
    tree[2].is_a?(Array) ? visit(tree[2]) : tree[2],
  )
end

def calc_pn(s)
  tree, = grouping(s.split ' ')
  visit(tree)
end

puts "ポーランド記法:"
p calc_pn gets
