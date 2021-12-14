// Implementation of an AVL self-balancing binary tree.
// The implementation of AVL self-balancing algorithm has been done by Amitabha Roy, Roll No. 19012. 
// The rest has been taken from Gopi sir's repository.
#include<stdio.h>
#include<stdlib.h>

typedef struct student
{
	int rank;
    int height;
	struct student *left, *right, *parent;
}student;

student *tmp  = NULL;
student *temp;
student *node = NULL;
char direction;

// This function assigns the height value to each node in the tree, starting from the root node.
// Call the function by passing the root node of the desired subtree.
int assign_height(student* p_node)
{
    if (!p_node) return 0; // Return 0 in case of null pointer.

    // Determine the height values of the left and the right child nodes.
    int h_left = assign_height(p_node->left), h_right = assign_height(p_node->right);
    
    // Compute thee height of the present node.
    p_node->height = (h_left >= h_right) ? (h_left + 1) : (h_right + 1);

    // Return the height of the present node.
    return p_node->height;
}

// This function balances the tree following the AVL algorithm.
// Call this function after ensuring that the height values are properly assigned.
// The parameter is the parent node of the node of operation.
/* nDirVal stores the direction of the connection betwene p_node_child and one of its child node. 
   The child node in this context contains the newly inserted element in its subtree.
*/  
void avl_balance(student** p_root_node_ptr, student* p_node, student* p_node_child, int nDirVal)
{   
    // Return in case null has been passed.
    if (!p_node) return;
    
    // Check the present node for disbalance. 
    int bal_fac = 0;
    
    // Determine balance factor of this node.
    if (p_node->left && p_node->right)
        bal_fac = p_node->right->height - p_node->left->height;
    else if (p_node->left)
        bal_fac = -p_node->left->height;
    else if (p_node->right)
        bal_fac = p_node->right->height;

    // If the subtree is left-heavy and against AVL condition.
    if (bal_fac < -1)
    {
        // LL rotation necessary.
        if (nDirVal == 1)
        {
            student *p_prev_left_node = p_node->left, // Left child of p_node before LL rotation.
                    *p_new_parent_node = p_node->left, // New parent of p_node after LL rotation.
                    *p_prev_parent_node = p_node->parent; // The parent of p_node before LL rotation.

            printf("\nPerforming LL rotation at node %d.\n", p_node->rank);

            // Perform clockwise-rotation at this node.
            // If the present node has no parent node, i.e, root node.
            if (!p_node->parent)
            {
                p_new_parent_node->parent = NULL; // The previous left child is the new parent node of the entire tree.
                *p_root_node_ptr = p_prev_left_node; // Reset the root node pointer in the main function.
            } 
            else
            {
                // The new parent of the previous left child is the parent of p_node.
                p_new_parent_node->parent = p_prev_parent_node;

                // Check if the present node is a left child or right child of the previous parent node.
                // Change the child accordingly for rotation.
                if (p_prev_parent_node->left == p_node)
                    p_prev_parent_node->left = p_new_parent_node;
                else
                    p_prev_parent_node->right = p_new_parent_node;
            }

            // The new parent of the present node is the previous left child.
            p_node->parent = p_prev_left_node;
        
            // Check if there is a right sub-tree of the new parent node.
            if (p_new_parent_node->right)
            {
                p_node->left = p_new_parent_node->right;
                p_node->left->parent = p_node; // Connect the left child of p_node with p_node completely from both the sides.
            }
            else // Otherwise there is no left child of this node.
                p_node->left = NULL;

            // Connect the new parent of this node with this node.
            p_new_parent_node->right = p_node;
        }
        else // LR rotation necessary.
        {
            student *p_prev_left_node = p_node->left, // Left node of the present node before rotation.
                    *p_new_parent_node = p_node->left->right, // Right child of the left child of p_node is the new parent of p_node.
                    *p_prev_parent_node = p_node->parent; // The parent node of p_node before LR rotation.

            // Message.
            printf("Performing LR rotation.\n");

            // Perform clockwise-rotation at this node.
            // If the present node has no parent node, i.e, it is the root node.
            if (!p_node->parent)
            {
                p_new_parent_node->parent = NULL; // The left child is the new parent node of the entire tree.
                *p_root_node_ptr = p_new_parent_node; // Reset the root node pointer in the main function.
            } 
            else
            {    
                p_new_parent_node->parent = p_prev_parent_node; // The parent of p_node is transfered to p_node->left->right.

                // Check if the present node is a left child or right child of its parent node.
                // Change the child accordingly for rotation.
                if (p_prev_parent_node->left == p_node)
                    p_prev_parent_node->left = p_new_parent_node;
                else
                    p_prev_parent_node->right = p_new_parent_node;
            }

            // The new parent of the left child is the parent of this node.
            p_prev_left_node->parent = p_new_parent_node;

            // The new parent of the present node is p_node->left->right. (As per LR rotation procedure)
            p_node->parent = p_new_parent_node;
            
            // Check if there is a right sub-tree of the node which has been set as the parent.
            if (p_new_parent_node->right)
            {
                p_node->left = p_new_parent_node->right;
                p_node->left->parent = p_node;
            }
            else // Otherwise there is no left child of this node.
                p_node->left = NULL;
            
            // Check if there is a left sub-tree of the node which has been set as the parent.
            if (p_new_parent_node->left)
            {
                p_prev_left_node->right = p_new_parent_node->left;
                p_prev_left_node->right->parent = p_prev_left_node;
            }
            else
                p_prev_left_node->right = NULL;

            // Connect the new parent node with its left and right nodes.
            p_new_parent_node->right = p_node;
            p_new_parent_node->left = p_prev_left_node;
        }
    }
    else if (bal_fac > 1) // If the subtree is right-heavy and against AVL condition.
    {
        // RR rotation necessary.
        if (nDirVal == 2) 
        {
            student *p_prev_right_node = p_node->right, // Left child of p_node before RR rotation.
                    *p_new_parent_node = p_node->right, // New parent of p_node after RR rotation.
                    *p_prev_parent_node = p_node->parent; // The parent of p_node before LL rotation.

            printf("Performing RR rotation.\n");

            // Perform anti-clockwise-rotation at this node.
            // If the present node has no parent node, i.e, root node.
            if (!p_node->parent)
            {
                p_new_parent_node->parent = NULL; // The right child of this node is the new parent of the entire tree.
                *p_root_node_ptr = p_node->right; // Reset the root node pointer in the main function.
            } 
            else
            {
                // The new parent of the right child (new parent of p_node) is the parent of this node.
                p_new_parent_node->parent = p_prev_parent_node;

                // Check if the present node is a left child or right child of its parent node.
                // Change the child accordingly for rotation.
                if (p_prev_parent_node->left == p_node)
                    p_prev_parent_node->left = p_new_parent_node;
                else
                    p_prev_parent_node->right = p_new_parent_node;
            }

            // The new parent of the present node is its previous right child.
            p_node->parent = p_new_parent_node;
        
            // Check if there is a left sub-tree of the new parent node.
            if (p_new_parent_node->left)
            {
                p_node->right = p_new_parent_node->left;
                p_node->right->parent = p_node; // Connect the left child of p_node with p_node completely from both the sides.
            }
            else // Otherwise there is no right child of this node.
                p_node->right = NULL;

            // Set the left child of new parent of the present node to the present node.
            p_new_parent_node->left = p_node;
        }
        else // RL rotation necessary.
        {
            student *p_prev_right_node = p_node->right, // Right node of the present node before rotation.
                    *p_new_parent_node = p_node->right->left, // Right child of the left child of p_node is the new parent of p_node.
                    *p_prev_parent_node = p_node->parent; // The parent node of p_node before RL rotation.

            // Message.
            printf("Performing RL rotation.\n");
         
            // Perform anti-clockwise-rotation at this node.
            // If the present node has no parent node, i.e, root node.
            if (!p_node->parent)
            {
                p_new_parent_node->parent = NULL; // The right child of is the new parent of the entire tree.
                *p_root_node_ptr = p_new_parent_node; // Reset the root node pointer in the main function.
            } 
            else
            {
                p_new_parent_node->parent = p_prev_parent_node; // .

                // Check if the present node is a left child or right child of its parent node.
                // Change the child accordingly for rotation.
                if (p_prev_parent_node->left == p_node)
                    p_prev_parent_node->left = p_new_parent_node;
                else
                    p_prev_parent_node->right = p_new_parent_node;
            }

            // The new parent of the right child is the parent of this node.
            p_prev_right_node->parent = p_new_parent_node;

            // The new parent of the present node is the right subtree of the left child.
            p_node->parent = p_new_parent_node;
            
            // Check if there is a right sub-tree of the node which has been set as the parent.
            if (p_new_parent_node->right)
            {
                p_prev_right_node->left = p_new_parent_node->right;
                p_prev_right_node->left->parent = p_prev_right_node;
            }
            else
                p_prev_right_node->left = NULL;

            // Check if there is a left sub-tree of the node which has been set as the parent.
            if (p_new_parent_node->left)
            {
                p_node->right = p_new_parent_node->left;
                p_node->right->parent = p_node;
            }
            else // Otherwise there is no left child of this node.
                p_node->right = NULL;
            
            // Connect the new parent node with its left and right nodes.
            p_new_parent_node->left = p_node;
            p_new_parent_node->right = p_prev_right_node;
        }
    }

    // Stop the recursion process in case the root node has been reached.
    if (p_node == *p_root_node_ptr) return;

    // In case no rotations has been done.
    if ((bal_fac >= -1) && (bal_fac <= 1))
    {
        //printf("In node %d\n", p_node->rank);
        avl_balance(p_root_node_ptr, p_node->parent, p_node, (p_node->left == p_node_child) ? 1 : 2); // Move onto the parent node of this node.
    }
    else
        assign_height(*p_root_node_ptr);  // Recompute heights.
}

