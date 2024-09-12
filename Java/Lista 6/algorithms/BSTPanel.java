package algorithms;

import java.awt.*;
import javax.swing.*;

public class BSTPanel extends JPanel 
{
    private BST<String> bst;
    public BSTPanel(BST<String> bst)
    {
        this.bst=bst;
    }
    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        drawTree(g,getWidth()/2,30,bst.root,getWidth()/4);
    }
    private void drawTree(Graphics g, int x, int y, BST<String>.Node<String> node, int xOffset)
    {
        if(node!=null)
        {
            g.drawString(node.value.toString(),x,y);
            if(node.left!=null)
            {
                int x_l=x-xOffset;
                int y_l=y+50;
                g.drawLine(x,y,x_l,y_l);
                drawTree(g,x_l,y_l,node.left,xOffset/2);
            }
            if(node.right!=null)
            {
                int x_r=x+xOffset;
                int y_r=y+50;
                g.drawLine(x,y,x_r,y_r);
                drawTree(g,x_r,y_r,node.right,xOffset/2);
            }
        }
    }
}
