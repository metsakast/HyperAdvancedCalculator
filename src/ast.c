#include "ast.h"
#include <stddef.h>

#define MAXIMUM_NODE_COUNT 256

static Node nodeArray[MAXIMUM_NODE_COUNT];
static int nextFreeNode = 0;

static Node *nodeAssigner(const NodeKind kind, int position) {
    // make sure that free nodes are available, assign n, set kind and position, return n.
    if (nextFreeNode >= MAXIMUM_NODE_COUNT) return NULL;

    Node *n = &nodeArray[nextFreeNode];
    nextFreeNode++;

    n->kind = kind;
    n->position = position;

    return n;
}

void resetPool(void) {
    nextFreeNode = 0;
}

Node *makeNumberNode(double value, int position) {
    Node *n = nodeAssigner(NODE_NUMBER, position);
    if (n == NULL) return NULL;

    n->as.number.value = value;

    return n;
}

Node *makeVariableNode(const char *nameStart, int nameLength, int position) {
    Node *n = nodeAssigner(NODE_VARIABLE, position);
    if (n == NULL) return NULL;

    n->as.variable.nameLength = nameLength;
    n->as.variable.nameStart = nameStart;

    return n;
}

Node *makeNegateNode(Node *operand, int position) {
    Node *n = nodeAssigner(NODE_NEGATE, position);
    if (n == NULL) return NULL;

    n->as.negate.operand = operand;

    return n;
}

Node *makeBinaryNode(OperationKind op, Node *left, Node *right, int position) {
    Node *n = nodeAssigner(NODE_BINARY, position);
    if (n == NULL) return NULL;

    n->as.binary.op = op;
    n->as.binary.left = left;
    n->as.binary.right = right;

    return n;
}

Node *makeCallNode(const char *nameStart, int nameLength, Node *argument, int position) {
    Node *n = nodeAssigner(NODE_CALL, position);
    if (n == NULL) return NULL;

    n->as.call.nameStart = nameStart;
    n->as.call.nameLength = nameLength;
    n->as.call.argument = argument;

    return n;
}

void printTree(const Node *tree) {

}


