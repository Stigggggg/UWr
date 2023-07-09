class Kolekcja
  attr_reader :size
  def initialize
    @head=nil
    @tail=nil
    @size=0
  end
  def add(element)
    node=Node.new(element)
    if(@head.nil?)
      @head=node
      @tail=node
    else
      @tail.next=node
      node.prev=@tail
      @tail=node
    end
    @size+=1
  end
  def get(index)
    return nil if(index<0 || index>=@size)
    current=@head
    index.times {current=current.next}
    current.element
  end

  class Node
    attr_accessor :prev,:next,:element
      def initialize(element)
      @prev=nil
      @next=nil
      @element=element
      end
  end
end

class Wyszukiwanie
  def self.wyszukiwanie_binarne(kolekcja,element)
    left=0
    right=kolekcja.size-1
    while(left<=right)
      mid=(left+right)/2
      value=kolekcja.get(mid)
      if (value==element)
        return mid
      elsif (value<element)
        left=mid+1
      else
        right=mid-1
      end
    end
    return nil
  end
  def self.wyszukiwanie_interpolacyjne(kolekcja, element)
    left=0
    right=kolekcja.size-1
    while(left <= right)
      range=kolekcja.get(right)-kolekcja.get(left)
      position=left+((element-kolekcja.get(left))*(right - left)/range).to_i
      value=kolekcja.get(position)
      if(value==element)
        return position
      elsif(value<element)
        left=position+1
      else
        right=position-1
      end
    end
    return nil
  end
end


collection=Kolekcja.new
collection.add(8)
collection.add(2)
collection.add(5)
collection.add(1)
collection.add(9)
result=Wyszukiwanie.wyszukiwanie_binarne(collection,5)
puts "Indeks: #{result}"