student* new_node(student* nstd,int nrank)
{
	student *tstd = (student *)malloc(sizeof(student));
	tstd->rank = nrank;
	tstd->left = NULL;
	tstd->right = NULL;
	tstd->parent = nstd;
    tstd->height = 0;
	printf("\n%d node created @ %p under %p", nrank,tstd,tstd->parent);
	return tstd;
}

void add_loc(int nrank)
{
    if(nrank < node->rank)
    {
        printf("\n%d is less than %d", nrank, node->rank);
        if(node->left)
        {
            node=node->left;
            add_loc(nrank);
        }
        else
            direction='l';
    }
    else if(nrank > node->rank)
    {
        printf("\n%d is greater than %d", nrank, node->rank);
        if(node->right)
        {
            node=node->right;
            add_loc(nrank);
        }
        else
            direction='r';
    }
    else 
        direction='s';
}

void search(student* tstd, int trank)
{
	if(tstd)
	{
		printf("\nsearching at %p where key is %d",tstd,tstd->rank);
	if(tstd->rank == trank)
		tmp = tstd;
	else if(tstd->rank > trank)
		search(tstd->left, trank);
	else if(tstd->rank < trank)
		search(tstd->right, trank);
	else
		tmp=NULL;
	}
}

student* minimum(student* node)
{
	for(;node->left;node=node->left);
	return node;
}

