package algorithms;

class BST<T extends Comparable<T>> implements Dictionary<T> 
{
    public class Node<U extends Comparable<U>>
    {
        Node<U> left,right;
        U value;
        Node(U value)
        {
            this.value=value;
            this.left=this.right=null;
        }
    }
    public Node<T> root;
    BST()
    {
        this.root=null;
    }
    @Override
    public boolean search(T x)
    {
        return search_rek(root,x);
    }
    private boolean search_rek(Node<T> root, T x)
    {
        if(root==null)
        {
            return false;
        }
        int comp=x.compareTo(root.value);
        if(comp==0)
        {
            return true;
        }
        else if(comp<0)
        {
            return search_rek(root.left,x);
        }
        else
        {
            return search_rek(root.right,x);
        }
    }
    @Override
    public void insert(T x)
    {
        if(x==null)
        {
            throw new IllegalArgumentException("Nie można dodać nulla do drzewa");
        }
        root=insert_rek(root,x);
    }
    private Node<T> insert_rek(Node<T> root, T x)
    {
        if(root==null)
        {
            return new Node<>(x);
        }
        if(root.value==x)
        {
            throw new IllegalStateException("W drzewie nie może być 2 takich samych wartości");
        }
        int comp=x.compareTo(root.value);
        if(comp<0)
        {
            root.left=insert_rek(root.left,x);
        }
        else if(comp>0)
        {
            root.right=insert_rek(root.right,x);
        }
        return root;
    }
    @Override 
    public void remove(T x)
    {
        root=remove_rek(root,x);
    }
    private Node<T> remove_rek(Node<T> root, T x)
    {
        if(root==null)
        {
            return null;
        }
        int comp=x.compareTo(root.value);
        if(comp<0)
        {
            root.left=remove_rek(root.left,x);
        }
        else if(comp>0)
        {
            root.right=remove_rek(root.right,x);
        }
        else
        {
            if(root.left==null)
            {
                return root.right;
            }
            else if(root.right==null)
            {
                return root.left;
            }
            root.value=find_min(root.right).value;
            root.right=remove_rek(root.right,root.value);
        }
        return root;
    }
    private Node<T> find_min(Node<T> root)
    {
        while(root.left!=null)
        {
            root=root.left;
        }
        return root;
    }
    @Override
    public T min()
    {
        if(root==null)
        {
            throw new IllegalStateException("Drzewo jest puste");
        }
        return find_min(root).value;
    }
    private Node<T> find_max(Node<T> root)
    {
        while(root.right!=null)
        {
            root=root.right;
        }
        return root;
    }
    @Override
    public T max()
    {
        if(root==null)
        {
            throw new IllegalStateException("Drzewo jest puste");
        }
        return find_max(root).value;
    }
    @Override
    public int size()
    {
        return size_rek(root);
    }
    private int size_rek(Node<T> root)
    {
        if(root==null)
        {
            return 0;
        }
        return 1+size_rek(root.left)+size_rek(root.right);
    }
    @Override
    public void clear()
    {
        root=null;
    }
    //Testy metod
    // public static void main(String[] args)
    // {
    //     BST<Integer> bst=new BST<>();
    //     bst.insert(5);
    //     bst.insert(3);
    //     bst.insert(7);
    //     bst.insert(12);
    //     System.out.println(bst.max());
    //     System.out.println(bst.min());
    //     System.out.println(bst.size());
    //     bst.clear();
    //     System.out.println(bst.size());
    //     System.out.println(bst.max());
    // }
}
