#ifndef CALCULATOR_PROJECT_AST_H
#define CALCULATOR_PROJECT_AST_H

typedef enum NodeKind {
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_NEGATE,
    NODE_BINARY,
    NODE_CALL
} NodeKind;

typedef enum OperationKind {
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_POWER
} OperationKind;

typedef struct Node {
    NodeKind kind;
    int position;

    union {
        struct {
            double value;
        } number;

        struct {
            const char *nameStart;
            int nameLength;
        } variable;

        struct {
            struct Node *operand;
        } negate;

        struct {
            OperationKind op;
            struct Node *left;
            struct Node *right;
        } binary;

        struct {
            const char *nameStart;
            int nameLength;
            struct Node *argument;
        } call;
    } as;
} Node;

void resetPool(void);
Node *makeNumberNode(double value, int position);
Node *makeVariableNode(const char *nameStart, int nameLength, int position);
Node *makeNegateNode(Node *operand, int position);
Node *makeBinaryNode(OperationKind op, Node *left, Node *right, int position);
Node *makeCallNode(const char *nameStart, int nameLength, Node *argument, int position);
void printTree(const Node *tree);

#endif //CALCULATOR_PROJECT_AST_H
