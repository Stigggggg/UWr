class ONPExpression
  OPERATORS=['+', '-', '*', '/'].freeze
  def initialize(tokens)
    @tokens = tokens
  end
  def evaluate(variables)
    stack=[]
    @tokens.each do |token|
      if OPERATORS.include?(token)
        b=stack.pop
        a=stack.pop
        result=calculate(a,b,token)
        stack.push(result)
      elsif variables.key?(token)
        stack.push(variables[token])
      else
        stack.push(token.to_i)
      end
      puts "Stos: #{stack.join(' ')}"
    end
    stack.pop
  end
  private
  def calculate(a, b, operator)
    case operator
    when '+'
      a+b
    when '-'
      a-b
    when '*'
      a*b
    when '/'
      a/b
    end
  end
end

expr=ONPExpression.new(['x','2','*','y','+'])
variables={'x'=> 3, 'y' => 4}
expr.evaluate(variables)


