#include <mpi.h>
#include <stdio.h>   // For printf and fprintf
#include <stdlib.h>  // For EXIT_SUCCESS, EXIT_FAILURE

/* Function prototypes */
void send_data();
void recv_data();

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int num_procs;
    int my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (num_procs != 2) {
        fprintf(stderr, "Error: Run this program in MPI with 2 processes.\n");
        MPI_Finalize(); // Make sure to finalize MPI before exiting on error
        return EXIT_FAILURE;
    }

    // Send data from rank 0 to rank 1
    if (my_rank == 0) {
        send_data();
    } else {
        recv_data();
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}

void send_data()
{
    int send_data[10];
    for (int i = 0; i < 10; i++) {
        send_data[i] = i + 1;
    }
    int data_count = 10;

    printf("Rank 0: Sending data.\n");
    printf("send_data: [");
    for (int i = 0; i < 10; i++)
        printf(" %d", send_data[i]);
    printf(" ]\n");

    MPI_Send((void*)send_data, data_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
}

void recv_data()
{
    int data[10];
    int data_count = 10;
    MPI_Status st;

    printf("Rank 1: Receiving data.\n");
    MPI_Recv((void*)data, data_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
    printf("recv_data: [");
    for (int i = 0; i < 10; i++)
        printf(" %d", data[i]);
    printf(" ]\n");
}
