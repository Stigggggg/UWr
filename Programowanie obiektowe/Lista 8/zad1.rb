require('bigdecimal')

class Masa
    def initialize(kg)
        @kilogram=kg
    end
    def kilogram
        @kilogram
    end
    def funt
        @kilogram/0.453592
    end
    def funt=(m)
        @kilogram=m*0.453592
    end
end

class Dlugosc
    def initialize(m)
        @metr=m
    end
    def metr
        @metr
    end
    def cal
        @metr/0.0254
    end
    def cal=(dl)
        @metr=dl*0.0254
    end
end

class Powierzchnia
    def initialize(ha)
        @hektar=ha
    end
    def hektar
        @hektar
    end
    def hektar=(ha)
        @hektar=ha
    end
    def cal_k
        x=Dlugosc.new((@hektar*10000)**0.5)
        x.cal**2
    end
    def cal_k=(p)
        y=Dlugosc.new(0)
        y.cal(p)
        @hektar=((y.metr)**2)/10000
    end
end

class Cisnienie
    def initialize(c)
        @bar=c
    end
    def bar
        @bar
    end
    def bar=(c)
        @bar=c
    end
    def psi
        m=Masa.new(10000);
        p=Powierzchnia.new(BigDecimal(1)/BigDecimal(10000))
        @bar*(m.funt/p.cal_k)
    end
    def psi=(c)
        m=Masa.new(10000);
        p=Powierzchnia.new(BigDecimal(1)/BigDecimal(10000))
        @bar=c/(m.funt/p.cal_k)
    end
end

puts "Tabela jednostek powierzchni:"
puts "Jednostki SI  | Jednostki anglosaskie"
puts "----------------------------------------"
(1..9).each do |n|
  area = Powierzchnia.new(n)
  puts "#{area.hektar.round(2)} ha          | #{area.cal_k.round(2)} sq in"
end

puts "\nTabela jednostek ciśnienia:"
puts "Jednostki SI  | Jednostki anglosaskie"
puts "----------------------------------"
(1..9).each do |n|
  pressure = Cisnienie.new(n)
  puts "#{pressure.bar.round(2)} bar         | #{pressure.psi.round(2)} psi"
end



