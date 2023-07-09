class Function2D
  def initialize(f)
    @f=f
  end
  def value(x, y)
    @f.call(x, y)
  end
  def volume(a,b,c,d,dx = 0.01,dy = 0.01)
    sum=0.0
    x_range=(a..b).step(dx).to_a
    y_range=(c..d).step(dy).to_a
    x_range.each do |x|
      y_range.each do |y|
        sum+=value(x,y)*dx*dy
      end
    end
    sum
  end
  def contour_line(a,b,c,d,height,dx,dy,epsilon)
    result=[]
    x_range=(a..b).step(dx).to_a
    y_range=(c..d).step(dy).to_a
    x_range.each do |x|
      y_range.each do |y|
        if (value(x,y)-height).abs<epsilon
          result<<[x,y]
        end
      end
    end
    result
  end
end

f = lambda { |x, y| Math.sin(x*y) }
function = Function2D.new(f)
puts function.value(0,0)
puts function.value(Math::PI,1)
puts function.volume(0,Math::PI,0,1)
points = function.contour_line(0,Math::PI,0,1,0.5,0.01,0.01,0.001)
puts points.size
puts points[0]
puts points[-1]
