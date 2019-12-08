require 'minitest'
require "minitest/autorun"
require "minitest/benchmark"

require_relative "ex7_sort.rb"

def randarray(n)
  return Array.new(n) do rand(10000) end
end

class TestMergeSort < Minitest::Test
  def test_split_array_5
    assert_equal [[1,2], [3,4,5]], split_array([1,2,3,4,5])
  end
  def test_split_array_2
    assert_equal [[1], [2]], split_array([1,2])
  end
  def test_split_array_1
    assert_raises { split_array([1]) }
  end
  def test_split_array_random_100
    a = randarray(100)
    left, right = split_array(a)
    assert_equal left.length, 50
    assert_equal right.length, 50
    assert_equal a, left + right
  end

  def test_merge_sort_1
    assert_equal [1], merge_sort([1])
  end
  def test_merge_sort_3
    assert_equal [1,2,3], merge_sort([3,2,1])
  end
  def test_merge_sort_random_10
    a = randarray(10)
    assert_equal a.sort(), merge_sort(a)
  end
  def test_merge_sort_random
    a = randarray(100)
    assert_equal a.sort(), merge_sort(a)
  end
end

class TestSortAlgorithmBenchmark < Minitest::Benchmark
  def self.bench_range
    [1, 10, 100, 1_000, 10_000, 100_000, 1_000_000]
  end

  def bench_merge_sort
    assert_performance_linear do |n|
      ra = randarray(n)
      merge_sort(ra)
    end
  end

  def bench_sample_merge_sort
    skip
    assert_performance_linear do |n|
      ra = randarray(n)
      sample_mergesort(ra)
    end
  end
end
