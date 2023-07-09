class Collection
  def initialize(arr)
    @arr = arr
  end
  def swap(i,j)
    @arr[i],@arr[j]=@arr[j],@arr[i]
  end
  def length
    @arr.length
  end
  def get(i)
    @arr[i]
  end
end

class Sorter
  def quick_sort(collection)
    quick_sort_recursive(collection,0,collection.length-1)
  end
  def quick_sort_recursive(collection,left,right)
    if (left<right)
      pivot_index=partition(collection,left,right)
      quick_sort_recursive(collection,left,pivot_index-1)
      quick_sort_recursive(collection,pivot_index+1,right)
    end
  end
  def partition(collection,left,right)
    pivot=collection.get(right)
    i=left-1
    left.upto(right-1) do |j|
      if(collection.get(j)<=pivot)
        i+=1
        collection.swap(i,j)
      end
    end
    collection.swap(i+1,right)
    i+1
  end
  def bubble_sort(collection)
    n=collection.length
    loop do
      swapped=false
      (n-1).times do |i|
        if(collection.get(i)>collection.get(i+1))
          collection.swap(i,i+1)
          swapped=true
        end
      end
      break unless swapped
    end
  end
  def sort1(collection)
    quick_sort(collection)
  end
  def sort2(collection)
    bubble_sort(collection)
  end
end

arr=[5,2,9,1,5,6]
collection=Collection.new(arr)
sorter=Sorter.new
sorter.sort1(collection)
puts "Quicksort: #{arr}"
arr=[5,2,9,1,5,6]
collection=Collection.new(arr)
sorter.sort2(collection)
puts "Bubblesort: #{arr}"
arr=(1..10000).to_a.shuffle
collection=Collection.new(arr)
t1=Time.now
sorter.sort1(collection)
t2=Time.now
puts "Czas quicksorta: #{t2 - t1} s"
arr=(1..10000).to_a.shuffle
collection=Collection.new(arr)
t1=Time.now
sorter.sort2(collection)
t2=Time.now
puts "Czas bubblesorta: #{t2 - t1} s"
