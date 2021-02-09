#include "binarytree.h"


BinaryTree::BinaryTree()
{
    TreeNode *root;
}

void BinaryTree::insertNode(QString string, QString dateTime)
{
    TreeNode *newNode, *nodePtr;

    newNode = new TreeNode;
    newNode->data = string;
    newNode->date = dateTime;
    newNode->left = newNode->right = NULL;

    if (!root)
        root = newNode;
    else
    {
        nodePtr = root;
    }
    while (nodePtr != NULL)
    {
        if (string < nodePtr->data)
        {
            if (nodePtr->left)
                nodePtr = nodePtr->left;
            else
            {
                nodePtr->left = newNode;
                break;
            }
        }
        else if (string > nodePtr->data)
        {
            if (nodePtr->right)
                nodePtr = nodePtr->right;
            else
            {
                nodePtr->right = newNode;
                break;
            }
        }
        else
        {
            break;
        }
    }
}

void BinaryTree::remove(QString string)
{
    deleteNode(string, root);
}

void BinaryTree::deleteNode(QString string, TreeNode *&nodePtr)
{
    if (string < nodePtr->data)
        deleteNode(string, nodePtr->left);
    else if (string > nodePtr->data)
        deleteNode(string, nodePtr->right);
    else
        makeDeletion(nodePtr);
}

void BinaryTree::makeDeletion(TreeNode *&nodePtr)
{
    TreeNode *tempNodePtr;

    if (nodePtr == NULL)
        QMessageBox::information(0,"Error","Cannot delete empty node.\n");
    else if (nodePtr->right == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;
        delete tempNodePtr;
    }
    else if (nodePtr->left == NULL)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
    else
    {
        tempNodePtr = nodePtr->right;
        while (tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
}

void BinaryTree::showNodeInOrder(void)
{
    traversal.clear();
    displayInOrder(root);
}

void BinaryTree::showNodeInReverseOrder(void)
{
    traversal.clear();
    reverseInOrder(root);
}

void BinaryTree::displayInOrder(TreeNode *nodePtr)
{
    if (nodePtr)
    {
        displayInOrder(nodePtr->left);
        traversal.append(nodePtr->data);
        displayInOrder(nodePtr->right);
    }
}

void BinaryTree::reverseInOrder(TreeNode *nodePtr)
{
    if (nodePtr)
    {

        reverseInOrder(nodePtr->right);
        traversal.append(nodePtr->data);
        reverseInOrder(nodePtr->left);

    }
}

bool BinaryTree::searchNode(QString string)
{
    TreeNode *nodePtr = root;
    while (nodePtr)
    {
        if (nodePtr->data == string)
            return true;
        else if (string < nodePtr->data)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
}

QStringList BinaryTree::returnTraversal(void)
{
    return traversal;
}

