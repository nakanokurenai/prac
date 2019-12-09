def quicksort(a)
  return a if a.length <= 1
  pivot_pos = rand(a.length)
  pivot = a[pivot_pos]
  smaller_than_pivot = []
  bigger_than_pivot = []
  a.each_with_index do |v, i|
    next if i == pivot_pos
  	if v <= pivot
      smaller_than_pivot.push v
  	elsif v > pivot
  	  bigger_than_pivot.push v
  	end
  end
  return quicksort(smaller_than_pivot) + [pivot] + quicksort(bigger_than_pivot)
end
