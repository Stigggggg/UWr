class Const extends Expression
{
    private int val;
    public Const(int value)
    {
        this.val=value;
    }
    public int evaluate()
    {
        return val;
    }
    public String to_string()
    {
        return Integer.toString(val);
    }
}
