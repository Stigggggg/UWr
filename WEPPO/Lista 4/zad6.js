function Tree(val, left, right) 
{
    this.left=left;
    this.right=right;
    this.val=val;
}

//przeszukiwanie w glab z wykladu
/*Tree.prototype[Symbol.iterator] = function*() {
    yield this.val;
    if ( this.left ) yield* this.left;
    if ( this.right ) yield* this.right;
}
    
var root = new Tree( 1,
    new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));
for ( var e of root ) {
    console.log( e );
}*/

Tree.prototype[Symbol.iterator]=function*()
{
    let queue=[];
    queue.push(this);
    while(queue.length>0)
    {
        console.log(queue);
        let node=queue.shift();
        yield node.val;
        if(node.left)
        {
            queue.push(node.left);
        }
        if(node.right)
        {
            queue.push(node.right);
        }
    }
};

var root=new Tree(1,new Tree(2,new Tree(3)),new Tree(4));
for(var e of root)
{
    console.log(e);
}

//dla stosu mielibysmy dodawanie na gore stosu i sciaganie od gory do dolu
//wiec byloby od prawej: 1 4 2 3 

