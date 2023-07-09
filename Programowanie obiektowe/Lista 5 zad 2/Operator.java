abstract class Operator extends Expression
{
    protected Expression left;
    protected Expression right;
    protected abstract String get_symbol();
    public Operator(Expression left, Expression right)
    {
        this.left=left;
        this.right=right;
    }
    public String to_string()
    {
        return "("+left.to_string()+get_symbol()+right.to_string()+")";
    }
}