student* maximum(student* node)
{
	for(;node->right;node=node->right);
	return node;
}

int delete(student *node)
{
/*
1. Find the pointer/node which needs to be deleted
2. There arises three cases
		1. Node is completely free from both left and right
					Make the link(either left or right) from parent node NULL
						- make a temporary parent node.
						- find in which direction the node to be deleted is connected.
						- Make that connection NULL
		2. Node is having either left or right subtree
		3. Node is is having both right and left subtrees
*/
	printf("\n%d need to be deleted which is at %p", node->rank, node);
	student* temp=node->parent;
	printf("\n%d parent details - %p",node->rank,(node->parent));

	if((node->left==NULL) && (node->right==NULL))
		{
			if(temp->rank > node->rank)
				temp->left=NULL;
			else
				temp->right=NULL;
		}
	else if((node->left==NULL) && (node->right))
		{
			if(temp->rank > node->rank)
			{
				temp->left=node->right;
				(node->right)->parent=temp;
			}
			else
			{
				temp->right=node->right;
				(node->right)->parent=temp;
			}
		}
      else if((node->right==NULL) && (node->left))
			{
				if(temp->rank > node->rank)
				{
					temp->left=node->left;
					(node->right)->parent=temp;
				}
				else
				{
					temp->right=node->left;
					(node->left)->parent=temp;
				}
			}
	   else	if((node->right)&&(node->left))
		{
			printf("\n %d has both left and right sub trees", node->rank);

			student* tmin=minimum(node->right);
			printf("\n Minimum of right subtree %d ",tmin->rank);
			node->rank=tmin->rank;
			delete(tmin);

		}

	//free(node);
	return 0;
}
void inorder(student *root)
{
	if (root != NULL)
	{
		inorder(root->right);
		printf("%d @ %p parent address:%p, height: %d\n", root->rank, root,root->parent, root->height);
		inorder(root->left);
	}
}
int main()
{
    int opt;
    int sval=0;
    int adval;
    char ch;
    int cnt;

    student *root = NULL;

    while(1)
    {
        printf("\n\n\n\n1. Add");
        printf("\n2. Delete");
        printf("\n3. Display Tree ");
        printf("\n4. Search");
        printf("\n5. Minimum");
        printf("\n6. Maximum");
        printf("\n7. Exit\n");
        printf("\n Choose your option from above list:  ");
        
        if(scanf("%d",&opt) != 1) break;

        switch(opt)
        {
        case 1:
                do
                {
                    printf("\n Add a new rank ");
                    scanf("%d",&sval);

                    if(sval>0)
                    {
                        if(root==NULL)
                            root=new_node(NULL,sval);
                        else
                        {
                            // printf("\nroot is not empty %p ",root);
                            node=root;
                            add_loc(sval);
                            switch(direction)
                            {
                                case 'l': printf("\n     direction =%c",direction);
                                                    printf("\n next location to add %d is left to %d",sval,node->rank);
                                                    node->left=new_node(node,sval);
                                                    break;
                                case 'r':  printf("\n     direction =%c",direction);
                                                    printf("\n next location to add %d is right to %d",sval,node->rank);
                                                    node->right=new_node(node,sval);
                                                    break;
                                case 's': printf("\n%d already exists.", sval);
                                                    break;
                            }

                            // Invoke AVL balance algorithm.
                            if ((direction == 'l') || (direction == 'r'))
                            {
                                // Refresh the height values of the tree.
                                assign_height(root);
                                
                                // 0 value for nDirVal since there is no node before the newly inserted node.
                                avl_balance(&root, node, (direction == 'l') ? node->left : node->right, 0); // Balance the tree from the parent node of the new node.                                                       
                            }
                        }
                    }
                    else 
                        printf("invalid rank");

                } while(sval <= 0);

                break;
        case 2: printf("\n Enter the key value to delete");
                scanf("%d",&sval);
                search(root,sval);
                if(tmp==root)
                {
                    printf("\nRoot can't be deleted");
                    break;
                }
                if(tmp)
                    delete(tmp);
                else
                    printf("\n key %d is not found",sval);
                break;

        case 3: printf("\n Display\n");
                if(root==NULL)
                    printf("\nNothing to display from tree");
                inorder(root);
                break;

        case 4: printf("\n Search for what? ");
                scanf("%d",&sval);
                tmp=NULL;
                search(root,sval);
                if(tmp)
                    printf("\n%d found @ %p", sval, tmp);
                else
                    printf("\n %d is found nowhere in tree", sval);
                break;

        case 5:
                if(root)
                    printf("\n Minimum : %d stored @ %p", minimum(root)->rank, minimum(root));
                else
                    printf("\n Tree is Empty....How can I find minimum? ");
                break;

        case 6:
                if(root)
                    printf("\n Maximum : %d stored @ %p", maximum(root)->rank, maximum(root));
                else
                    printf("\n Tree is Empty....How can I find maximum?");
                break;

        case 7: printf("\n ***Exit***\n");
                exit(0);

        default: printf("\n Invalid input");
                break;
        }
    }

	return 0;
}
