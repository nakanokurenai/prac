# 二項演算子 のみ
#   "+" 加算
#   "-" 除算
#   "*" 乗算
#   "/" 除算
#   "^" 冪乗
#   "%" 余剰

BINARY_OPERATIONS = {
  "+" => -> (l, r) { l + r },
  "-" => -> (l, r) { l - r },
  "*" => -> (l, r) { l * r },
  "/" => -> (l, r) { l / r },
  "^" => -> (l, r) { l ** r },
  "%" => -> (l, r) { l % r },
}
BINARY_OPERATORS = BINARY_OPERATIONS.keys
OPERATORS = BINARY_OPERATORS

def op?(c)
  OPERATORS.include?(c)
end

# Generate tree
def grouping(a)
  return [a.first.to_i, 1] unless op?(a.first)
  seek = 1
  lv, ls = grouping(a[seek..a.size])
  seek += ls
  rv, rs = grouping(a[seek..a.size])
  seek += rs
  [[a.first, lv, rv], seek]
end

# Calculate [op, ...numbers] node
def calculate_node!(op, *args)
  raise "NOT OP." unless OPERATORS.include?(op)
  if BINARY_OPERATORS.include?(op)
    left, right = args
	return BINARY_OPERATIONS[op].call(left, right)
  end
end

# Eval tree recursively
def visit!(tree)
  op = tree.first
  calculate_node!(
    op,
    tree[1].is_a?(Array) ? visit!(tree[1]) : tree[1],
    tree[2].is_a?(Array) ? visit!(tree[2]) : tree[2],
  )
end

def calc_pn(s)
  tree, = grouping(s.split ' ')
  visit!(tree)
end

puts "ポーランド記法:"
p calc_pn gets
