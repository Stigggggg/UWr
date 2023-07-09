class Function
  def initialize(&block)
    @function=block
  end
  def value(x)
    @function.call(x)
  end
  def zero(a, b, e)
    while((a-b).abs>e)
      x1=(a+b)/2
      if((@function.call(x1)).abs<=e)
        break
      elsif(@function.call(x1)*@function.call(a)<0)
        b=x1
      else
        a=x1
      end
    end
    (a+b)/2
  end
  def field(a,b)
    eps=0.0001
    x=a
    suma=0
    while(x<b)
      suma+=eps*(@function.call(x)+@function.call(x+eps))/2
      x+=eps
    end
    suma
  end
  def deriv(x)
    eps=0.0001
    (value(x+eps)-value(x-eps))/(2*eps)
  end
end

f=Function.new { |x| x**2 * Math.sin(x) }
puts f.value(1/2)
puts f.zero(-1,1,0.0001)
puts f.field(-1,1)
puts f.deriv(1)
