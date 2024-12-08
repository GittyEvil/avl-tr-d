//=============================================================================
// bst.c - binary search tree, based on binary tree (bt.h/bt.c)
//=============================================================================
#include "global.h"
#include "bst.h"

//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a);
static void _inorder(BST T, int* pos, int* a);
static void _postorder(BST T, int* pos, int* a);
//-----------------------------------------------------------------------------
// public functions, exported through bst.h
//-----------------------------------------------------------------------------
// new_BST: creates a new BST
BST new_BST(int val)
{
	return new_BT(val);
}
//-----------------------------------------------------------------------------
// bst_add: adds the value v to the BST T (unless duplicate)
//-----------------------------------------------------------------------------
BST bst_add(BST T, int v)
{
	return	!T            	?	new_BST(v)                            :
		v < get_val(T)	?	cons(add(get_LC(T), v), T, get_RC(T)) :
		v > get_val(T)	?	cons(get_LC(T), T, add(get_RC(T), v)) :
		/* duplicate */		T;
}
//-----------------------------------------------------------------------------
// bst_rem: removes the value val from the BST (if it exists)
//-----------------------------------------------------------------------------
BST bst_rem(BST T, int val)
{
	// TODO
    return !T ? NULL :
       val < get_val(T) ? cons(bst_rem(get_LC(T), val), T, get_RC(T)) :
       val > get_val(T) ? cons(get_LC(T), T, bst_rem(get_RC(T), val)) :
        /*
        kommer kolla höjden då barn finns på båda sidor, den med högst höjd får prio/åker upp
        är höjd lika då kommer vänster del prioriteras
        */
       !get_LC(T) ? get_RC(T) :
       !get_RC(T) ? get_LC(T) :
       (height(get_RC(T)) > height(get_LC(T)) ? ({
            BST successor = get_RC(T);
            while (get_LC(successor)) successor = get_LC(successor);
            cons(get_LC(T), set_val(T, get_val(successor)), bst_rem(get_RC(T), get_val(successor)));
    
        }) : ({
            BST predecessor = get_LC(T);
            while (get_RC(predecessor)) predecessor = get_RC(predecessor);
            cons(bst_rem(get_LC(T), get_val(predecessor)), set_val(T, get_val(predecessor)), get_RC(T));
        }));

    /*
    kommer nu även behöva kolla position på noder som tas bort och hur trädet ska anpassa sig för får 
    malloc problem och core dumped, misstänker en kombination av felhantering av malloc men sen hur jag tar bort
    använda sig av srl och srr typ

    problemet var att jag råkade ha static i varje order funktion för position variabeln, fixade det. Nu återstår att fixa att de inte fortsätter uppdatera rätt vid varje order funktion. fixade order funktionerna oxå, litet syntax fel
    nu återstår det att fixa så remove gör hantering av noder rätt
    */

}
//-----------------------------------------------------------------------------
// preorder: puts the BST T values into array a in preorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void preorder(BST T, int* a)
{
	int pos = 0;
	_preorder(T, &pos, a);
}
//-----------------------------------------------------------------------------
// inorder: puts the BST T values into array a in inorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [1,2,3]      / \  --> [2,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void inorder(BST T, int* a)
{
	// TODO
    /*
    LNR
    */
    int pos = 0;
    _inorder(T, &pos,a); 
}
//-----------------------------------------------------------------------------
// postorder: puts the BST T values into array a in postorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [1,3,2]      / \  --> [3,2]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void postorder(BST T, int* a)
{
	// TODO

    /*
    LRN
    */
    int pos = 0;  
    _postorder(T,&pos,a);
}
//-----------------------------------------------------------------------------
// bfs: puts the BST T values into array a in bfs-order, non-nodes
// are indicated by X, as defined in global.h
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,X,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void bfs(BST T, int* a, int max)
{
	// TODO
    /*
    breath first search metod

    vilket går ut på att kolla nivåer horisontellt för varje nivå
    alltså root -> root left child -> root right child -> left left child -> left right child -> right left child -> right right child osv
    */
    if(!T) {
        return;
    }
    //fyller upp listan med tomma platser
    for (int i = 0; i < max; i++) {
        a[i] = X; 
    }

    BST queue[max];
    int front = 0,back = 0;
    queue[back++] = T;
    a[0] = get_val(T);
    
    for(int pos = 0; front < back && pos < max; pos++) {
        //näst kommande nod
        BST current = queue[front++];
        if(current) {
            //för vänster
            if (get_LC(current)) {
                queue[back++] = get_LC(current);
                a[2 * pos + 1] = get_val(get_LC(current));
            } else {
                queue[back++] = NULL;
            }
            //för höger
            if (get_RC(current)) {
                queue[back++] = get_RC(current);
                a[2 * pos + 2] = get_val(get_RC(current));
            } else {
                queue[back++] = NULL;
            }
        } else {
            //för både vänster å höger
            queue[back++] = NULL;  
            queue[back++] = NULL; 
        }
    }
}
//-----------------------------------------------------------------------------
// is_member: checks if value val is member of BST T
//-----------------------------------------------------------------------------
bool is_member(BST T, int val)
{
    if(!T) {
        return false; 
    } else if (get_val(T) == val) {
        return true;
    } else if (val < get_val(T)) { 
        return is_member(get_LC(T), val); 
    }
    return is_member(get_RC(T), val); 
}
//-----------------------------------------------------------------------------
// height: returns height of BST T
//-----------------------------------------------------------------------------
int height(BST T)
{
    if(!T) {
        return 0; 
    }

    int leftHeight = height(get_LC(T)); 
    int rightHeight = height(get_RC(T)); 

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); 
    
}
//-----------------------------------------------------------------------------
// size: returns size of BST T
//-----------------------------------------------------------------------------
int size(BST T)
{
	if(!T) { 
        return 0; 
    }
    return 1 + size(get_LC(T)) + size(get_RC(T)); 
}
//-----------------------------------------------------------------------------
// private helper functions, not exported
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a)
{
	if (T)
	{
		a[(*pos)++] = get_val(T);
		_preorder(get_LC(T), pos, a);
		_preorder(get_RC(T), pos, a);
	}
}

static void _inorder(BST T, int* pos, int* a) {
    if (T) {
        _inorder(get_LC(T),pos, a); 
        a[(*pos)++] = get_val(T); 
        _inorder(get_RC(T),pos, a);
    }
}

static void _postorder(BST T, int* pos, int* a) {
    if (T) {
        _postorder(get_LC(T),pos, a);
        _postorder(get_RC(T),pos, a);
        a[(*pos)++] = get_val(T);
    }  
}
