using System;
using System.Linq.Expressions;

public class PrintExpressionVisitor : ExpressionVisitor
{
    protected override Expression VisitConstant(ConstantExpression node)
    {
        Console.WriteLine("Constant: {0}", node.Value);
        return base.VisitConstant(node);
    }

    protected override Expression VisitParameter(ParameterExpression node)
    {
        Console.WriteLine("Parameter: {0} (Type: {1})", node.Name, node.Type);
        return base.VisitParameter(node);
    }

    protected override Expression VisitUnary(UnaryExpression node)
    {
        Console.WriteLine("Unary: {0} {1}", node.NodeType, node.Operand);
        return base.VisitUnary(node);
    }
}

class Zad4
{
    public static void Main()
    {
        var visitor = new PrintExpressionVisitor();
        Expression constExpr = Expression.Constant(100);
        Console.WriteLine("Visiting Constant:");
        visitor.Visit(constExpr);
        var param = Expression.Parameter(typeof(int), "x");
        Console.WriteLine("Visiting Parameter:");
        visitor.Visit(param);
        var negExpr = Expression.Negate(param);
        Console.WriteLine("Visiting Unary:");
        visitor.Visit(negExpr);
    }
}

