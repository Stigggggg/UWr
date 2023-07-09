class Variable extends Expression
{
    private String nazwa;
    private int val;
    public Variable(String nazwa)
    {
        this.nazwa=nazwa;
    }
    public void set_val(int val)
    {
        this.val=val;
    }
    public int evaluate()
    {
        return val;
    }
    public String to_string()
    {
        return nazwa;
    }
}
