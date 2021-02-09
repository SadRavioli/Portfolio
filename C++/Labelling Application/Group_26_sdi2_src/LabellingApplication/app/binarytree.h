#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QtCore/QDateTime>

/**
* @brief Binary tree file system.
*
*/
class BinaryTree
{
public:

    QStringList traversal;

    struct TreeNode
    {
        QString data;
        QString date;
        struct TreeNode *left;
        struct TreeNode *right;
    };

    TreeNode *root;
    /**
         * @brief Constructor for BinaryTree class
         *
         * @param parent
         */
        BinaryTree();

        /**
         * @brief Function to insert node into tree
         * Each node stores filename and the time it was created
         *
         * @param parent
         */
        void insertNode(QString, QString);
        /**
         * @brief Function to remove node from tree
         * Takes filename and calls deleteNode function with root
         *
         * @param parent
         */
        void remove(QString);
        /**
         * @brief Recursive function that goes through each node
         * and then calls makeDeletion when the node is found
         *
         * @param parent
         */
        void deleteNode(QString, TreeNode *&);
        /**
         * @brief Function to delete nodes
         *
         * @param parent
         */
        void makeDeletion(TreeNode *&);
        /**
         * @brief Calls displayInOrder function
         *
         * @param parent
         */
        void showNodeInOrder(void);
        /**
         * @brief Calls reverseInOrder function
         *
         * @param parent
         */
        void showNodeInReverseOrder(void);
        /**
         * @brief Recursive function that goes left as far as it can, before adding
         * node to traversal list, then right
         *
         * @param parent
         */
        void displayInOrder(TreeNode *);
        /**
         * @brief Recursive function like InOrder but reverse. Right, add to list, left.
         *
         * @param parent
         */
        void reverseInOrder(TreeNode *);
        /**
         * @brief Function that searches for node of particular value. Returns true or false
         *
         * @param parent
         */
        bool searchNode(QString);
        /**
         * @brief Function to return traversal list.
         *
         * @param parent
         */
        QStringList returnTraversal(void);

    };


#endif // BINARYTREE_H
