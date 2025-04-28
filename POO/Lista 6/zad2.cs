using System;
using System.Collections.Generic;

public class Context
{
    private Dictionary<string, bool> variables = new Dictionary<string, bool>();

    public bool SetValue(string variableName, bool value)
    {
        variables[variableName] = value;
        return true;
    }

    public bool GetValue(string variableName)
    {
        if (!variables.ContainsKey(variableName))
            throw new Exception($"Brak wartości dla zmiennej: {variableName}");
        return variables[variableName];
    }
}

public abstract class AbstractExpression
{
    public abstract bool Interpret(Context context);
}

public class ConstExpression : AbstractExpression
{
    private readonly bool value;

    public ConstExpression(bool value)
    {
        this.value = value;
    }

    public override bool Interpret(Context context)
    {
        return value;
    }
}

public class VariableExpression : AbstractExpression
{
    private readonly string name;

    public VariableExpression(string name)
    {
        this.name = name;
    }

    public override bool Interpret(Context context)
    {
        return context.GetValue(name);
    }
}

public class UnaryExpression : AbstractExpression
{
    private readonly AbstractExpression operand;

    public UnaryExpression(AbstractExpression operand)
    {
        this.operand = operand;
    }

    public override bool Interpret(Context context)
    {
        return !operand.Interpret(context);
    }
}

public enum BinaryOperator
{
    And,
    Or
}

public class BinaryExpression : AbstractExpression
{
    private readonly AbstractExpression left;
    private readonly AbstractExpression right;
    private readonly BinaryOperator op;

    public BinaryExpression(AbstractExpression left, AbstractExpression right, BinaryOperator op)
    {
        this.left = left;
        this.right = right;
        this.op = op;
    }

    public override bool Interpret(Context context)
    {
        bool lval = left.Interpret(context);
        bool rval = right.Interpret(context);
        switch (op)
        {
            case BinaryOperator.And:
                return lval && rval;
            case BinaryOperator.Or:
                return lval || rval;
            default:
                throw new NotImplementedException();
        }
    }
}


class Zad2
{
    public static void Main(string[] args)
    {
        Context ctx = new Context();
        ctx.SetValue("x", false);
        ctx.SetValue("y", true);
        AbstractExpression expression = new BinaryExpression(
            new BinaryExpression(
                new UnaryExpression(new VariableExpression("x")),
                new VariableExpression("y"),
                BinaryOperator.And
            ),
            new ConstExpression(true),
            BinaryOperator.Or
        );
        bool result = expression.Interpret(ctx);
        Console.WriteLine($"{result}");
    }
}
