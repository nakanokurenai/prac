def merge_sort(a)
  return a if a.length === 1

  left, right = split_array(a)
  merged_left = merge_sort(left)
  merged_right = merge_sort(right)

  merge(merged_left, merged_right)
end
def split_array(a)
  raise if a.length === 1 # something wrong

  break_point = a.length / 2
  [a[0..(break_point-1)], a[break_point...a.length]]
end
def merge(left, right)
  r = []

  l_value = left.shift()
  r_value = right.shift()
  while !l_value.nil? || !r_value.nil?  do
    if l_value.nil?
      r.push(r_value)
      r_value = right.shift()
      next
    end
    if r_value.nil?
      r.push(l_value)
      l_value = left.shift()
      next
    end
    if l_value < r_value
      r.push(l_value)
      l_value = left.shift()
      next
    end
    if r_value <= l_value
      r.push(r_value)
      r_value = right.shift()
      next
    end
  end
  return r
end
