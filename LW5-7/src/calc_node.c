#include "../include/calc_node.h"
#include "../include/comp_utils.h"
#include "../include/manage_node.h"
#include "../include/tree.h"
#include "../include/message.h"

TreeNode* current_node = NULL;

void start_calc_node(int node_id, int parent_id) {
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_REP);
    char endpoint[64];
    sprintf(endpoint, "tcp://*:%d", 5555 + node_id);
    zmq_bind(socket, endpoint);
    current_node = create_node(node_id, getpid(), endpoint);

    while (1) {
        Message msg;
        int recv_result = receive_message(socket, &msg);
        if (recv_result > 0) {
            if (msg.target_id == node_id) {
                if (strcmp(msg.command, CMD_EXEC) == 0) {
                    char* result = find_substring(msg.data, msg.data + strlen(msg.data) + 1);
                    sprintf(msg.data, "%d: %s", node_id, result);
                    send_message(socket, &msg);
                } else if (strcmp(msg.command, CMD_PING) == 0) {
                    strcpy(msg.data, "1");
                    send_message(socket, &msg);
                }
            } else {
                int child_id = determine_child_to_forward(root, node_id, msg.target_id);
                if (child_id != -1) {
                    void* forward_socket = zmq_socket(context, ZMQ_REQ);
                    char child_endpoint[64];
                    sprintf(child_endpoint, "tcp://localhost:%d", 5555 + child_id);
                    zmq_connect(forward_socket, child_endpoint);
                    msg.source_id = node_id;

                    send_message(forward_socket, &msg);

                    receive_message(forward_socket, &msg);

                    send_message(socket, &msg);

                    zmq_close(forward_socket);
                } else {
                    strcpy(msg.data, "-1");
                    send_message(socket, &msg);
                }
            }
        }
    }
    zmq_close(socket);
    zmq_ctx_destroy(context);
}

int check_parent_availability(void* context, int parent_id, int node_id) {
    if (parent_id < 0) { return 1; }
    
    void* parent_socket = zmq_socket(context, ZMQ_REQ);
    char parent_endpoint[64];
    sprintf(parent_endpoint, "tcp://localhost:%d", 5555 + parent_id);
    
    int timeout = 1000;
    int linger = 0;
    zmq_setsockopt(parent_socket, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
    zmq_setsockopt(parent_socket, ZMQ_SNDTIMEO, &timeout, sizeof(timeout));
    zmq_setsockopt(parent_socket, ZMQ_LINGER, &linger, sizeof(linger));
    if (zmq_connect(parent_socket, parent_endpoint) != 0) {
        zmq_close(parent_socket);
        return 0;
    }

    Message msg = {0};
    strcpy(msg.command, CMD_PING);
    msg.source_id = node_id;
    msg.target_id = parent_id;
    if (send_message(parent_socket, &msg) <= 0) {
        zmq_close(parent_socket);
        return 0;
    }
    
    if (receive_message(parent_socket, &msg) <= 0) {
        zmq_close(parent_socket);
        return 0;
    }

    zmq_close(parent_socket);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <node_id> <parent_id>\n", argv[0]);
        return 1;
    }
    int node_id = atoi(argv[1]);
    int parent_id = atoi(argv[2]);
    start_calc_node(node_id, parent_id);
    return 0;
}