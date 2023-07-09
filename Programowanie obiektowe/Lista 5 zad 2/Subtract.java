class Subtract extends Operator
{
    public Subtract(Expression left, Expression right)
    {
        super(left,right);
    }
    public int evaluate()
    {
        return left.evaluate()-right.evaluate();
    }
    protected String get_symbol()
    {
        return "-";
    }
}
