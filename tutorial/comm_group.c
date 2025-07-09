#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size < 5) {
        if (world_rank == 0)
            fprintf(stderr, "Need at least 5 processes.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    // === Group A: {0,1,2,3} ===
    int ranks_a[] = {0, 1, 2, 3};
    MPI_Group group_a;
    MPI_Group_incl(world_group, 4, ranks_a, &group_a);
    MPI_Comm comm_a;
    MPI_Comm_create_group(MPI_COMM_WORLD, group_a, 0, &comm_a);

    // === Group B: {0,1,2,4} ===
    int ranks_b[] = {0, 1, 2, 4};
    MPI_Group group_b;
    MPI_Group_incl(world_group, 4, ranks_b, &group_b);
    MPI_Comm comm_b;
    MPI_Comm_create_group(MPI_COMM_WORLD, group_b, 1, &comm_b);

    // === 通信例: それぞれのcommで rank 0 が他のプロセスに送信 ===
    if (comm_a != MPI_COMM_NULL) {
        int comm_a_rank;
        MPI_Comm_rank(comm_a, &comm_a_rank);
        if (comm_a_rank == 0) {
            int msg = 100;
            for (int i = 1; i < 4; i++)
                MPI_Send(&msg, 1, MPI_INT, i, 0, comm_a);
        } else {
            int recv;
            MPI_Recv(&recv, 1, MPI_INT, 0, 0, comm_a, MPI_STATUS_IGNORE);
            printf("comm_a: World Rank %d received %d from Rank 0\n", world_rank, recv);
        }
    }

    if (comm_b != MPI_COMM_NULL) {
        int comm_b_rank;
        MPI_Comm_rank(comm_b, &comm_b_rank);
        if (comm_b_rank == 0) {
            int msg = 200;
            for (int i = 1; i < 4; i++)
                MPI_Send(&msg, 1, MPI_INT, i, 0, comm_b);
        } else {
            int recv;
            MPI_Recv(&recv, 1, MPI_INT, 0, 0, comm_b, MPI_STATUS_IGNORE);
            printf("comm_b: World Rank %d received %d from Rank 0\n", world_rank, recv);
        }
    }

    // === 試みに Rank 3 から Rank 4 に送ってみる（失敗する） ===
    if (world_rank == 3) {
        int msg = 999;
        int rc = MPI_Send(&msg, 1, MPI_INT, 4, 99, MPI_COMM_WORLD);
        printf("Rank 3 tried to send to Rank 4 via MPI_COMM_WORLD (rc=%d)\n", rc);
    }

    if (world_rank == 4) {
        int recv;
        MPI_Status status;
        int flag;
        MPI_Iprobe(3, 99, MPI_COMM_WORLD, &flag, &status);
        if (flag) {
            MPI_Recv(&recv, 1, MPI_INT, 3, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank 4 received unexpected message from Rank 3: %d\n", recv);
        } else {
            printf("Rank 4: No message from Rank 3 (as expected)\n");
        }
    }

    // Cleanup
    if (comm_a != MPI_COMM_NULL) MPI_Comm_free(&comm_a);
    if (comm_b != MPI_COMM_NULL) MPI_Comm_free(&comm_b);
    MPI_Group_free(&group_a);
    MPI_Group_free(&group_b);
    MPI_Group_free(&world_group);

    MPI_Finalize();
    return 0;
}
