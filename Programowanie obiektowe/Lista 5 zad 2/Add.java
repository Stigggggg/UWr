class Add extends Operator
{
    public Add(Expression left, Expression right)
    {
        super(left,right);
    }
    public int evaluate()
    {
        return left.evaluate()+right.evaluate();
    }
    protected String get_symbol()
    {
        return "+";
    }
}
