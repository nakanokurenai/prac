# (c) Eguchi

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
def bi_op?(c)
  BINARY_OPERATORS.include?(c)
end

OPERATORS = BINARY_OPERATORS
def op?(c)
  OPERATORS.include?(c)
end

# Generate tree
def grouping(a)
  return [a.first.to_i, 1] unless op?(a.first)

  op = a.first
  node = [op]

  seek = 1
  if bi_op?(op)
    2.times do
      child, s = grouping(a[seek..a.size])
      seek += s
      node.push(child)
    end
  end

  [node, seek]
end

# Calculate [op, ...numbers] node
def operator!(op, *args)
  raise "Unhandled." unless op?(op)
  if bi_op?(op)
    left, right = args
	return BINARY_OPERATIONS[op].call(left, right)
  end
end

# Eval tree recursively
def visit!(tree)
  op = tree.first
  args = tree[1..tree.size].map { |child| child.is_a?(Array) ? visit!(child) : child }
  operator!(
    op,
    *args
  )
end

def calc_pn(s)
  tree, = grouping(s.split ' ')
  visit!(tree)
end

puts "ポーランド記法:"
p calc_pn gets
