#define MAX_STR_LEN 10

struct node_stack {
    struct node_stack* prev;
    char value[MAX_STR_LEN];
};

struct node_stack* init(const char* value);
struct node_stack* push(struct node_stack* stack, const char* value);
struct node_stack* pop(struct node_stack* stack, char* value_out);
char* peek(struct node_stack* stack, char* value_out);
void destroy(struct node_stack* stack);
